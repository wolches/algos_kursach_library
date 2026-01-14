//
// Created for library management system
//

#include "library_service.h"
#include "../../book/book.h"
#include "../../reader/reader.h"
#include "../../book/book_code.h"
#include "../../reader/reader_id.h"
#include "../../reader/full_name.h"
#include "../../utils/short_value_object.h"
#include "../../utils/utils.h"
#include "../../book_issue/book_issue.h"
#include "../../utils/boyer_moore.h"
#include <optional>

library_service::library_service() {
    bookRepo = book_repository();
    readerRepo = reader_repository();
    issueRepo = book_issue_repository();
}

void library_service::registerReader(const std::wstring &readerAccess, const int &regYear, const std::wstring &fullName,
                                     short yearOfBirth, const std::wstring &address, const std::wstring &counterparty) {
    int totalReaders = readerRepo.countReaders();
    if (totalReaders > 9999) throw std::invalid_argument("Too many readers (>9999)");
    std::wstring stringId = addLeadingZeros(totalReaders, 4);
    std::wstring strRegYear = addLeadingZeros(regYear, 4).substr(2);
    std::wstring readerId = std::vformat(reader_id_format, std::make_wformat_args(readerAccess, stringId, strRegYear));
    reader_id id(readerId);
    full_name name(fullName);
    short_value_object year(yearOfBirth);
    reader r(id, name, year, address, counterparty);
    readerRepo.save(r);
}

void library_service::editReader(const std::wstring &readerId, const std::wstring &access, const std::wstring &fullName, short yearOfBirth,
                                 const std::wstring &address, const std::wstring &counterparty
) {
    auto optR = readerRepo.findByStringId(readerId);
    if (optR.has_value()) {
        reader_id id(readerId);
        id.setAccess(access[0]);
        full_name name(fullName);
        short_value_object year(yearOfBirth);
        reader r(id, name, year, address, counterparty);
        readerRepo.save(r);
    } else {
        throw std::invalid_argument("No such reader");
    }
}

void library_service::removeReader(const std::wstring &readerId) {
    if (readerRepo.contains(readerId)) {
        boyer_moore bm(readerId);
        auto issueSearchPredicate = [bm](const book_issue &bi) {
            bool res = bm.contains(bi.getReaderId());
            return res && bi.getReturnDate() != nullptr;
        };
        auto issues = issueRepo.findIssues(issueSearchPredicate);
        if (!issues.empty()) throw std::exception("Cannot delete reader with issued books!");
        readerRepo.remove(readerId);
    }
}

reader_info library_service::toDto(reader r) {
    reader_info info;
    info.readerId = r.getReaderId();
    info.fullName = r.getFullName();
    info.yearOfBirth = r.getYearOfBirth();
    info.address = r.getAddress();
    info.counterparty = r.getCounterParty();
    auto issues = issueRepo.findIssues([&r](book_issue issue) {
        return issue.getReaderId() == r.getReaderId() && issue.getReturnDate() == nullptr;
    });
    for (const auto &issue : issues) {
        info.issuedBookCodes.push_back(issue.getBookCode());
    }
    return info;
}

std::vector<reader_info> library_service::getAllReaders() {
    std::vector<reader_info> result;
    auto readers = readerRepo.getAll();
    for (auto &r : readers) {
        result.push_back(toDto(r));
    }
    return result;
}

void library_service::clearReaders() {
    readerRepo.clear();
}

std::optional<reader_info> library_service::findReaderById(const std::wstring &readerId) {
    auto optReader = readerRepo.findByStringId(readerId);
    if (!optReader.has_value()) {
        return std::nullopt;
    }
    return toDto(optReader.value());
}

std::vector<reader_info> library_service::fullTextReaderSearch(const std::wstring &pattern) {
    std::vector<reader_info> result;
    boyer_moore bm(pattern);
    auto readerSearchPredicate = [bm](const reader &r) {
        bool res = bm.contains(r.getReaderId())
        || bm.contains(r.getFullName())
        || bm.contains(r.getAddress())
        || bm.contains(r.getCounterParty())
        || bm.contains(std::to_wstring(r.getYearOfBirth()));
        return res;
    };
    auto readers = readerRepo.find(readerSearchPredicate);
    for (const auto &r : readers) {
        result.push_back(toDto(r));
    }
    return result;
}

void library_service::addBook(const short &categoryId, const short &bookId,
                              const std::wstring &name, const std::wstring &author,
                              const std::wstring &publisher, short year, short totalCopies) {
    book_code bookCode(categoryId, bookId);
    if (bookRepo.contains(bookCode)) {
        throw std::exception("book already exists!");
    }
    short_value_object yearObj(year);
    short_value_object copiesObj(totalCopies);
    book b(bookCode, name, author, publisher, yearObj, copiesObj);
    bookRepo.save(b);
}

