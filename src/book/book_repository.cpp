//
// Created by anton on 2026-01-07.
//

#include "book_repository.h"
#include "book.h"
#include "book_code.h"
#include "../utils/tree_map.h"

book_repository::book_repository() : books([](const book_code &a, const book_code &b) {return 0;}) {
    auto compareFunc = [](const book_code &a, const book_code &b) {
        return a == b ? 0 : (a < b ? -1 : 1);
    };
    this->books = tree_map<book_code, book>(compareFunc);
}

void book_repository::save(const book &bookEntity) {
    books.insert(bookEntity.getCode(), bookEntity);
}

book book_repository::get(book_code bookCode) {
    return books.get(bookCode);
}

book book_repository::get(const std::wstring &bookCode) {
    return get(book_code(bookCode));
}

void book_repository::remove(const book &entity) {
    books.remove(entity.getCode());
}

void book_repository::remove(const std::wstring &bookCode) {
    books.remove(book_code(bookCode));
}

std::optional<book> book_repository::findByCode(book_code bookCode) {
    try {
        return get(bookCode);
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<book> book_repository::findByStringCode(const std::wstring &bookCode) {
    return findByCode(book_code(bookCode));
}

void book_repository::clear() {
    books.clear();
}

int book_repository::countBooks() const {
    return books.size();
}

std::vector<book> book_repository::getAll() const {
    return books.getAllValues();
}

bool book_repository::contains(const book_code &bookCode) {
    return books.contains(bookCode);
}

std::vector<book> book_repository::find(const std::function<bool(book)> &predicate) {
    auto all = books.getAllValues();
    std::vector<book> result;
    for (auto &b : all) {
        if (predicate(b)) {
            result.push_back(b);
        }
    }
    return result;
}









