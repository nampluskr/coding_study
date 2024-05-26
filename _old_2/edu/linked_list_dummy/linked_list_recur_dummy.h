#pragma once

template<typename T>
struct LinkedListRecurDummy {
    struct Node {
        T data;
        Node* next = nullptr;
    };
    Node* head = new Node{ {}, nullptr };

    ~LinkedListRecurDummy() {
        delete head;
        head = nullptr;
    }
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
            cur = cur->next;
            delete temp;
            return cur;
        }
        cur->next = eraseRecur(cur->next, data);
        return cur;
    }

    // Implementations
    void clear() { head->next = clearRecur(head->next); }
    void insert(const T& data) { head->next = insertRecur(head->next, data); }
    Node* find(const T& data)  { return findRecur(head->next, data); }
    void erase(const T& data) { head->next = eraseRecur(head->next, data); }

};