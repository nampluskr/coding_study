#pragma once

#include <cstdio>

template<typename T>
struct Node {
    T data;
	Node* next;
};

template<typename T>
struct Iterator {
    Node<T>* ptr;

    Iterator(Node<T>* ptr = nullptr) { this->ptr = ptr; }
    bool operator!=(const Iterator& iter) const { return ptr != iter.ptr; }
    bool operator==(const Iterator& iter) const { return ptr == iter.ptr; }
    T& operator*() { return ptr->data; }                        // *iter
    Iterator& operator++() { ptr = ptr->next; return *this; }   // ++iter
    Iterator operator++(int) { Iterator iter = *this; ++(*this);  return iter; }
};

void preorder(Node<int>* ptr);
void postorder(Node<int>* ptr);
void postorder2(Node<int>* ptr);    // stack
void inorder(Node<int>* ptr);

// LinkedList 구조체 내부에 Node, Iterator 구조체 포함 가능
template<typename T>
struct LinkedList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;

    void clear() { while (head != nullptr) pop_front(); }
    void push_back(const T& data) {
        Node<T>* node = new Node<T>{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
    }
    void pop_front() {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) { tail = nullptr; }
    }

    Iterator<T> begin() { return Iterator<T>(head); }
    Iterator<T> end() { return Iterator<T>(nullptr); }
};