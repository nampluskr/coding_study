#pragma once

template<typename T>
struct Node {
    T data;
    Node* left = nullptr;
    Node* right = nullptr;
};