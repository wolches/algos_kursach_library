//
// Created by anton on 2025-12-15.
//

#ifndef ALGOS_KURSACH_SINGLE_LINKED_LIST_H
#define ALGOS_KURSACH_SINGLE_LINKED_LIST_H
#include <stdexcept>

template<typename T> struct iterative_node {
    T value;
    iterative_node<T>* next;

    // 3-5-0

    iterative_node(const T &v, iterative_node *n = 0) : value(v), next(n) {}

    ~iterative_node() {
        if (next) {
            delete next;
        }
    }

    iterative_node &operator=(const iterative_node &other) {
        value = other.value;
        next = nullptr;
        if (other.next) {
            next = new iterative_node(value);
            *next = *other.next;
        }
        return *this;
    }

    bool hasNext() {
        return next != nullptr;
    }
};

template<typename T> class single_linked_list {
private:
    iterative_node<T>* head;
public:
    // 3-5-0

    single_linked_list() {
        this->head = 0;
    }

    ~single_linked_list() {
        clear();
    }

    single_linked_list<T> &operator=(const single_linked_list<T> &other) {
        clear();
        if (other.head) {
            iterative_node<T> *newHead = new iterative_node<T>(other.head->value);
            *newHead = *other.head;
            head = newHead;
        }
        return *this;
    }

    iterative_node<T> *getHead() {
        return head;
    }

    iterative_node<T>* popHead() {
        iterative_node<T>* temp = this->head;
        if (temp != nullptr) {
            this->head = this->head->next;
        }
        return temp;
    }

    void add(T value) {
        if (this->head == nullptr) {
            this->head = new iterative_node<T>(value);
            return;
        }
        iterative_node<T> *node = this->head;
        while (node->hasNext()) {
            node = node->next;
        }
        node->next = new iterative_node<T>(value);
    }

    void add(T value, int index) {
        if (index == 0) {
            iterative_node<T> *newNode = new iterative_node<T>();
            newNode->value = value;
            newNode->next = this->head;
            this->head = newNode;
            return;
        }
        iterative_node<T> *node = this->head;
        while (node->hasNext() && index > 1) {
            node = node->next;
            index--;
        }
        if (index == 1) {
            iterative_node<T> *newNode = new iterative_node<T>();
            newNode->value = value;
            newNode->next = node->next;
            node->next = newNode;
            return;
        }
        throw std::out_of_range("index out of range");
    }

    T get(int index) {
        iterative_node<T> *node = this->head;
        while (node->next != nullptr && index > 0) {
            node = node->next;
            index--;
        }
        if (index == 0) {
            return node->value ;
        }
        throw std::out_of_range("index out of range");
    }

    void set(T value, int index) {
        iterative_node<T> *node = this->head;
        while (node->next != nullptr && index > 0) {
            node = node->next;
            index--;
        }
        if (index == 0) {
            node->value = value;
            return;
        }
        throw std::out_of_range("index out of range");
    }

    void remove(int index) {
        if (index == 0) {
            if (this->head == nullptr) throw std::out_of_range("index out of range");
            auto toRemove = this->head;
            this->head = this->head->next;
            delete toRemove;
            return;
        }
        iterative_node<T> *node = this->head;
        while (node->next != nullptr && index > 1) {
            node = node->next;
            index--;
        }
        if (index == 1 && node->next != nullptr) {
            auto toRemove = node->next;
            node->next = toRemove->next;
            delete toRemove;
            return;
        }
        throw std::out_of_range("index out of range");
    }

    void clear() {
        if (head != nullptr) {
            delete head;
            head = nullptr;
        }
    }

    int getSize() {
        int i = 0;
        iterative_node<T> *node = this->head;
        while (node != nullptr) {
            node = node->next;
            i++;
        }
        return i;
    }

};


#endif //ALGOS_KURSACH_SINGLE_LINKED_LIST_H