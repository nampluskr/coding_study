### [deque.h]

```cpp
#pragma once

#include <cassert>
#define MAX_SIZE    100

// https://www.geeksforgeeks.org/implementation-deque-using-circular-array/
template<typename T>
struct DequeArray {
    T arr[MAX_SIZE];
    int head = -1;
    int tail = 0;
    int cnt = 0;

    void clear() { head = -1; tail = 0; cnt = 0; }
    void push_front(const T& data) {
        if (head == -1) { head = 0; tail = 0; }
        else if (head == 0) { head = MAX_SIZE - 1; }
        else { head--; }
        arr[head] = data;
        cnt++;
    }
    void push_back(const T& data) {
        if (head == -1) { head = 0; tail = 0; }
        else if (tail == MAX_SIZE - 1) { tail = 0; }
        else { tail++; }
        arr[tail] = data;
        cnt++;
    }
    void pop_front() {
        if (head == tail) { head = -1; tail = -1; }
        else if (head == MAX_SIZE - 1) { head = 0; }
        else { head++; }
        cnt--;
    }
    void pop_back() {
        if (head == tail) { head = -1; tail = -1; }
        else if (tail == 0) { tail = MAX_SIZE - 1; }
        else { tail--; }
        cnt--;
    }
    T front() { return arr[head]; }
    T back() { return arr[tail]; }
    bool empty() { return head == -1; }
    bool full() { return (head == 0 && tail == MAX_SIZE - 1) || (head == tail + 1); }
    int size() { return cnt; }
};


// https://www.geeksforgeeks.org/implementation-deque-using-doubly-linked-list/
template<typename T>
struct Node {
    T data;
    Node* prev = nullptr;
    Node* next = nullptr;
};

template<typename T>
struct DequeDLL {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int cnt = 0;

    void clear() {
        tail = nullptr;
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        cnt = 0;
    }
    void push_front(const T& data) {
        Node<T>* node = new Node<T>{ data, nullptr, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { node->next = head; head->prev = node; head = node; }
        cnt++;
    }
    void push_back(const T& data) {
        Node<T>* node = new Node<T>{ data, nullptr, nullptr };
        if (tail == nullptr) { head = tail = node; }
        else { node->prev = tail; tail->next = node; tail = node; }
        cnt++;
    }
    void pop_front() {
        Node<T>* temp = head;
        head = head->next;
        if (head == nullptr) { head = nullptr; }
        else { head->prev = nullptr; }
        delete temp;
        cnt--;
    }
    void pop_back() {
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail == nullptr) { head = nullptr; }
        else { tail->next = nullptr; }
        delete temp;
        cnt--;
    }
    T front() { return head->data; }
    T back() { return tail->data; }
    bool empty() { return head == nullptr; }
    int size() { return cnt; }
};
```

### [deque.cpp]

```cpp
#include "deque.h"
#include <cstdio>

DequeArray<int> Q;
DequeDLL<int> D;

void test_dequeArray(int option) {
    if (option == 0) return;

    Q.clear();
    Q.push_back(1);
    Q.push_back(2);
    Q.push_back(3);
    Q.push_back(4);
    Q.push_back(5);

    while (!Q.empty()) {
        auto cur = Q.front(); Q.pop_front();
        printf(">> front = %d (size = %d)\n", cur, Q.size());
    }

    Q.clear();
    Q.push_back(1);
    Q.push_back(2);
    Q.push_back(3);
    Q.push_back(4);
    Q.push_back(5);

    while (!Q.empty()) {
        auto cur = Q.back(); Q.pop_back();
        printf(">> back = %d (size = %d)\n", cur, Q.size());
    }
}

void test_dequeDLL(int option) {
    if (option == 0) return;

    D.clear();
    D.push_front(1);
    D.push_front(2);
    D.push_front(3);
    D.push_front(4);
    D.push_front(5);

    while (!D.empty()) {
        auto cur = D.front(); D.pop_front();
        printf(">> front = %d (size = %d)\n", cur, D.size());
    }

    D.clear();
    D.push_back(1);
    D.push_back(2);
    D.push_back(3);
    D.push_back(4);
    D.push_back(5);

    while (!D.empty()) {
        auto cur = D.back(); D.pop_back();
        printf(">> back = %d (size = %d)\n", cur, D.size());
    }
}
```

### [main.cpp]

```cpp
#include <cstdio>

extern void test_dequeArray(int);
extern void test_dequeDLL(int);

int main()
{
    printf("\n*** [Deque Using Array]\n");
    test_dequeArray(1);

    printf("\n*** [Deque Using Doubly Linked List]\n");
    test_dequeDLL(1);

    return 0;
}
```
