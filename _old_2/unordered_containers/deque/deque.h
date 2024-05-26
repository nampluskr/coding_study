#pragma once

template<typename T>
struct Deque {
    struct Node {
        T data;
        Node* next = nullptr;
    };
    Node *head = nullptr;
    Node *tail = nullptr;

    void clear() { while (empty()) pop_front(); }
    void push_front(const T& data) {
        Node* node = new Node{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { node->next = head; head = node; }
    }
    void push_back(const T& data) {
        Node* node = new Node{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
    }
    void pop_front() {
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) tail = nullptr;
    }
    void pop_back() {}  // O(N)
    bool empty() { return head == nullptr; }
    T front() { return head->data; }
    T back() { return tail->data; }
};