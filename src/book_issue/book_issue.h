//
// Created by anton on 2026-01-08.
//

#ifndef ALGOS_KURSACH_BOOK_ISSUE_H
#define ALGOS_KURSACH_BOOK_ISSUE_H
#include <string>
#include "../utils/utils.h"


class book_issue {
public:
    book_issue(std::wstring bookCode, std::wstring readerId, tm *date);
    std::wstring getBookCode() const;
    std::wstring getReaderId() const;
    tm *getIssueDate() const;
    tm *getReturnDate() const;
    void setReturnDate(tm *date);
private:
    std::wstring bookCode;
    std::wstring readerId;
    tm* issueDate;
    tm* returnDate;
};


#endif //ALGOS_KURSACH_BOOK_ISSUE_H