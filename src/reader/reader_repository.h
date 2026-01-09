//
// Created by anton on 2025-12-14.
//

#ifndef ALGOS_KURSACH_GUEST_REPOSITORY_H
#define ALGOS_KURSACH_GUEST_REPOSITORY_H
#include <optional>
#include <set>
#include <string>
#include "reader.h"
#include "../utils/hash_map.h"

class reader_repository {
private:
    hash_map<short, reader> readers;
    std::set<short> readerIds;
    int count;
public:
    reader_repository();
    std::vector<reader> find(const std::function<bool(reader)> &predicate);
    std::optional<reader> findByStringId(const std::wstring &readerId);
    std::optional<reader> findById(short readerId);
    reader get(const std::wstring &readerId);
    reader get(short readerId);
    void save(const reader &guest);
    void remove(const std::wstring &readerId);
    void remove(const reader &guest);
    bool contains(const std::wstring &readerId);
    void clear();
    int countReaders() const;
    std::vector<reader> getAll() const;
};

#endif //ALGOS_KURSACH_GUEST_REPOSITORY_H