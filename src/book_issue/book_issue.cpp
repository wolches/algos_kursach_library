//
// Created by anton on 2026-01-08.
//

#include "book_issue.h"

book_issue::book_issue(std::wstring bookCode, std::wstring readerId, tm *date) {
    this->bookCode = bookCode;
    this->readerId = readerId;
    this->issueDate = date;
    this->returnDate = nullptr;
}

std::wstring book_issue::getBookCode() const {
    return this->bookCode;
}

std::wstring book_issue::getReaderId() const {
    return this->readerId;
}

tm *book_issue::getIssueDate() const {
    return this->issueDate;
}

tm *book_issue::getReturnDate() const {
    return this->returnDate;
}

void book_issue::setReturnDate(tm *date) {
    this->returnDate = date;
}