void library_service::editBook(const std::wstring &code, const std::wstring &name, const std::wstring &author,
                               const std::wstring &publisher, short year, short totalCopies) {
    book_code bookCode(code);
    if (!bookRepo.contains(bookCode)) {
        throw std::exception("book not exists!");
    }
    boyer_moore bm(code);
    auto issueSearchPredicate = [bm](const book_issue &bi) {
        bool res = bm.contains(bi.getBookCode());
        return res && bi.getReturnDate() != nullptr;
    };
    auto issues = issueRepo.findIssues(issueSearchPredicate);
    if (!issues.empty()) {
        throw std::exception("Cannot edit issued books!");
    }
    short_value_object yearObj(year);
    short_value_object copiesObj(totalCopies);
    book b(bookCode, name, author, publisher, yearObj, copiesObj);
    bookRepo.save(b);
}

void library_service::removeBook(const std::wstring &code) {
    boyer_moore bm(code);
    auto issueSearchPredicate = [bm](const book_issue &bi) {
        bool res = bm.contains(bi.getBookCode());
        return res && bi.getReturnDate() != nullptr;
    };
    auto issues = issueRepo.findIssues(issueSearchPredicate);
    if (!issues.empty()) {
        throw std::exception("Cannot remove issued books!");
    }
    bookRepo.remove(code);
}

book_info library_service::toDto(book b) {
    book_info info;
    info.code = b.getCode();
    info.name = b.getName();
    info.author = b.getAuthor();
    info.publisher = b.getPublisher();
    info.year = b.getYear();
    info.totalCopies = b.getTotalCopies();

    // Find readers who have this book and calculate available
    auto issues = issueRepo.findIssues([&b](book_issue issue) {
        return issue.getBookCode() == b.getCode() && issue.getReturnDate() == nullptr;
    });
    info.available = b.getTotalCopies() - static_cast<short>(issues.size());

    for (const auto &issue : issues) {
        auto optReader = readerRepo.findByStringId(issue.getReaderId());
        if (optReader.has_value()) {
            reader r = optReader.value();
            info.issuedToReaders.push_back({r.getReaderId(), r.getFullName()});
        }
    }
    return info;
}


std::vector<book_info> library_service::getAllBooks() {
    std::vector<book_info> result;
    auto books = bookRepo.getAll();
    for (const auto &b : books) {
        result.push_back(toDto(b));
    }
    return result;
}

void library_service::clearBooks() {
    bookRepo.clear();
}

std::optional<book_info> library_service::findBookByCode(const std::wstring &code) {
    auto optBook = bookRepo.findByStringCode(code);
    if (!optBook.has_value()) {
        return std::nullopt;
    }
    return toDto(optBook.value());
}

std::vector<book_info> library_service::fullTextBookSearch(const std::wstring &pattern) {
    boyer_moore bm(pattern);
    auto readerSearchPredicate = [bm](const book &b) {
        bool res =
            bm.contains(b.getCode())
         || bm.contains(b.getAuthor())
         || bm.contains(b.getName())
         || bm.contains(b.getPublisher())
         || bm.contains(std::to_wstring(b.getYear()));
        return res;
    };
    auto books = bookRepo.find(readerSearchPredicate);
    std::vector<book_info> result;
    for (const auto &b : books) {
        result.push_back(toDto(b));
    }
    return result;
}

void library_service::issueBook(const std::wstring &bookCode, const std::wstring &readerId) {
    auto optBook = bookRepo.findByStringCode(bookCode);
    if (!optBook.has_value()) {
        throw std::invalid_argument("Book not found");
    }
    book b = optBook.value();
    auto issues = issueRepo.findIssues([&bookCode](book_issue issue) {
        return issue.getBookCode() == bookCode && issue.getReturnDate() == nullptr;
    });
    short actualAvailable = b.getTotalCopies() - static_cast<short>(issues.size());
    if (actualAvailable <= 0) {
        throw std::invalid_argument("No available copies");
    }
    auto optReader = readerRepo.findByStringId(readerId);
    if (!optReader.has_value()) {
        throw std::invalid_argument("Reader not found");
    }
    if (optReader->getAccess() == L'Ч') {
        throw std::invalid_argument("Access denied, only reading room allowed for this reader");
    }
    issueRepo.issueBook(bookCode, readerId);
}

void library_service::returnBook(const std::wstring &bookCode, const std::wstring &readerId) {
    auto optIssue = issueRepo.findNotReturned(bookCode, readerId);
    if (!optIssue.has_value()) {
        throw std::invalid_argument("Book issue not found");
    }
    issueRepo.returnBook(bookCode, readerId, now());
}

void library_service::clearIssues() {
    issueRepo.clear();
}

