#pragma once

template<typename T>
struct LinkedListIterDummy {
    struct Node {
        T data;
        Node* next = nullptr;
    };
    Node* head = new Node{ {}, nullptr };

    ~LinkedListIterDummy() {
        delete head;
        head = nullptr;
    }
    void clear() {
        while (head->next != nullptr) {
            Node* temp = head->next;
            head->next = head->next->next;
            delete temp;
        }
    }
    void insert(const T& data) {
        Node* prev = head;
        Node* cur = head->next;
        while (cur != nullptr) {
            if (cur->data == data) return;
            prev = cur;
            cur = cur->next;
        }
        // cur == nullptr
        prev->next = new Node{ data, nullptr};
    }
    Node* find(const T& data) {
        Node* cur = head->next;
        while (cur != nullptr) {
            if (cur->data == data) return cur;
            cur = cur->next;
        }
        return nullptr;
    }
    void erase(const T& data) {
        Node* prev = head;
        Node* cur = head->next;
        while (cur != nullptr) {
            if (cur->data == data) break;
            prev = cur;
            cur = cur->next;
        }
        if (cur == nullptr) return;
        // cur->data == data
        prev->next = cur->next;
        delete cur;
    }
};