//
// Created by anton on 2026-01-08.
//

#ifndef ALGOS_KURSACH_BOOK_ISSUE_REPOSITORY_H
#define ALGOS_KURSACH_BOOK_ISSUE_REPOSITORY_H
#include <functional>
#include <optional>
#include <vector>

#include "book_issue.h"
#include "../utils/single_linked_list.h"


class book_issue_repository {
public:
    book_issue_repository();
    std::vector<book_issue> findIssues(const std::function<bool(book_issue)> &predicate);
    std::optional<book_issue> findNotReturned(std::wstring bookCode, std::wstring readerId);
    void issueBook(const std::wstring &bookCode, const std::wstring &readerId);
    void returnBook(const std::wstring &bookCode, const std::wstring &readerId, tm *date);
    void clear();
private:
    single_linked_list<book_issue> issues;
    void sort();
    book_issue &getNotReturned(const std::wstring &bookCode, const std::wstring &readerId);
    book_issue &getNotReturned(const std::wstring &bookCode, const std::wstring &readerId, const tm &date);
};


#endif //ALGOS_KURSACH_BOOK_ISSUE_REPOSITORY_H