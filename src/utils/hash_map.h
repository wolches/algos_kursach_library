//
// Created by anton on 2025-12-15.
//

#ifndef ALGOS_KURSACH_HASH_MAP_H
#define ALGOS_KURSACH_HASH_MAP_H
#include <functional>
#include <utility>

#include "single_linked_list.h"

inline const unsigned long long p = 997;
inline const unsigned long long mod = 1'000'000'007;

template<typename K, typename V>
class hash_map {
private:
    std::function<unsigned long long(const K&)> hasher;
    single_linked_list<std::pair<K, V>> **buckets;
    unsigned long long size;
    unsigned long long bucketsCount;

    single_linked_list<std::pair<K, V>> &bucket(const K &key) {
        if (buckets == nullptr) {
            buckets = new single_linked_list<std::pair<K, V>>*[bucketsCount];
            for (unsigned long long i = 0; i < bucketsCount; i++) {
                buckets[i] = new single_linked_list<std::pair<K, V>>;
            }
        }
        unsigned long long bucket = hasher(key) % bucketsCount;
        single_linked_list<std::pair<K, V>> *ptr = buckets[bucket];
        if (ptr == nullptr) {
            buckets[bucket] = new single_linked_list<std::pair<K, V>>();
            ptr = buckets[bucket];
        }
        single_linked_list<std::pair<K, V>> &ref = *ptr;
        return ref;
    }

    single_linked_list<std::pair<K, V>> &bucket(const K &key) const {
        if (buckets == nullptr) {
            throw std::runtime_error("Hash map not initialized");
        }
        unsigned long long bucket = hasher(key) % bucketsCount;
        single_linked_list<std::pair<K, V>> *ptr = buckets[bucket];
        if (ptr == nullptr) {
            throw std::runtime_error("Bucket not found");
        }
        single_linked_list<std::pair<K, V>> &ref = *ptr;
        return ref;
    }
public:
    hash_map(
        std::function<unsigned long long(const K&)> hasher,
        unsigned long long bucketsCount
    ) : hasher(hasher),
        bucketsCount(bucketsCount),
        size(0),
        buckets(nullptr) {
        buckets = new single_linked_list<std::pair<K, V>>*[bucketsCount];
        for (unsigned long long i = 0; i < bucketsCount; i++) {
            buckets[i] = new single_linked_list<std::pair<K, V>>;
        }
    }

    ~hash_map() {
        clear();
    }

    hash_map &operator=(const hash_map &other) {
        clear();
        bucketsCount = other.bucketsCount;
        hasher = other.hasher;
        size = other.size;
        buckets = new single_linked_list<std::pair<K, V>>*[bucketsCount];
        for (unsigned long long i = 0; i < bucketsCount; i++) {
            buckets[i] = new single_linked_list<std::pair<K, V>>;
        }
        if (!other.isEmpty() && other.buckets != nullptr) {
            for (unsigned long long i = 0; i < other.bucketsCount; i++) {
                *buckets[i] = *other.buckets[i];
            }
        }
        return *this;
    }

    void insert(const K& key, const V& value) {
        single_linked_list<std::pair<K, V>> &list = bucket(key);
        iterative_node<std::pair<K, V>>* node = list.getHead();
        while (node != nullptr) {
            if (node->value.first == key) {
                node->value = std::make_pair(key, value);
                return;
            }
            node = node->next;
        }
        list.add(std::make_pair(key, value));
        size++;
    }

    V get(const K& key) const {
        try {
            single_linked_list<std::pair<K, V>> &list = bucket(key);
            iterative_node<std::pair<K, V>> *node = list.getHead();
            while (node != nullptr && node->value.first != key) {
                node = node->next;
            }
            if (node != nullptr) {
                return node->value.second;
            }
        } catch (std::exception &e) {
            // NOOP
        }
        throw std::invalid_argument("Key not found");
    }

    bool contains(const K& key) const {
        try {
            single_linked_list<std::pair<K, V>> &list = bucket(key);
            iterative_node<std::pair<K, V>> *node = list.getHead();
            while (node != nullptr && node->value.first != key) {
                node = node->next;
            }
            return node != nullptr;
        } catch (std::exception &e) {
            return false;
        }
    }

    void remove(const K& key) {
        single_linked_list<std::pair<K, V>> &list = bucket(key);
        iterative_node<std::pair<K, V>> *node = list.getHead();
        if (node == nullptr) {
            return;
        }
        if (node->value.first == key) {
            iterative_node<std::pair<K, V>> *toRemove = list.popHead();
            toRemove->next = nullptr;
            delete toRemove;
            size--;
            return;
        }
        while (node->hasNext()) {
            if (node->next->value.first == key) {
                const iterative_node<std::pair<K, V>> *toRemove = node->next;
                node->next = toRemove->next;
                delete toRemove;
                size--;
                return;
            }
            node = node->next;
        }
    }

    void clear() {
        if (buckets != nullptr) {
            for (int i = 0; i < this->bucketsCount; i++) {
                this->buckets[i]->~single_linked_list<std::pair<K, V>>();
            }
            delete this->buckets;
            this->buckets = nullptr;
        }
        size = 0;
    }

    bool isEmpty() const {
        return size == 0;
    }

    unsigned long long getSize() const {
        return size;
    }
};


#endif //ALGOS_KURSACH_HASH_MAP_H