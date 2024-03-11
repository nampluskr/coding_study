#pragma once

#include "node.h"

template<typename T>
struct UnorderedLinkedList_iter {
    Node<T>* head;

    Node<T>* find(const T& data) {
        Node<T>* ptr = head;
        while (ptr != nullptr) {
            if (data == ptr->data) return ptr;
            ptr = ptr->next;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* ptr = head;
        while (ptr != nullptr) {
            if (data == ptr->data) return;
            prev = ptr;
            ptr = ptr->next;
        }

        // (ptr ==  nullptr)
        Node<T>* node = new Node<T>{ data, nullptr };
        if (prev == nullptr)
            head = node;
        else
            prev->next = node;
    }
    void remove(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* ptr = head;
        while (ptr != nullptr) {
            if (data == ptr->data) break;
            prev = ptr;
            ptr = ptr->next;
        }
        if (ptr == nullptr) return;

        // (data == ptr->data)
        Node<T>* temp = ptr;
        if (prev == nullptr)
            head = ptr->next;
        else
            prev->next = ptr->next;
        delete temp;
    }
};