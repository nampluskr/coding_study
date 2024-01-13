#pragma once

#include "node.h"

template<typename T>
struct List {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int cnt = 0;

    void clear() { while (!empty()) pop_front(); }
    void push_front(const T& data) {
        Node<T>* node = new Node<T>{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { node->next = head; head = node; }
        cnt++;
    }
    void push_back(const T& data) {
        Node<T>* node = new Node<T>{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
        cnt++;
    }
    void pop_front() {
        Node<T>* temp = head;
        head = head->next;
        delete temp; cnt--;
        if (head == nullptr) { tail = nullptr; }
    }
    void pop_back() {
        Node<T>* prev = nullptr;
        Node<T>* cur = head;
        while (cur->next != nullptr) { prev = cur; cur = cur->next; }
        tail = prev;
        if (prev == nullptr) { head = nullptr; }
        else { prev->next = nullptr; }
        delete cur; cnt--;
    }
    bool empty() { return head == nullptr; }
    T front() { return head->data; }
    T back() { return tail->data; }
    int size() { return cnt; }
};

template<typename T>
struct Stack {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int cnt = 0;

    void clear() { while (!empty()) pop(); }
    void push(const T& data) {    // push_front()
        Node<T>* node = new Node<T>{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { node->next = head; head = node; }
        cnt++;
    }
    void pop() {                // pop_front()
        Node<T>* temp = head;
        head = head->next;
        delete temp; cnt--;
        if (head == nullptr) { tail = nullptr; }
    }
    bool empty() { return head == nullptr; }
    T top() { return head->data; }
    int size() { return cnt; }
};

template<typename T>
struct Queue {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int cnt = 0;

    void clear() { while (!empty()) pop(); }
    void push(const T& data) {    // push_back()
        Node<T>* node = new Node<T>{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
        cnt++;
    }
    void pop() {                // pop_front()
        Node<T>* temp = head;
        head = head->next;
        delete temp; cnt--;
        if (head == nullptr) { tail = nullptr; }
    }
    bool empty() { return head == nullptr; }
    T front() { return head->data; }
    int size() { return cnt; }
};