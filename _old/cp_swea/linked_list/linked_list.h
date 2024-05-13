#pragma once
#include <iostream>
using namespace std;


template<typename T>
struct LinkedList{
    struct Node {
        T data;
        Node* next;
    };
    Node* head = nullptr;
    Node* tail = nullptr;

    void clear() { while (!empty()) pop_front(); }
    void push_back(const T& data) {
        Node* node = new Node{ data, nullptr };
        if (head == nullptr) { head = tail = node; }
        else { tail->next = node; tail = node; }
    }
    void pop_front() {
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) { tail = nullptr; }
    }
    bool empty() { return head == nullptr; }
    T front() { return head->data; }
    T back() { return tail->data; }
    Node* find(const T& data) {
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data == data) return cur;
            cur = cur->next;
        }
        return nullptr;
    }
    void print() {
        Node* cur = head;
        while (cur != nullptr) {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};
