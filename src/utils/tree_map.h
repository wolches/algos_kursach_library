//
// Created by anton on 2026-01-03.
//

#ifndef ALGOS_KURSACH_TREE_MAP_H
#define ALGOS_KURSACH_TREE_MAP_H
#include <functional>
#include <stack>
#include <stdexcept>
#include <vector>

template<typename K, typename V>
struct tree_node {
    K key;
    V value;
    tree_node<K, V> *left;
    tree_node<K, V> *right;
};

template<typename K, typename V>
class tree_map {
private:
    tree_node<K, V> *root;
    std::function<int(K, K)> keyComparator;

    tree_node<K, V> *rebalance(tree_node<K, V> *node) {
        int bal = balance(node);
        if (bal > 1 && balance(node->left) >= 0) {
            return rotate_right(node);
        }
        if (bal > 1 && balance(node->left) < 0) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        if (bal < -1 && balance(node->right) <= 0) {
            return rotate_right(node);
        }
        if (bal < -1 && balance(node->right) > 0) {
            node->right = rotate_right(node->right);
            return rotate_right(node);
        }
        return node;
    }

    int height(tree_node<K, V> *node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(height(node->left), height(node->right));
    }

    int balance(tree_node<K, V> *node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    tree_node<K, V> *rotate_left(tree_node<K, V> *root) {
        if (root == nullptr) {
            return nullptr;
        }
        tree_node<K, V> *newRoot = root->right;
        tree_node<K, V> *temp = newRoot->left;
        newRoot->left = root;
        root->right = temp;
        return newRoot;
    }

    tree_node<K, V> *rotate_right(tree_node<K, V> *node) {
        if (root == nullptr) {
            return nullptr;
        }
        tree_node<K, V> *newRoot = root->left;
        tree_node<K, V> *temp = newRoot->right;
        newRoot->right = root;
        root->left = temp;
        return newRoot;
    }

    tree_node<K, V> *insert_with_rebalance(tree_node<K, V> *node, const K& key, const V& value) {
        if (node == nullptr) {
            auto *newNode = new tree_node<K, V>(key, value, nullptr, nullptr);
            /*
            newNode->key = key;
            newNode->value = value;
            newNode->left = nullptr;
            newNode->right = nullptr;*/
            return newNode;
        }
        int cmp = keyComparator(node->key, key);
        if (cmp == 0) {
            node->value = value;
        } else if (cmp > 0) {
            // left
            node->left = insert_with_rebalance(node->left, key, value);
        } else {
            // right
            node->right = insert_with_rebalance(node->right, key, value);
        }
        return rebalance(node);
    }

    tree_node<K, V> *remove_with_rebalance(tree_node<K, V> *node, const K& key) {
        if (node == nullptr) {
            return nullptr;
        }
        int cmp = keyComparator(node->key, key);
        if (cmp == 0) {
            if (node->left != nullptr && node->right != nullptr) {
                auto min_larger = min(node->right);
                node->key = min_larger->key;
                node->value = min_larger->value;
                node->right = remove_with_rebalance(node->right, min_larger->key);
            } else if (node->right == nullptr) {
                auto temp = node->left;
                delete node;
                return temp;
            } else {
                auto temp = node->right;
                delete node;
                return temp;
            }
        } else if (cmp > 0) {
            // left
            node->left = remove_with_rebalance(node->left, key);
        } else {
            // right
            node->right = remove_with_rebalance(node->right, key);
        }
        return rebalance(node);
    }

    tree_node<K, V> *min(tree_node<K, V> *node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    tree_node<K, V> *max(tree_node<K, V> *node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    int size(tree_node<K, V> *node) const {
        if (node == nullptr) return 0;
        return size(node->left) + size(node->right) + 1;
    }

    /**
     * Симметричный обход дерева1
     */
    void collectValues(tree_node<K, V> *node, std::vector<V> &result) const {
        if (node == nullptr) return;
        collectValues(node->left, result);
        result.push_back(node->value);
        collectValues(node->right, result);
    }

public:
    tree_map(std::function<int(K, K)> keyComparator) {
        this->keyComparator = keyComparator;
        this->root = nullptr;
    }

    ~tree_map() {
        clear();
    }

    void insert(const K& key, const V& value) {
        root = insert_with_rebalance(root, key, value);
    }

    V get(const K& key) {
        if (root == nullptr) {
            throw std::out_of_range("Key not found");
        }
        tree_node<K, V> *current = root;
        while (true) {
            int cmp = keyComparator(current->key, key);
            if (cmp == 0) {
                return current->value;
            } else if (cmp > 0) {
                // left
                if (current->left == nullptr) {
                    break;
                }
                current = current->left;
            } else {
                // right
                if (current->right == nullptr) {
                    break;
                }
                current = current->right;
            }
        }
        throw std::out_of_range("Key not found");
    }

    std::pair<K, V> lower_bound(const K& key)  {
        tree_node<K, V> *current = root;
        tree_node<K, V> *result = nullptr;
        while (current != nullptr) {
            if (keyComparator(current->key, key) >= 0) {
                result = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (result == nullptr) {
            throw std::out_of_range("Key not found");
        }
        return std::make_pair(result->key, result->value);
    }

    std::pair<K, V> upper_bound(const K& key) {
        tree_node<K, V> *current = root;
        tree_node<K, V> *result = nullptr;
        while (current != nullptr) {
            if (keyComparator(current->key, key) <= 0) {
                result = current;
                current = current->right;
            } else {
                current = current->left;
            }
        }
        if (result == nullptr) {
            throw std::out_of_range("Key not found");
        }
        return std::make_pair(result->key, result->value);
    }

    bool contains(const K& key) {
        if (root == nullptr) {
            return false;
        }
        tree_node<K, V> *current = root;
        while (true) {
            int cmp = keyComparator(current->key, key);
            if (cmp == 0) {
                return true;
            } else if (cmp > 0) {
                if (current->left == nullptr) {
                    break;
                }
                current = current->left;
            } else {
                if (current->right == nullptr) {
                    break;
                }
                current = current->right;
            }
        }
        return false;
    }

    void remove(const K& key) {
        root = remove_with_rebalance(root, key);
    }

    void clear() {
        std::stack<tree_node<K, V> *> toRemove;
        if (root != nullptr) toRemove.push(root);
        root = nullptr;
        while (!toRemove.empty()) {
            tree_node<K, V> *node = toRemove.top();
            toRemove.pop();
            if (node->left != nullptr) toRemove.push(node->left);
            if (node->right != nullptr) toRemove.push(node->right);
            delete node;
        }
    }

    int size() const {
        return size(root);
    }

    std::vector<V> getAllValues() const {
        std::vector<V> result;
        collectValues(root, result);
        return result;
    }
};

#endif //ALGOS_KURSACH_TREE_MAP_H