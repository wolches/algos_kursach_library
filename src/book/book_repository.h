//
// Created by anton on 2026-01-07.
//

#ifndef ALGOS_KURSACH_BOOK_REPOSITORY_H
#define ALGOS_KURSACH_BOOK_REPOSITORY_H
#include <optional>
#include "book.h"
#include "book_code.h"
#include "../utils/tree_map.h"

class book_repository {
private:
    tree_map<book_code, book> books;
public:
    book_repository();
    std::optional<book> findByCode(book_code bookCode);
    std::optional<book> findByStringCode(const std::wstring &bookCode);
    std::vector<book> find(const std::function<bool(book)> &predicate);
    book get(const std::wstring &bookCode);
    book get(book_code bookCode);
    void save(const book &bookEntity);
    void remove(const std::wstring &bookCode);
    void remove(const book &entity);
    bool contains(const book_code &bookCode);
    void clear();
    int countBooks() const;
    std::vector<book> getAll() const;
};


#endif //ALGOS_KURSACH_BOOK_REPOSITORY_H