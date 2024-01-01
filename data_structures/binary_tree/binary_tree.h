#pragma once

#include <cstdio>
#include <queue>
#include <stack>

template<typename T>
struct Node {
    T data;
    Node* left = nullptr;
    Node* right = nullptr;
};

template<typename T>
Node<T>* new_node(const T& data, Node<T>* left, Node<T>* right) {
    Node<T>* node = new Node<T>{ data, left, right };
    return node;
}

template<typename T>
Node<T>* clear(Node<T>* ptr) {
    if (ptr == nullptr) { return nullptr; }
    ptr->left = clear(ptr->left);
    ptr->right = clear(ptr->right);
    delete ptr;
    return nullptr;
}

void preorder(Node<int>* ptr) {
    if (ptr == nullptr) return;     // base case
    printf("[%d]->", ptr->data);    // visit the node
    preorder(ptr->left);
    preorder(ptr->right);
}

void inorder(Node<int>* ptr) {
    if (ptr == nullptr) return;     // base case
    inorder(ptr->left);
    printf("[%d]->", ptr->data);    // visit the node
    inorder(ptr->right);
}

void postorder(Node<int>* ptr) {
    if (ptr == nullptr) return;     // base case
    postorder(ptr->left);
    postorder(ptr->right);
    printf("[%d]->", ptr->data);    // visit the node
}

void preorder_stack(Node<int>* ptr) {
    std::stack<Node<int>*> S;
    S.push(ptr);

    while (!S.empty()) {
        ptr = S.top(); S.pop();

        printf("[%d]->", ptr->data);    // visit the node
        if (ptr->right != nullptr) { S.push(ptr->right); }
        if (ptr->left != nullptr) { S.push(ptr->left); }
    }
}

void level_order(Node<int>* ptr) {
    std::queue<Node<int>*> Q;
    Q.push(ptr);

    while (!Q.empty()) {
        ptr = Q.front(); Q.pop();

        printf("[%d]->", ptr->data);    // visit the node
        if (ptr->left != nullptr)
            Q.push(ptr->left);
        if (ptr->right != nullptr)
            Q.push(ptr->right);
    }
}

// 노드 값 연산
const int INF = 0x7fffffff;
inline int sum(int a, int b) { return a + b; }
inline int max(int a, int b) { return (a < b) ? b : a; }
inline int min(int a, int b) { return (a < b) ? a : b; }

int sum_tree(Node<int>* ptr) {
    int res = 0;                            // default value
    if (ptr == nullptr) { return 0; }       // default value

    res = sum(res, ptr->data);
    int a = sum_tree(ptr->left);            // left tree value
    int b = sum_tree(ptr->right);           // right tree value
    return res = sum(res, sum(a, b));
}

int max_tree(Node<int>* ptr) {
    int res = -INF;                         // default value
    if (ptr == nullptr) { return -INF; }    // default value

    res = max(res, ptr->data);
    int a = max_tree(ptr->left);            // left tree value
    int b = max_tree(ptr->right);           // right tree value
    return res = max(res, max(a, b));
}

int min_tree(Node<int>* ptr) {
    int res = INF;                          // default value
    if (ptr == nullptr) { return INF; }     // default value

    res = min(res, ptr->data);
    int a = min_tree(ptr->left);            // left tree value
    int b = min_tree(ptr->right);           // right tree value
    return res = min(res, min(a, b));
}

// 조건별 노드 개수 세기
int count_nodes(Node<int>* ptr) {
    int cnt = 0;
    if (ptr == nullptr) { return 0; }       // default value
    cnt += 1;
    return cnt += count_nodes(ptr->left) + count_nodes(ptr->right);
}

int leaf_nodes(Node<int>* ptr) {
    int cnt = 0;
    if (ptr == nullptr) { return 0; }       // default value
    if (ptr->left == nullptr && ptr->right == nullptr)
        cnt += 1;
    return cnt += leaf_nodes(ptr->left) + leaf_nodes(ptr->right);
}

int single_nodes(Node<int>* ptr) {
    int cnt = 0;
    if (ptr == nullptr) { return 0; }       // default value
    if ((ptr->left && !ptr->right) || (!ptr->left && ptr->right))
        cnt += 1;
    return cnt += single_nodes(ptr->left) + single_nodes(ptr->right);
}

int height_tree(Node<int>* ptr) {
    int cnt = 0;
    if (ptr == nullptr) { return 0; }
    cnt += 1;
    return cnt += max(height_tree(ptr->left), height_tree(ptr->right));
}

// Binary Expression Tree 계산
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