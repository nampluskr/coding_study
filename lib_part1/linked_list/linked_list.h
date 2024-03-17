#pragma once
#include <queue>

template<typename T>
struct Node {
    T data;
    Node* next = nullptr;
};

template<typename T>
struct LinkedList_recur {
    Node<T>* head;

    void clear() { head = clear(head); }
    Node<T>* find(const T& data) { return find(head, data); }
    void insert(const T& data) { head = insert(head, data); }
    void remove(const T& data) { head = remove(head, data); }

    Node<T>* clear(Node<T>* curr) {
        if (curr == nullptr) return nullptr;
        curr->next = clear(curr->next);
        delete curr;
        return nullptr;
    }
    Node<T>* find(Node<T>* curr, const T& data) {
        if (curr == nullptr) return nullptr;
        if (data == curr->data) return curr;
        return find(curr->next, data);
    }
    Node<T>* insert(Node<T>* curr, const T& data) {
        if (curr == nullptr) return new Node<int>{ data, nullptr };
        //if (data == curr->data) return curr;  // 중복 불가
        curr->next = insert(curr->next, data);
        return curr;
    }
    Node<T>* remove(Node<T>* curr, const T& data) {
        if (curr == nullptr) return nullptr;
        if (data == curr->data) {
            auto temp = curr;
            curr = curr->next;
            delete temp;
            return curr;
        }
        curr->next = remove(curr->next, data);
        return curr;
    }
};

template<typename T>
struct LinkedList_iter {
    Node<T>* head;

    void clear() {
        if (head == nullptr) return;
        std::queue<Node<int>*> Q;
        Q.push(head);
        while (!Q.empty()) {
            auto curr = Q.front(); Q.pop();
            if (curr->next != nullptr) Q.push(curr->next);
            delete curr;
        }
        head = nullptr;
    }
    Node<T>* find(const T& data) {
        Node<T>* curr = head;
        while (curr != nullptr) {
            if (data == curr->data) return curr;
            curr = curr->next;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr != nullptr) {
            //if (data == curr->data) return; // 중복 불가
            prev = curr;
            curr = curr->next;
        }
        Node<T>* node = new Node<int>{ data, curr };
        if (prev == nullptr) head = node;
        else prev->next = node;
    }
    void remove(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr != nullptr) {
            if (data == curr->data) break;
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) return;

        if (prev == nullptr) head = curr->next;
        else prev->next = curr->next;
        delete curr;
    }
};

template<typename T>
struct OrderedLinkedList_recur {
    Node<int>* head;

    void clear() { head = clear(head); }
    Node<T>* find(const T& data) { return find(head, data); }
    void insert(const T& data) { head = insert(head, data); }
    void remove(const T& data) { head = remove(head, data); }

    Node<T>* clear(Node<T>* curr) {
        if (curr == nullptr) return nullptr;
        curr->next = clear(curr->next);
        delete curr;
        return nullptr;
    }
    Node<T>* find(Node<T>* curr, const T& data) {
        if (curr == nullptr) return nullptr;
        if (data == curr->data) return curr;
        if (data < curr->data) return find(curr->next, data);
        else return nullptr;
    }
    Node<T>* insert(Node<T>* curr, const T& data) {
        if (curr == nullptr) return new Node<T>{ data, nullptr };
        if (data == curr->data) return curr;  // 중복 불가
        if (data < curr->data) curr->next = insert(curr->next, data);
        else curr = new Node<T>{ data, curr };
        return curr;
    }
    Node<T>* remove(Node<T>* curr, const T& data) {
        if (curr == nullptr) return nullptr;
        if (data == curr->data) {
            Node<T>* temp = curr;
            curr = curr->next;
            delete temp;
            return curr;
        }
        if (data < curr->data) curr->next = remove(curr->next, data);
        else curr = nullptr;
        return curr;
    }
};

template<typename T>
struct OrderedLinkedList_iter{
    Node<int>* head;

    void clear() {
        if (head == nullptr) return;
        std::queue<Node<int>*> Q;
        Q.push(head);
        while (!Q.empty()) {
            auto curr = Q.front(); Q.pop();
            if (curr->next != nullptr) Q.push(curr->next);
            delete curr;
        }
        head = nullptr;
    }
    Node<T>* find(const T& data) { 
        Node<T>* curr = head;
        while (curr != nullptr) {
            if (data == curr->data) return curr;
            if (data < curr->data) curr = curr->next;
            else return nullptr;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr != nullptr) {
            if (data == curr->data) return;
            if (data < curr->data) { 
                prev = curr;
                curr = curr->next;
            }
            else break;
        }
        Node<T>* node = new Node<T>{ data, curr };
        if (prev == nullptr) head = node;
        else prev->next = node;
    }
    void remove(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr != nullptr) {
            if (data == curr->data) break;
            if (data < curr->data) {
                prev = curr;
                curr = curr->next;
            }
            else return;
        }
        if (prev == nullptr) head = curr->next;
        else prev->next = curr->next;
        delete curr;
    }
};