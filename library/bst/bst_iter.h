#pragma once

#include "node.h"

template<typename T>
struct BinarySearchTree_iter {
    Node<T>* root;

    Node<T>* find(const T& data) {
        Node<T>& ptr = root;
        while (ptr != nullptr) {
            if (data == ptr->data) return ptr;

            if (data < ptr->data) ptr = ptr->left;
            else ptr = ptr->right;
        }
        return nullptr;     // not found!
    }
    void insert(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* ptr = root;
        while (ptr != nullptr) {
            if (data == ptr->data) return;

            prev = ptr;
            if (data < ptr->data) ptr = ptr->left;
            else ptr = ptr->right;
        }

        // (ptr == nullptr): not found => insert data into prev node
        Node<T>* node = new Node<T>{ data, nullptr, nullptr };
        if (prev == nullptr) root = node;
        else if (data < prev->data) prev->left = node;
        else prev->right = node;
    }
    void remove(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* ptr = root;
        while (ptr != nullptr) {
            if (data == ptr->data) break;

            prev = ptr;
            if (data < ptr->data) ptr = ptr->left;
            else ptr = ptr->right;
        }
        if (ptr == nullptr) return; // not found!

        // (data == ptr->data): Found! succ => ptr and delete ptr
        if (ptr->left == nullptr && ptr->right == nullptr) {
            if (prev == nullptr) root = nullptr;
            else if (prev->left == ptr) prev->left = nullptr;
            else prev->right = nullptr;
        }
        else if (ptr->right == nullptr) {
            if (prev == nullptr) root = ptr->left;
            else if (prev->left == ptr) prev->left = ptr->left;
            else prev->right = ptr->left;
        }
        else if (ptr->left == nullptr) {
            if (prev == nullptr) root = ptr->right;
            else if (prev->left == ptr) prev->left = ptr->right;
            else prev->right = ptr->right;
        }
        else {
            Node<T>* succ_prev = ptr;
            Node<T>* succ = ptr->right;
            while (succ->left != nullptr) {
                succ_prev = ptr;
                succ = succ->left;
            }
            ptr->data = succ->data;
            if (succ_prev->left == succ)
                succ_prev->left = succ->right;
            else
                succ_prev->right = succ->right;
            ptr = succ;
        }
        delete ptr;
    }

};