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

template<typename T>
struct OrderedLinkedList {
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
Node<T>* OrderedLinkedList<T>::find(const T& data) {
    Node<T>* ptr = head;
    while (ptr != nullptr) {
        if (ptr->data == data) { return ptr; }
        if (data < ptr->data) { ptr = ptr->next; }
        else { break; }
    }
    return nullptr;
}

template<typename T>
void OrderedLinkedList<T>::insert(const T& data) {
    Node<T>* parent = nullptr;
    Node<T>* ptr = head;
    while (ptr != nullptr) {
        if (ptr->data == data) { return; }
        if (data < ptr->data) { 
            parent = ptr;
            ptr = ptr->next;
        }
        else { break; }
    }
    Node<T>* node = new Node<T>{ data, nullptr };
    if (parent != nullptr) {    // parent 와 ptr 사이에 node 삽입
        parent->next = node;
        node->next = ptr;
    }
    else {                      // head 앞에 node 삽입
        node->next = head;
        head = node; 
    }
}

template<typename T>
void OrderedLinkedList<T>::remove(const T& data) {
    Node<T>* parent = nullptr;
    Node<T>* ptr = head;
    while (ptr != nullptr) {
        if (ptr->data == data) { break; }
        if (data < ptr->data) {
            parent = ptr;
            ptr = ptr->next;
        }
        else { break; }
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
Node<T>* OrderedLinkedList<T>::find(Node<T>* ptr, const T& data) {
    if (ptr == nullptr) { return nullptr; }
    if (ptr->data == data) { return ptr; }
    if (data < ptr->data) { return find(ptr->next, data); }
    return nullptr;
}

template<typename T>
Node<T>* OrderedLinkedList<T>::insert(Node<T>* ptr, const T& data) {
    if (ptr == nullptr) { return new_node<T>(data, nullptr); }
    if (ptr->data == data) { return ptr; }
    if (data < ptr->data) { ptr->next = insert(ptr->next, data); }
    else if (ptr->data < data) { // ptr 앞에 node 삽입
        Node<T>* node = new_node<T>(data, nullptr);
        node->next = ptr;
        ptr = node;
    }
    return ptr;
}

template<typename T>
Node<T>* OrderedLinkedList<T>::remove(Node<T>* ptr, const T& data) {
    if (ptr == nullptr) { return nullptr; }
    if (ptr->data == data) {
        Node<T>* temp = ptr;
        if (ptr->next == nullptr) { ptr = nullptr; }
        else { ptr = ptr->next; }
        delete temp;
        return ptr;
    }
    if (data < ptr->data) { ptr->next = remove(ptr->next, data); }
    return ptr;
}