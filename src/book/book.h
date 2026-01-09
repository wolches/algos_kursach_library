//
// Created by anton on 2025-12-15.
//

#ifndef ALGOS_KURSACH_BOOK_H
#define ALGOS_KURSACH_BOOK_H
#include <string>

#include "book_code.h"
#include "../utils/short_value_object.h"

class book {
private:
    book_code code;
    std::wstring name;
    std::wstring author;
    std::wstring publisher;
    short_value_object year;
    short_value_object totalCopies;
    short_value_object available;
public:
    book();
    book(book_code code,
        std::wstring name, std::wstring author, std::wstring publisher,
        short_value_object year, short_value_object totalCopies
    );
    short getCategoryId();
    short getBookId();
    std::wstring getCode() const;
    std::wstring getName() const;
    std::wstring getAuthor() const;
    std::wstring getPublisher() const;
    short getYear() const;
    short getTotalCopies() const;
    short getAvailable() const;
};


#endif //ALGOS_KURSACH_BOOK_H