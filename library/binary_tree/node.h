#pragma once

#include <cstdio>
#include <stack>
#include <queue>


template<typename T>
struct Node {
    T data;
    Node* left = nullptr;
    Node* right = nullptr;
};


template<typename T>
Node<T>* clear(Node<T>* ptr) {
    if (ptr == nullptr) { return nullptr; }
    ptr->left = clear(ptr->left);
    ptr->right = clear(ptr->right);
    delete ptr;
    return nullptr;
}


template<typename T>
Node<T>* new_node(const T& data, Node<T>* left, Node<T>* right) {
    Node<T>* node = new Node<T>{ data, left, right };
    return node;
}


/////////////////////////////////////////////////////////////////////
// Binary Tree Traversals

void preOrder(Node<int>* ptr) {
    if (ptr == nullptr) return;     // base case
    printf("[%d]->", ptr->data);    // visit the node
    preOrder(ptr->left);
    preOrder(ptr->right);
}

void inOrder(Node<int>* ptr) {
    if (ptr == nullptr) return;     // base case
    inOrder(ptr->left);
    printf("[%d]->", ptr->data);    // visit the node
    inOrder(ptr->right);
}

void postOrder(Node<int>* ptr) {
    if (ptr == nullptr) return;     // base case
    postOrder(ptr->left);
    postOrder(ptr->right);
    printf("[%d]->", ptr->data);    // visit the node
}

void preOrder_stack(Node<int>* ptr) {
    std::stack<Node<int>*> S;
    S.push(ptr);

    while (!S.empty()) {
        ptr = S.top(); S.pop();

        printf("[%d]->", ptr->data);    // visit the node
        if (ptr->right != nullptr) { S.push(ptr->right); }
        if (ptr->left != nullptr) { S.push(ptr->left); }
    }
}

void levelOrder(Node<int>* ptr) {
    std::queue<Node<int>*> Q;
    Q.push(ptr);

    while (!Q.empty()) {
        ptr = Q.front(); Q.pop();

        printf("[%d]->", ptr->data);    // visit the node
        if (ptr->left != nullptr) { Q.push(ptr->left); }
        if (ptr->right != nullptr) { Q.push(ptr->right); }
    }
}

/////////////////////////////////////////////////////////////////////
// Binary Tree Operations

const int INF = 0x7fffffff;

inline int sum(int a, int b) { return a + b; }
inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a < b) ? b : a; }

int countNodes(Node<int>* ptr) {
    int cnt = 0;
    if (ptr == nullptr) { return 0; }       // default value
    cnt += 1;
    return cnt += countNodes(ptr->left) + countNodes(ptr->right);
}

int countLeafNodes(Node<int>* ptr) {
    int cnt = 0;
    if (ptr == nullptr) { return 0; }       // default value
    if (ptr->left == nullptr && ptr->right == nullptr)
        cnt += 1;
    return cnt += countLeafNodes(ptr->left) + countLeafNodes(ptr->right);
}

int countSingleNodes(Node<int>* ptr) {
    int cnt = 0;
    if (ptr == nullptr) { return 0; }       // default value
    if ((ptr->left && !ptr->right) || (!ptr->left && ptr->right))
        cnt += 1;
    return cnt += countSingleNodes(ptr->left) + countSingleNodes(ptr->right);
}

int getHeight(Node<int>* ptr) {
    int cnt = 0;
    if (ptr == nullptr) { return 0; }
    cnt += 1;
    return cnt += max(getHeight(ptr->left), getHeight(ptr->right));
}

int getSum(Node<int>* ptr) {
    int res = 0;                            // default value
    if (ptr == nullptr) { return 0; }       // default value

    res = sum(res, ptr->data);
    int a = getSum(ptr->left);              // left tree value
    int b = getSum(ptr->right);             // right tree value
    return res = sum(res, sum(a, b));
}

int getMax(Node<int>* ptr) {
    int res = -INF;                         // default value
    if (ptr == nullptr) { return -INF; }    // default value

    res = max(res, ptr->data);
    int a = getMax(ptr->left);              // left tree value
    int b = getMax(ptr->right);             // right tree value
    return res = max(res, max(a, b));
}

int getMin(Node<int>* ptr) {
    int res = INF;                          // default value
    if (ptr == nullptr) { return INF; }     // default value

    res = min(res, ptr->data);
    int a = getMin(ptr->left);              // left tree value
    int b = getMin(ptr->right);             // right tree value
    return res = min(res, min(a, b));
}

/////////////////////////////////////////////////////////////////////
// Binary Expression Tree

int evaluate(Node<int>* ptr) {
    if (ptr == nullptr) { return 0; }

    if (ptr->left == nullptr && ptr->right == nullptr) {
        return ptr->data;
    }
    else {
        int op = ptr->data;
        int value1 = evaluate(ptr->left);
        int value2 = evaluate(ptr->right);
        printf(">> Evaluate: %d %c %d\n", value1, op, value2);

        switch (op) {
        case '+': return value1 + value2;
        case '-': return value1 - value2;
        case '*': return value1 * value2;
        case '/': return value1 / value2;
        }
    }
    return 0;
}
