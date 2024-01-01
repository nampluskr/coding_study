#pragma once

template<typename T>
struct Node {
    T data;
    Node* next = nullptr;
};

template<typename T>
struct LinkedList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;

    void clear() { while (!empty()) pop_front(); }
    void push_front(const T& data) {
        Node<T>* node = new Node<T>{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { node->next = head; head = node; }
    }
    void push_back(const T& data) {
        Node<T>* node = new Node<T>{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
    }
    void pop_front(const T& data) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) { tail = nullptr; }
    }
    bool empty() { return head == nullptr; }
    T top() { return head->data; }
    T back() { return tail->data; }
};

template<typename T>
struct Stack {
    Node<T>* head = nullptr;

    void clear() { while (!empty()) pop(); }
    void push(const T& data) {  // push_front()
        Node<T>* node = new Node<T>{ data, nullptr };
        if (head == nullptr) { head = node; }
        else { node->next = head; head = node; }
    }
    void pop(const T& data) {   // pop_front()
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    bool empty() { return head == nullptr; }
    T top() { return head->data; }
};

template<typename T>
struct Queue {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;

    void clear() { while (!empty()) pop(); }
    void push(const T& data) {  // push_back()
        Node<T>* node = new Node<T>{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
    }
    void pop(const T& data) {   // pop_front()
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) { tail = nullptr; }
    }
    bool empty() { return head == nullptr; }
    T front() { return head->data; }
};

template<typename T, int max_size>
struct ListArray {
    T arr[max_size * 2];
    int head = max_size - 1, tail = max_size - 1, arrSize = 0;

    void clear() { head = tail = max_size - 1; arrSize = 0; }
    void push_front(const T& data) {
        if (empty()) { tail--; }
        arr[--head] = data; arrSize++;
    }
    void push_back(const T& data) {
        if (empty()) { head++; }
        arr[++tail] = data; arrSize++;
    }
    void pop_front() {
        tail--; arrSize--;
        if (empty()) { clear(); }
    }
    void pop_back() {
        head++; arrSize--;
        if (empty()) { clear(); }
    }
    bool empty() { return arrSize == 0; }
    T front() { return arr[head]; }
    T back() { return arr[tail]; }
    T size() { return arrSize; }
};

template<typename T, int max_size>
struct StackArray {
    T arr[max_size];
    int head = -1, tail = -1;

    void clear() { head = tail = -1; }
    void push(const T& data) {  // push_back()
        if (tail == max_size - 1) return;
        if (head == -1) { head = 0; }
        arr[++tail] = data;
    }
    void pop() {                // pop_back()
        tail--;
        if (tail < head) { head = tail = -1; }
    }
    bool empty() { return head == -1; }
    T top() { return arr[tail]; }
};

template<typename T, int max_size>
struct QueueArray {
    T arr[max_size];
    int head = -1, tail = -1;

    void clear() { head = tail = -1; }
    void push(const T& data) {  // push_back()
        if (tail == max_size - 1) return;
        if (head == -1) { head = 0; }
        arr[++tail] = data;
    }
    void pop() {                // pop_front()
        head++;
        if (tail < head) { head = tail = -1; }
    }
    bool empty() { return head == -1; }
    T top() { return arr[head]; }
};