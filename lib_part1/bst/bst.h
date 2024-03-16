#pragma once

template<typename T>
struct Node {
    T data;
    Node* left;
    Node* right;
};

template<typename T>
struct BST_recur {
    Node<T>* root;

    Node<T>* find(const T& data) { return find(root, data); }
    void insert(const T& data) { root = insert(root, data); }
    void remove(const T& data) { root = remove(root, data); }

    Node<T>* find(Node<T>* curr, const T& data) {
        if (curr == nullptr) return nullptr;
        if (data == curr->data) return curr;
        if (data < curr->data) return find(curr->left, data);
        else return find(curr->right, data);
    }
    Node<T>* insert(Node<T>* curr, const T& data) {
        if (curr == nullptr) return new Node<T>{ data, nullptr };
        //if (data == curr->data) return curr;
        if (data < curr->data) curr->left = insert(curr->left, data);
        else if (curr->data < data) curr->right = insert(curr->right, data);
        return curr;
    }
    Node<T>* remove(Node<T>* curr, const T& data) {
        if (curr == nullptr) return nullptr;
        if (data == curr->data) {
            if (curr->left == nullptr && curr->right == nullptr) {
                delete curr;
                return nullptr;
            }
            else if (curr->right == nullptr) {
                auto temp = curr->left;
                delete curr;
                return temp;
            }
            else if (curr->left == nullptr) {
                auto temp = curr->right;
                delete curr;
                return temp;
            }
            else {
                auto succ = findMinNode(curr->right);
                curr->data = succ->data;
                curr->right = remove(curr->right, succ->data);
            }
        }
        if (data < curr->data) curr->left = remove(curr->left, data);
        else curr->right = remove(curr->right, data);
        return curr;
    }
    Node<T>* findMinNode(Node<T>* curr) {
        if (curr == nullptr) return nullptr;
        if (curr->left == nullptr) return curr;
        return findMinNode(curr->left);
    }
};

template<typename T>
struct BST_iter {
    Node<T>* root;

    Node<T>* find(const T& data) {
        Node<T>* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) return curr;
            if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) return;
            prev = curr;
            if (data < curr->data) curr = curr->left;
            else if (curr->data < data) curr = curr->right;
        }

        // curr == nullptr
        Node<T>* node = new Node<T>{ data, nullptr };
        if (prev == nullptr) root = node;
        else if (data < prev->data) prev->left = node;
        else prev->right = node;
    }
    void remove(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) break;
            prev = curr;
            if (data < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        if (curr == nullptr) return nullptr;

        // data == curr->data
        if (curr->left == nullptr && curr->right) {
            if (prev == nullptr) root = nullptr;
            else if (data < prev->data) prev->left = nullptr;
            else prev->right = nullptr;
        }
        else if (curr->right == nullptr) {
            if (prev == nullptr) root = curr->left;
            else if (data < prev->data) prev->left = curr->left;
            else prev->right = curr->left;
        }
        else if (curr->left == nullptr) {
            if (prev == nullptr) root = curr->right;
            else if (data < prev->data) prev->left = curr->right;
            else prev->right = curr->right;
        }
        else {
            Node<T>* succ_prev = curr;
            Node<T>* succ = curr->right;
            while (succ->left != nullptr) {
                succ_prev = curr;
                succ = curr->left;
            }
            curr->data = succ->data;
            if (succ_prev->left == succ) succ_prev->left = succ->right;
            else succ_prev->right = succ->right;
            curr = succ;    // delete succ
        }
        delete curr;
    }
};