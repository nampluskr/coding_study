﻿#pragma once

template<typename T>
struct Node {
    T data;
    Node* left = nullptr;
    Node* right = nullptr;
};

template<typename T>
Node<T>* new_node(const T& data, Node<T>* left, Node<T>* right) {
    Node<T>* node = new Node<T>{ data, left, right };
    return node;
}

template<typename T>
struct BinarySearchTree {
    Node<T>* root = nullptr;

    // iterative
    Node<T>* find(const T& data);
    void insert(const T& data);
    void remove(const T& data);

    // recursive
    Node<T>* find(Node<T>* ptr, const T& data);
    Node<T>* insert(Node<T>* ptr, const T& data);
    Node<T>* remove(Node<T>* ptr, const T& data);
    Node<T>* find_min(Node<T>* ptr);
};

// iterative
template<typename T>
Node<T>* BinarySearchTree<T>::find(const T& data) {
    Node<T>* ptr = root;
    while (ptr != nullptr) {
        if (ptr->data == data) { return ptr; }
        if (data < ptr->data) { ptr = ptr->left; }
        else if (ptr->data < data) { ptr = ptr->right; }
    }
    return nullptr;
}

template<typename T>
void BinarySearchTree<T>::insert(const T& data) {
    Node<T>* parent = nullptr;
    Node<T>* ptr = root;
    while (ptr != nullptr) {
        if (ptr->data == data) { return; }
        parent = ptr;
        if (data < ptr->data) { ptr = ptr->left; }
        else if (ptr->data < data) { ptr = ptr->right; }
    }
    // 노드 데이터 찾기 실패 (parent 노드에 삽입)
    Node<T>* node = new Node<T>{ data, nullptr, nullptr };
    if (parent != nullptr) {
        if (data < parent->data) { parent->left = node; }
        else if (parent->data < data) { parent->right = node; }
    }
    else { root = node; }    // 루트 노드에 삽입
}

template<typename T>
void BinarySearchTree<T>::remove(const T& data) {
    Node<T>* parent = nullptr;
    Node<T>* ptr = root;
    while (ptr != nullptr) {
        if (ptr->data == data) { break; }
        parent = ptr;
        if (data < ptr->data) { ptr = ptr->left; }
        else if (ptr->data < data) { ptr = ptr->right; }
    }
    if (ptr == nullptr) { return; }

    // 노드 데이터 찾기 성공 -> ptr 노드 삭제 -> parent 노드와 ptr 노드 연결
    if (!ptr->left && !ptr->right) {        // ptr 노드 차수 0
        if (parent == nullptr) { root = nullptr; }
        else {
            if (parent->left == ptr) { parent->left = nullptr; }
            else { parent->right = nullptr; }
        }
    }
    else if (!ptr->left || !ptr->right) {   // ptr 노드 차수 1
        Node<T>* child = (ptr->left) ? ptr->left : ptr->right;
        if (parent == nullptr) { root = child; }
        else {
            if (parent->left == ptr) { parent->left = child; }
            else { parent->right = child; }
        }
    }
    else { // succ: ptr 오른쪽 서브트리에서 최소값 노드
        Node<T>* succ_parent = ptr;
        Node<T>* succ = ptr->right;
        while (succ->left != nullptr) {
            succ_parent = succ;
            succ = succ->left;
        }
        ptr->data = succ->data;
        if (succ_parent->left == succ) { succ_parent->left = succ->right; }
        else { succ_parent->right = succ->right; }
        ptr = succ;
    }
    delete ptr;
}

// recursive
template<typename T>
Node<T>* BinarySearchTree<T>::find(Node<T>* ptr, const T& data) {
    if (ptr == nullptr) { return nullptr; }
    
    if (ptr->data == data) { return ptr; }
    
    if (data < ptr->data) { return find(ptr->left, data); }
    else if (ptr->data < data) { return find(ptr->right, data); }
}

template<typename T>
Node<T>* BinarySearchTree<T>::insert(Node<T>* ptr, const T& data) {
    if (ptr == nullptr) { return new_node<T>(data, nullptr, nullptr); }
    
    if (ptr->data == data) { return ptr; }
    
    if (data < ptr->data) { ptr->left = insert(ptr->left, data); }
    else if (ptr->data < data) { ptr->right = insert(ptr->right, data); }
    return ptr;
}

template<typename T>
Node<T>* BinarySearchTree<T>::find_min(Node<T>* ptr) {
    if (ptr->left == nullptr) { return ptr; }
    return find_min(ptr->left);
}

// https://srdeveloper.tistory.com/26?utm_source=pocket_saves
template<typename T>
Node<T>* BinarySearchTree<T>::remove(Node<T>* ptr, const T& data) {
    if (ptr == nullptr) { return nullptr; }
    if (ptr->data == data) {
        Node<T>* temp = ptr;
        if (!ptr->left && !ptr->right) { ptr = nullptr; }
        else if (ptr->left && !ptr->right) { ptr = ptr->left; }
        else if (!ptr->left && ptr->right) { ptr = ptr->right; }
        else {
            Node<T>* min_node = find_min(ptr->right);
            ptr->right = ptr->right->right;
            min_node->left = ptr->left;
            min_node->right = ptr->right;
            ptr = min_node;
        }
        delete temp;
        return ptr;
    }
    if (data < ptr->data) { ptr->left = remove(ptr->left, data); }
    else if (ptr->data < data) { ptr->right = remove(ptr->right, data); }
    return ptr;
}