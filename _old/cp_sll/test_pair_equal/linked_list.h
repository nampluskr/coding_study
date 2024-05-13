#pragma once

// (SLL with head only)
template<typename T>
struct LinkedList {
    struct Node {
        T data;
        Node* next = nullptr;
    };
    Node* head = nullptr;

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete head;
        }
    }
    void insert(const T& data) {
        Node* node = new Node{ data, nullptr };
        if (head != nullptr ) node->next = head;
        head = node;
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
        if (cur == nullptr) return;     // Not found

        if (prev == nullptr) head = cur->next;
        else prev->next = cur->next;
        delete cur;
    }
};