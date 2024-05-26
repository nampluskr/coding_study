#pragma once

template<typename T>
struct LinkedListRecur {
    struct Node {
        T data;
        Node* next = nullptr;
    };
    Node* head = nullptr;

    Node* clearRecur(Node* cur) {
        if (cur == nullptr) return nullptr;
        cur->next = clearRecur(cur->next);
        delete cur;
        return nullptr;
    }
    Node* insertRecur(Node* cur, const T& data) {
        if (cur == nullptr) return new Node{ data, nullptr };
        if (cur->data == data) return cur;
        cur->next = insertRecur(cur->next, data);
        return cur;
    }
    Node* findRecur(Node* cur, const T& data) {
        if (cur == nullptr) return nullptr;
        if (cur->data == data) return cur;
        return findRecur(cur->next, data);
    }
    Node* eraseRecur(Node* cur, const T& data) {
        if (cur == nullptr) return nullptr;
        if (cur->data == data) {
            Node* temp = cur;
            if (cur->next == nullptr) cur = nullptr;
            else cur = cur->next;
            delete temp;
            return cur;
        }
        cur->next = eraseRecur(cur->next, data);
        return cur;
    }

    // Implementation
    void clear() { head = clearRecur(head); }
    void insert(const T& data) { head = insertRecur(head, data); }
    Node* find(const T& data) { return findRecur(head, data); }
    void erase(const T& data) { head = eraseRecur(head, data); }

};