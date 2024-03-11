#pragma once

template<typename T>
struct Node {
    T data;
    Node* next = nullptr;

    Node(const T& data, Node* next) {
        this->data = data;
        this->next = next;
    }
};