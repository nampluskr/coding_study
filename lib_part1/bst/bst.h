#pragma once

#include <queue>
#include <stack>

template<typename T>
struct Node {
    T data;
    Node* left;
    Node* right;
};

template<typename T>
struct BinarySearchTree_recur {
    Node<T>* root;

    void clear() { root = clear(root); }
    Node<T>* find(const T& data) { return find(root, data); }
    void insert(const T& data) { root = insert(root, data); }
    void remove(const T& data) { root = remove(root, data); }

    Node<T>* clear(Node<T>* curr) {
        if (curr == nullptr) return nullptr;
        curr->left = clear(curr->left);
        curr->right = clear(curr->right);
        delete curr;
        return nullptr;
    }
    Node<T>* find(Node<T>* curr, const T& data) {
        if (curr == nullptr) return nullptr;
        if (data == curr->data) return curr;
        if (data < curr->data) return find(curr->left, data);
        else return find(curr->right, data);
    }
    Node<T>* insert(Node<T>* curr, const T& data) {
        if (curr == nullptr) return new Node<T>{ data, nullptr };
        if (data == curr->data) return curr;    // 중복 불가
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
               Node<T>* temp = curr->left;
               delete curr;
               return temp;
           }
           else if (curr->left == nullptr) {
               Node<T>* temp = curr->right;
               delete curr;
               return temp;
           }
           else {
               Node<T>* succ = findMinNode(curr->right);
               curr->data = succ->data;
               curr->right = remove(curr->right, succ->data);
           }
       }
       if (data < curr->data) curr->left = remove(curr->left, data);
       else curr->right = remove(curr->right, data);
       return curr;
    }
    // Node<T>* remove(Node<T>* curr, const T& data) {
    //     if (curr == nullptr) return nullptr;
    //     if (data == curr->data) {
    //         if (curr->left == nullptr && curr->right == nullptr) {
    //             delete curr;
    //             return nullptr;
    //         }
    //         else if (curr->right != nullptr) {
    //             Node<T>* temp = findMinNode(curr->right);   // successor
    //             curr->data = temp->data;
    //             curr->right = remove(curr->right, temp->data);
    //         }
    //         else if (curr->left != nullptr) {
    //             Node<T>* temp = findMaxNode(curr->left);    // predecessor
    //             curr->data = temp->data;
    //             curr->left = remove(curr->left, temp->data);
    //         }
    //         return curr;
    //     }
    //     if (data < curr->data) curr->left = remove(curr->left, data);
    //     else curr->right = remove(curr->right, data);
    //     return curr;
    // }

    Node<T>* findMinNode(Node<T>* curr) {
        if (curr == nullptr) return nullptr;
        if (curr->left == nullptr) return curr;
        return findMinNode(curr->left);
    }
    Node<T>* findMaxNode(Node<T>* curr) {
        if (curr == nullptr) return nullptr;
        if (curr->right == nullptr) return curr;
        return findMaxNode(curr->right);
    }
};

template<typename T>
struct BinarySearchTree_iter {
    Node<T>* root;

    //void clear() {          // delete nodes in preorder
    //    std::stack<Node<T>*> S;
    //    S.push(root);
    //    while (!S.empty()) {
    //        auto curr = S.top(); S.pop();
    //        if (curr->left != nullptr) S.push(curr->left);
    //        if (curr->right != nullptr) S.push(curr->right);
    //        delete curr;
    //    }
    //    root = nullptr;
    //}
    void clear() {            // delete nodes in level order
        std::queue<Node<T>*> Q;
        Q.push(root);
        while (!Q.empty()) {
            auto curr = Q.front(); Q.pop();
            if (curr->left != nullptr) Q.push(curr->left);
            if (curr->right != nullptr) Q.push(curr->right);
            delete curr;
        }
        root = nullptr;
    }
    Node<T>* find(const T& data) {
        Node<T>* curr = root;
        while (curr != nullptr) {
            if (data == curr->data) return curr;    // 중복 불가
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
        if (curr == nullptr) return;

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
                succ_prev = succ;
                succ = succ->left;
            }
            curr->data = succ->data;
            if (succ_prev->left == succ) succ_prev->left = succ->right;
            else succ_prev->right = succ->right;
            curr = succ;    // delete succ
        }
        delete curr;
    }

    Node<T>* findMinNode(Node<T>* curr) {
        if (curr == nullptr) return nullptr;
        while (curr->left != nullptr) curr = curr->left;
        return curr;
    }
    Node<T>* findMaxNode(Node<T>* curr) {
        if (curr == nullptr) return nullptr;
        while (curr->right != nullptr) curr = curr->right;
        return curr;
    }
};