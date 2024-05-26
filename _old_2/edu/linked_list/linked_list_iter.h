#pragma once 

template<typename T>
struct LinkedListIter {
    struct Node {
        T data;
        Node* next = nullptr;
    };
    Node* head = nullptr;

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void insert(const T& data) {
        Node* prev = nullptr;
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data == data) return;
            prev = cur;
            cur = cur->next;
        }
        // cur == nullptr
        Node* node = new Node{ data, nullptr };
        if (prev == nullptr) head = node;
        else prev->next = node;
    }
    Node* find(const T& data) {
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data == data) return cur;
            cur = cur->next;
        }
        return nullptr;
    }
    void erase(const T& data) {
        Node* prev = nullptr;
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data == data) break;
            prev = cur;
            cur = cur->next;
        }
        if (cur == nullptr) return;
        // cur->data == data
        if (prev == nullptr) head = cur->next;
        else prev->next = cur->next;
        delete cur;
    }
};