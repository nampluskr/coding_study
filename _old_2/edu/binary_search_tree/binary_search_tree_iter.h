#pragma once

template<typename T>
struct Queue {
    struct Node {
        T data;
        Node* next = nullptr;
    };
    Node* head = nullptr;
    Node* tail = nullptr;

    void push(const T& data) {
        Node* node = new Node{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
    }
    void pop() {
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) tail = nullptr;
    }
    T front() { return head->data; }
    bool empty() { return head == nullptr; }
};

template<typename T>
struct BinarySearchTreeIter {
    struct Node {
        T data;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    Node* root;

    void clear() {
        if (root == nullptr) return;
        Queue<Node*> Q;
        Q.push(root);
        while (!Q.empty()) {
            auto cur = Q.front(); Q.pop();
            if (cur->left != nullptr) Q.push(cur->left);
            if (cur->right != nullptr) Q.push(cur->right);
            delete cur;
        }
        root = nullptr;
    }
    void insert(const T& data) {
        Node* prev = nullptr;
        Node* cur = root;
        while (cur != nullptr) {
            if (cur->data == data) return;
            prev = cur;
            if (data < cur->data) cur = cur->left;
            else cur = cur->right;
        }
        // cur == nullptr
        Node* node = new Node{ data, nullptr, nullptr };
        if (prev == nullptr) root = node;
        else if (data < prev->data) prev->left = node;
        else prev->right = node;
    }
    Node* find(const T& data) {
        Node* cur = root;
        while (cur != nullptr) {
            if (cur->data == data) return cur;
            if (data < cur->data) cur = cur->left;
            else cur = cur->right;
        }
        return nullptr;
    }
    void erase(const T& data) {
        Node* prev = nullptr;
        Node* cur = root;
        while (cur != nullptr) {
            if (cur->data == data) break;
            prev = cur;
            if (data < cur->data) cur = cur->left;
            else cur = cur->right;
        }
        if (cur == nullptr) return;
        // cur->data == data
        // Case 1: No child
        if (cur->left == nullptr && cur->right == nullptr) {
            if (prev == nullptr) root = nullptr;
            else if (prev->left == cur) prev->left = nullptr;
            else prev->right = nullptr;
        }
        // Case 2: One child
        else if (cur->left == nullptr || cur->right == nullptr) {
            Node* child = (cur->left != nullptr)? cur->left: cur->right;
            if (prev == nullptr) root = child;
            else if (prev->left == cur) prev->left = child;
            else prev->right = child;
        }
        // Case 3: Two children
        else {
            Node* temp_prev = cur;
            Node* temp_cur = cur->right;
            while (temp_cur->left != nullptr) {
                temp_prev = temp_cur;
                temp_cur = temp_cur->left;
            }
            cur->data = temp_cur->data; // min node
            if (temp_prev->left == temp_cur) temp_prev->left = temp_cur->right;
            else temp_prev->right = temp_cur->right;
            cur = temp_cur;
        }
        delete cur;
    }
};