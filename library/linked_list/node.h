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