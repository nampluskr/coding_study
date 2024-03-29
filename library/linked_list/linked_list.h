#pragma once

#include "node.h"

template<typename T>
struct LinkedListIterative{
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
            ptr = ptr->next;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* ptr = head;
        while (ptr != nullptr) {
            if (ptr->data == data) { return; }
            prev = ptr;
            ptr = ptr->next;
        }
        Node<T>* node = new Node<T>{ data, nullptr };
        if (prev != nullptr) { prev->next = node; }
        else { head = node; }
    }
    void remove(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* ptr = head;
        while (ptr != nullptr) {
            if (ptr->data == data) { break; }
            prev = ptr;
            ptr = ptr->next;
        }
        if (ptr == nullptr) { return; }

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

    Iterator<T> begin() { return Iterator<T>(head); }
    Iterator<T> end() { return Iterator<T>(nullptr); }
};

template<typename T>
struct LinkedListRecursive {
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
        return find(ptr->next, data);
    }
    Node<T>* insert(Node<T>* ptr, const T& data) {
        if (ptr == nullptr) { 
            Node<T>* node = new Node<T>{ data, nullptr };
            return node;
        }
        if (ptr->data == data) { return ptr; }
        ptr->next = insert(ptr->next, data);
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
        ptr->next = remove(ptr->next, data);
        return ptr;
    }

    Iterator<T> begin() { return Iterator<T>(head); }
    Iterator<T> end() { return Iterator<T>(nullptr); }
};