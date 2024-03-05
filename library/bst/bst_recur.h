#pragma once

#include "node.h"

template<typename T>
struct BinarySearchTree_recur {
    Node<T>* root;

    Node<T>* find(const T& data) { return find(root, data); }
    void insert(const T& data) { root = insert(root, data); }
    void remove(const T& data) { root = remove(root, data); }

    Node<T>* find(Node<T>* ptr, const T& data) {
        if (ptr == nullptr) return nullptr; // not found!

        if (data == ptr->data) return ptr;
        if (data < ptr->data) return find(ptr->left, data);
        else return find(ptr->right, data);
    }
    Node<T>* insert(Node<T>* ptr, const T& data) {
        if (ptr == nullptr) return new Node<T>{ data, nullptr, nullptr };

        if (data == ptr->data) return ptr;  // not found!
        if (data < ptr->data) ptr->left = insert(ptr->left, data);
        else ptr->right = insert(ptr->right, data);
        return ptr;
    }
    Node<T>* find_min(Node<T>* ptr) {
        if (ptr->left == nullptr) return ptr;
        return find_min(ptr->left);
    }
    Node<T>* find_max(Node<T>* ptr) {
        if (ptr->right == nullptr) return ptr;
        return find_max(ptr->right);
    }

    // https://simplesnippets.tech/what-is-binary-search-tree-bst-with-full-code-dsa/
    //Node<T>* remove(Node<T>* ptr, const T& data) {
    //    if (ptr == nullptr) return nullptr; // not found!

    //    if (data == ptr->data) {
    //        if (ptr->left == nullptr && ptr->right == nullptr) {
    //            delete ptr;
    //            return nullptr;
    //        }
    //        else if (ptr->right == nullptr) {
    //            Node<T>* temp = ptr->left;
    //            delete ptr;
    //            return temp;
    //        }
    //        else if (ptr->left == nullptr) {
    //            Node<T>* temp = ptr->right;
    //            delete ptr;
    //            return temp;
    //        }
    //        else { // succ => ptr and delete ptr
    //            Node<T>* succ = find_min(ptr->right);
    //            ptr->data = succ->data;
    //            ptr->right = remove(ptr->right, succ->data);
    //        }
    //    }

    //    if (data < ptr->data) ptr->left = remove(ptr->left, data);
    //    else ptr->right = remove(ptr->right, data);
    //    return ptr;
    //}

    // https://srdeveloper.tistory.com/26
    Node<T>* remove(Node<T>* ptr, const T& data) {
        if (ptr == nullptr) return nullptr; // not found!

        if (data == ptr->data) {
            Node<T>* temp = ptr;
            if (ptr->left == nullptr && ptr->right == nullptr)
                ptr = nullptr;
            else if (ptr->right == nullptr)
                ptr = ptr->left;
            else if (ptr->left == nullptr)
                ptr = ptr->right;
            else {
                Node<T>* succ = find_min(ptr->right);
                ptr->right = ptr->right->right;
                succ->left = ptr->left;
                succ->right = ptr->right;
                ptr = succ;
            }
            delete temp;
            return ptr;
        }

        if (data < ptr->data) ptr->left = remove(ptr->left, data);
        else ptr->right = remove(ptr->right, data);
        return ptr;
    }

    // https://www.geeksforgeeks.org/deletion-in-binary-search-tree/
    //Node<T>* remove(Node<T>* ptr, const T& data) {
    //    if (ptr == nullptr) return nullptr; // not found!

    //    if (data == ptr->data) {
    //        if (ptr->left == nullptr) {
    //            Node<T>* temp = ptr->right;
    //            delete ptr;
    //            return temp;
    //        }
    //        else if (ptr->right == nullptr) {
    //            Node<T>* temp = ptr->left;
    //            delete ptr;
    //            return temp;
    //        }
    //        else {
    //            Node<T>* succ_prev = ptr;
    //            Node<T>* succ = ptr->right;
    //            while (succ->left != nullptr) {
    //                succ_prev = succ;
    //                succ = succ->left;
    //            }
    //            ptr->data = succ->data;
    //            if (succ_prev->left == succ) // (succ_prev != ptr)
    //                succ_prev->left = succ->right;
    //            else
    //                succ_prev->right = succ->right;

    //            delete succ;
    //            return ptr;
    //        }
    //    }

    //    if (data < ptr->data) ptr->left = remove(ptr->left, data);
    //    else ptr->right = remove(ptr->right, data);
    //    return ptr;
    //}

    // https://www.interviewbit.com/blog/delete-node-from-binary-search-tree/
    //Node<T>* remove(Node<T>* ptr, int data) {
    //    if (ptr == nullptr) return nullptr;

    //    if (data == ptr->data){
    //        if (ptr->left == nullptr && ptr->right == nullptr){
    //            delete ptr;
    //            return nullptr;
    //        }
    //        else if (ptr->right != nullptr) {
    //            Node<T>* succ = find_min(ptr->right);   // successor
    //            ptr->data = succ->data;
    //            ptr->right = remove(ptr->right, succ->data);
    //        }
    //        else {  // (ptr->left != nullptr)
    //            Node<T>* pred = find_max(ptr->left);    // predecessor
    //            ptr->data = pred->data;
    //            ptr->left = remove(ptr->left, pred->data);
    //        }
    //        return ptr;
    //    }

    //    if (data < ptr->data) ptr->left = remove(ptr->left, data);
    //    else ptr->right = remove(ptr->right, data);
    //    return ptr;
    //}
};