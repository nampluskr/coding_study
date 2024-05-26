#pragma once

template<typename T>
struct BinarySearchTreeRecur {
    struct Node {
        T data;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    Node* root;

    Node* clearRecur(Node* cur) {
        if (cur == nullptr) return nullptr;
        cur->left = clearRecur(cur->left);
        cur->right = clearRecur(cur->right);
        delete cur;
        return nullptr;
    }
    Node* insertRecur(Node* cur, const T& data) {
        if (cur == nullptr) return new Node{ data, nullptr, nullptr };
        if (cur->data == data) return cur;
        if (data < cur->data) cur->left = insertRecur(cur->left, data);
        else cur->right = insertRecur(cur->right, data);
        return cur;
    }
    Node* findRecur(Node* cur, const T& data) {
        if (cur == nullptr) return nullptr;
        if (cur->data == data) return cur;
        if (data < cur->data) return findRecur(cur->left, data);
        else return findRecur(cur->right, data);
    }
    Node* findMin(Node* cur) {
        if (cur->left == nullptr) return cur;
        return findMin(cur->left);
    }
    // SWEA set
    Node* eraseRecur(Node* cur, const T& data) {
        if (cur == nullptr) return nullptr;
        if (cur->data == data) {
            // Case 1: No child
            if (cur->left == nullptr && cur->right == nullptr) {
                delete cur;
                return nullptr;
            }
            // Case 2: One child
            else if (cur->left == nullptr || cur->right == nullptr) {
                Node* child = (cur->left != nullptr)? cur->left: cur->right;
                delete cur;
                return child;
            // Case 3: Two children
            } else {
                Node* min_node = findMin(cur->right);
                cur->data = min_node->data;
                cur->right = eraseRecur(cur->right, cur->data);
            }
        }
        if (data < cur->data) cur->left = eraseRecur(cur->left, data);
        else cur->right = eraseRecur(cur->right, data);
        return cur;
    }

    // Implementation
    void clear() { root = clearRecur(root); }
    void insert(const T& data) { root = insertRecur(root, data); }
    Node* find(const T& data) { return findRecur(root, data); }
    void erase(const T& data) { root = eraseRecur(root, data); }
};