#pragma once

#include "node.h"

template<typename T>
struct OrderedLinkedListIterative {
    Node<T>* head = nullptr;

    void clear() {
        Node<T>* cur = head;
        while (cur != nullptr) {
            Node<T>* temp = cur;
            cur = cur->next;
            delete temp;
        }
        head = nullptr;
    }
    Node<T>* find(const T& data) {
        Node<T>* ptr = head;
        while (ptr != nullptr) {
            if (ptr->data == data) { return ptr; }
            if (data < ptr->data) { ptr = ptr->next; }
            else { break; }
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* ptr = head;
        while (ptr != nullptr) {
            if (ptr->data == data) { return; }
            if (data < ptr->data) { prev = ptr; ptr = ptr->next; }
            else { break; }
        }
        Node<T>* node = new Node<T>{ data, nullptr };
        if (prev != nullptr) { prev->next = node; node->next = ptr; }
        else { node->next = head; head = node; }
    }
    void remove(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* ptr = head;
        while (ptr != nullptr) {
            if (ptr->data == data) { break; }
            if (data < ptr->data) { prev = ptr; ptr = ptr->next; }
            else { break; }
        }
        if (ptr == nullptr) { return; }
        if (ptr->data != data) { return; }

        if (ptr->next == nullptr) {
            if (prev == nullptr) { head = nullptr; }
            else { prev->next = nullptr; }
        }
        else {
            if (prev == nullptr) { head = ptr->next; }
            else { prev->next = ptr->next; }
        }
        delete ptr;
    }
};

template<typename T>
struct OrderedLinkedListRecursive {
    Node<T>* head = nullptr;

    Node<T>* clear(Node<T>* ptr) {
        if (ptr == nullptr) { return nullptr; }
        ptr->next = clear(ptr->next);
        delete ptr;
        return nullptr;
    }
    Node<T>* find(Node<T>* ptr, const T& data) {
        if (ptr == nullptr) { return nullptr; }
        if (ptr->data == data) { return ptr; }
        if (data < ptr->data) { return find(ptr->next, data); }
        return nullptr;
    }
    Node<T>* insert(Node<T>* ptr, const T& data) {
        if (ptr == nullptr) { 
            Node<T>* node = new Node<T>{ data, nullptr };
            return node;
        }
        if (ptr->data == data) { return ptr; }
        if (data < ptr->data) { ptr->next = insert(ptr->next, data); }
        else if (ptr->data < data) {
            Node<T>* node = new Node<T>{ data, nullptr };
            node->next = ptr;
            ptr = node;
        }
        return ptr;
    }
    Node<T>* remove(Node<T>* ptr, const T& data) {
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
};