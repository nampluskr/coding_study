#pragma once

#include <cstdio>

template<typename T>
struct Node {
    T data;
    Node* next = nullptr;
};

template<typename T>
Node<T>* new_node(const T& data, Node<T>* next) {
    Node<T>* node = new Node<T>{ data, next };
    return node;
}

void preorder(Node<int>* ptr) {
    if (ptr == nullptr) { return; }
    printf("[%d]->", ptr->data);    // visit the node
    preorder(ptr->next);
}

void postorder(Node<int>* ptr) {
    if (ptr == nullptr) { return; }
    preorder(ptr->next);
    printf("[%d]->", ptr->data);    // visit the node
}

template<typename T>
Node<T>* clear(Node<T>* ptr) {
    if (ptr == nullptr) { return nullptr; }
    ptr->next = clear(ptr->next);
    delete ptr;
    return nullptr;
}

template<typename T>
struct LinkedList {
    Node<T>* head = nullptr;

    // iterative
    Node<T>* find(const T& data);
    void insert(const T& data);
    void remove(const T& data);

    // recursive
    Node<T>* find(Node<T>* ptr, const T& data);
    Node<T>* insert(Node<T>* ptr, const T& data);
    Node<T>* remove(Node<T>* ptr, const T& data);
};

// iterative
template<typename T>
Node<T>* LinkedList<T>::find(const T& data) {
    Node<T>* ptr = head;
    while (ptr != nullptr) {
        if (ptr->data == data) { return ptr; }
        ptr = ptr->next;
    }
    return nullptr;
}

template<typename T>
void LinkedList<T>::insert(const T& data) {
    Node<T>* parent = nullptr;
    Node<T>* ptr = head;
    while (ptr != nullptr) {
        if (ptr->data == data) { return; }
        parent = ptr;
        ptr = ptr->next;
    }
    Node<T>* node = new Node<T>{ data, nullptr };
    if (parent != nullptr) { parent->next = node; }
    else { head = node; }
}

template<typename T>
void LinkedList<T>::remove(const T& data) {
    Node<T>* parent = nullptr;
    Node<T>* ptr = head;
    while (ptr != nullptr) {
        if (ptr->data == data) { break; }
        parent = ptr;
        ptr = ptr->next;
    }
    if (ptr == nullptr) { return; }

    // ptr->data == data (ptr 노드 삭제)
    if (ptr->next == nullptr) {             // ptr 차수 0 (마지막 노드)
        if (parent == nullptr) { head = nullptr; }
        else { parent->next = nullptr; }
    }
    else {        // ptr 차수 1 (중간 노드)
        if (parent == nullptr) { head = ptr->next; }
        else { parent->next = ptr->next; }
    }
    delete ptr;
}

// recursive
template<typename T>
Node<T>* LinkedList<T>::find(Node<T>* ptr, const T& data) {
    if (ptr == nullptr) { return nullptr; }
    if (ptr->data == data) { return ptr; }
    return find(ptr->next, data);
}

template<typename T>
Node<T>* LinkedList<T>::insert(Node<T>* ptr, const T& data) {
    if (ptr == nullptr) { return new_node<T>(data, nullptr); }
    if (ptr->data == data) { return ptr; }
    ptr->next = insert(ptr->next, data);
    return ptr;
}

template<typename T>
Node<T>* LinkedList<T>::remove(Node<T>* ptr, const T& data) {
    if (ptr == nullptr) { return nullptr; }
    if (ptr->data == data) {
        Node<T>* temp = ptr;
        if (ptr->next == nullptr) { ptr = nullptr; }
        else { ptr = ptr->next; }
        delete temp;
        return ptr;
    }
    ptr->next = remove(ptr->next, data);
    return ptr;
}