//
// Created by anton on 2025-12-15.
//

#include "book_code.h"

#include <format>
#include <regex>

#include "../utils/utils.h"

book_code::book_code() {
    this->categoryId = -1;
    this->bookId = -1;
}

book_code::book_code(std::wstring value) {
    value = trim(value);
    if (std::regex_match(value, std::wregex(book_code_regex))) {
        auto parts = split(value, L".");
        this->categoryId = std::stoi(parts[0]);
        this->bookId = std::stoi(parts[1]);
    } else {
        throw std::invalid_argument("Invalid book code value");
    }
}

book_code::book_code(short categoryId, short bookId) {
    this->categoryId = categoryId;
    this->bookId = bookId;
    validate();
}

void book_code::validate() {
    if (categoryId > 999 || bookId > 999) throw std::invalid_argument("Invalid book code");
}

short book_code::getBookId() {
    return bookId;
}

short book_code::getCategoryId() {
    return categoryId;
}

std::wstring book_code::getValue() const {
    const auto strCat = addLeadingZeros(categoryId, 3);
    const auto strBook = addLeadingZeros(bookId, 3);
    return std::vformat(
        book_code_format,
        std::make_wformat_args(strCat, strBook)
    );
}

bool book_code::operator<(const book_code &other) const {
    int self = categoryId * 1000 + bookId;
    int otherCategoryId = other.categoryId * 1000 + other.bookId;
    return self < otherCategoryId;
}

bool book_code::operator==(const book_code &other) const {
    int selfId = categoryId * 1000 + bookId;
    int otherId = other.categoryId * 1000 + other.bookId;
    return selfId == otherId;
}




