//
// Created by anton on 2025-12-15.
//

#ifndef ALGOS_KURSACH_BOOK_CODE_VALUE_OBJ_H
#define ALGOS_KURSACH_BOOK_CODE_VALUE_OBJ_H
#include <string>

inline const std::wstring book_code_regex = L"\\d{3}\\.\\d{3}";
inline const std::wstring book_code_format = L"{}.{}";

class book_code {
public:
    book_code();
    book_code(std::wstring value);
    book_code(short categoryId, short bookId);
    std::wstring getValue() const;
    short getCategoryId();
    short getBookId();
    bool operator<(const book_code &other) const;
    bool operator==(const book_code &other) const;
private:
    short categoryId;
    short bookId;
    void validate();
};


#endif //ALGOS_KURSACH_BOOK_CODE_VALUE_OBJ_H