//
// Created for library management system
//

#ifndef ALGOS_KURSACH_LIBRARY_SERVICE_H
#define ALGOS_KURSACH_LIBRARY_SERVICE_H

#include <string>
#include <vector>
#include "../../book/book_repository.h"
#include "../../reader/reader_repository.h"
#include "../../book_issue/book_issue_repository.h"

struct reader_info {
    std::wstring readerId;
    std::wstring fullName;
    short yearOfBirth;
    std::wstring address;
    std::wstring counterparty;
    std::vector<std::wstring> issuedBookCodes;
};

struct book_info {
    std::wstring code;
    std::wstring name;
    std::wstring author;
    std::wstring publisher;
    short year;
    short totalCopies;
    short available;
    std::vector<std::pair<std::wstring, std::wstring>> issuedToReaders; // readerId, fullName
};

class library_service {
private:
    book_repository bookRepo;
    reader_repository readerRepo;
    book_issue_repository issueRepo;
    reader_info toDto(reader r);
    book_info toDto(book b);
public:
    library_service();
    
    // Reader operations
    void registerReader(
        const std::wstring &readerAccess, const int &year, const std::wstring &fullName,
        short yearOfBirth, const std::wstring &address, const std::wstring &counterparty
    );
    void editReader(
        const std::wstring &readerId, const std::wstring &fullName,
        short yearOfBirth, const std::wstring &address, const std::wstring &counterparty
    );
    void removeReader(const std::wstring &readerId);
    std::vector<reader_info> getAllReaders();
    void clearReaders();
    std::optional<reader_info> findReaderById(const std::wstring &readerId);
    std::vector<reader_info> fullTextReaderSearch(const std::wstring &nameFragment);
    
    // Book operations
    void addBook(const short &categoryId, const short &bookId, const std::wstring &name,
                 const std::wstring &author, const std::wstring &publisher, short year, short totalCopies);
    void editBook(const std::wstring &code, const std::wstring &name,
                  const std::wstring &author, const std::wstring &publisher, short year, short totalCopies);
    void removeBook(const std::wstring &code);
    std::vector<book_info> getAllBooks();
    void clearBooks();
    std::optional<book_info> findBookByCode(const std::wstring &code);
    std::vector<book_info> fullTextBookSearch(const std::wstring &pattern);
    
    // Book issue operations
    void issueBook(const std::wstring &bookCode, const std::wstring &readerId);
    void returnBook(const std::wstring &bookCode, const std::wstring &readerId);
    void clearIssues();
};

#endif //ALGOS_KURSACH_LIBRARY_SERVICE_H
