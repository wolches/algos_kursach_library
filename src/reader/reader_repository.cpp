//
// Created by anton on 2025-12-14.
//

#include "reader_repository.h"
#include "../utils/utils.h"
#include <stdexcept>
#include <algorithm>
#include <cwctype>

reader_repository::reader_repository() :
readers(hash_map<short, reader>([](short k) {return k;}, 1000))
{
    this->count = 0;
    this->readerIds = std::set<short>();
}

void reader_repository::save(const reader &readerObj) {
    if (!this->readerIds.contains(readerObj.getId())) {
        readerIds.insert(readerObj.getId());
    }
    readers.insert(readerObj.getId(), readerObj);
    count++;
}

std::optional<reader> reader_repository::findById(short readerId) {
    try {
        reader r = readers.get(readerId);
        return std::optional(r);
    } catch (std::invalid_argument &e) {
        return std::nullopt;
    }
}

std::optional<reader> reader_repository::findByStringId(const std::wstring &readerId) {
    short id = (reader_id(readerId)).getId();
    return findById(id);
}

std::vector<reader> reader_repository::find(const std::function<bool(reader)> &predicate) {
    std::vector<reader> result;
    for (short id : readerIds) {
        try {
            reader r = readers.get(id);
            if (predicate(r)) {
                result.push_back(r);
            }
        } catch (...) {
            // Skip if not found
        }
    }
    return result;
}

reader reader_repository::get(const std::wstring &readerId) {
    short id = (reader_id(readerId)).getId();
    return get(id);
}

reader reader_repository::get(short readerId) {
    return readers.get(readerId);
}

void reader_repository::remove(const reader &readerObj) {
    readerIds.erase(readerObj.getId());
    count--;
    readers.remove(readerObj.getId());
}

void reader_repository::remove(const std::wstring &readerId) {
    short id = (reader_id(readerId)).getId();
    readerIds.erase(id);
    count--;
    readers.remove(id);
}

void reader_repository::clear() {
    readerIds.clear();
    count = 0;
    readers.clear();
}

int reader_repository::countReaders() const {
    return count;
}

std::vector<reader> reader_repository::getAll() const {
    std::vector<reader> result;
    for (short id : readerIds) {
        try {
            result.push_back(readers.get(id));
        } catch (...) {
            // Skip if not found
        }
    }
    return result;
}

bool reader_repository::contains(const std::wstring &readerId) {
    reader_id id = reader_id(readerId);
    return readerIds.contains(id.getId());
}