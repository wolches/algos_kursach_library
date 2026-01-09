//
// Created by anton on 2025-12-15.
//

#include "book.h"

book::book() {
    
}

book::book(
    book_code code, std::wstring name, std::wstring author, std::wstring publisher,
    short_value_object year, short_value_object totalCopies
) {
    this->code = code;
    this->name = name;
    this->author = author;
    this->publisher = publisher;
    this->year = year;
    this->totalCopies = totalCopies;
    this->available = totalCopies;
}

short book::getBookId() {
    return code.getBookId();
}

short book::getCategoryId() {
    return code.getCategoryId();
}

std::wstring book::getCode() const {
    return code.getValue();
}

std::wstring book::getName() const {
    return name;
}

std::wstring book::getAuthor() const {
    return author;
}

std::wstring book::getPublisher() const {
    return publisher;
}

short book::getAvailable() const {
    return available.getValue();
}

short book::getTotalCopies() const {
    return totalCopies.getValue();
}

short book::getYear() const {
    return year.getValue();
}



