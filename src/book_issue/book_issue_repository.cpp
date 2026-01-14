//
// Created by anton on 2026-01-08.
//

#include "book_issue_repository.h"

#include <chrono>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "../book/book_code.h"
#include "../utils/single_linked_list.h"
#include "../utils/utils.h"

book_issue_repository::book_issue_repository() : issues() {

}

int index(book_code value) {
    return value.getCategoryId() * 1000 + value.getBookId();
}

// Подсчетом
void book_issue_repository::sort() {
    std::vector<int> counts(1000000);
    std::unordered_map<int, std::vector<book_issue>> values;
    for (int i = 0; i < 1000000; ++i) {
        counts[i] = 0;
        values[i] = std::vector<book_issue>();
    }
    auto node = issues.getHead();
    while (node != nullptr) {
        auto value = node->value;
        int i = index(book_code(value.getBookCode()));
        counts[i]++;
        values[i].push_back(value);
        node = node->next;
    }
    node = issues.getHead();
    for (int i = 0; i < 1000000 && node != nullptr; ++i) {
        for (const auto &issue : values[i]) {
            node->value = issue;
            node = node->next;
        }
    }
}

void book_issue_repository::returnBook(const std::wstring &bookCode, const std::wstring &readerId, tm *date) {
    auto issue = getNotReturned(bookCode, readerId, *date);
    issue.setReturnDate(date);
}

void book_issue_repository::issueBook(const std::wstring &bookCode, const std::wstring &readerId) {
    issues.add(book_issue(bookCode, readerId, now()));
    sort();
}

void book_issue_repository::clear() {
    issues.clear();
}

std::optional<book_issue> book_issue_repository::findNotReturned(std::wstring bookCode, std::wstring readerId) {
    try {
        return std::optional(getNotReturned(bookCode, readerId));
    } catch (...) {
        return std::nullopt;
    }
}

book_issue &book_issue_repository::getNotReturned(const std::wstring &bookCode, const std::wstring &readerId) {
    auto node = issues.getHead();
    while (node != nullptr) {
        if (node->value.getBookCode() == bookCode && readerId == node->value.getReaderId()) {
            if (node->value.getReturnDate() == nullptr) {
                return node->value;
            }
        }
        node = node->next;
    }
    throw std::invalid_argument("Book issue not found!");
}

book_issue &book_issue_repository::getNotReturned(const std::wstring &bookCode, const std::wstring &readerId, const tm &date) {
    auto node = issues.getHead();
    while (node != nullptr) {
        if (node->value.getBookCode() == bookCode && readerId == node->value.getReaderId()) {
            if (node->value.getReturnDate() == nullptr) {
                if (isGreaterOrEqual(date, *node->value.getIssueDate())) {
                    return node->value;
                }
            }
        }
        node = node->next;
    }
    throw std::invalid_argument("Book issue not found!");
}



std::vector<book_issue> book_issue_repository::findIssues(const std::function<bool(book_issue)> &predicate) {
    auto node = issues.getHead();
    std::vector<book_issue> result;
    while (node != nullptr) {
        if (predicate(node->value)) {
            result.push_back(node->value);
        }
        node = node->next;
    }
    return result;
}



