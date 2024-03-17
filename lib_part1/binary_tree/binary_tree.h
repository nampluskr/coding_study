#pragma once
#include <stack>
#include <queue>

const int INF = 10e6;
inline int sum(int a, int b) { return a + b; }
inline int max(int a, int b) { return (a < b) ? b : a; }
inline int min(int a, int b) { return (a < b) ? a : b; }

template<typename T>
struct Node {
    T data;
    Node* left;
    Node* right;
};

struct BinaryTree {
    Node<int>* root;

    // clear all nodes
    void clear() { root = clear_recur(root); }
    Node<int>* clear_recur(Node<int>* curr);
    void clear_stack();
    void clear_queue();

    // traversals (recursive)
    void preOrder(Node<int>* curr);
    void postOrder(Node<int>* curr);
    void inOrder(Node<int>* curr);

    // traversals (iterative)
    void preOrder_stack(Node<int>* curr);
    void levelOrder(Node<int>* curr);

    // count nodes
    int countNodes(Node<int>* curr) {
        int cnt = 0;
        if (curr == nullptr) return 0;      // base condition
        cnt += 1;                           // visit the node
        return cnt += countNodes(curr->left) + countNodes(curr->right);
    }
    int countLeafNodes(Node<int>* curr) {
        int cnt = 0;
        if (curr == nullptr) return 0;      // base condition
        if (curr->left == nullptr && curr->right == nullptr)
            cnt += 1;                       // visit the node
        return cnt += countLeafNodes(curr->left) + countLeafNodes(curr->right);
    }
    int countSingleNodes(Node<int>* curr) {
        int cnt = 0;
        if (curr == nullptr) return 0;      // base condtion
        if ((curr->left && !curr->right) || (!curr->left && curr->right))
            cnt += 1;                       // visit the node
        return cnt += countSingleNodes(curr->left) + countSingleNodes(curr->right);
    }
    int getHeight(Node<int>* curr) {
        int cnt = 0;
        if (curr == nullptr) return 0;      // base condition
        cnt += 1;                           // visit the node
        return cnt += max(getHeight(curr->left), getHeight(curr->right));
    }

    // caculate node values
    int getSum(Node<int>* curr) {
        int res = 0;
        if (curr == nullptr) return 0;      // base condition
        res = sum(res, curr->data);         // visit the node
        int a = getSum(curr->left);         // left tree value
        int b = getSum(curr->right);        // right tree value
        return res = sum(res, sum(a, b));
    }
    int getMax(Node<int>* curr) {
        int res = -INF;
        if (curr == nullptr) return -INF;   // base condition
        res = max(res, curr->data);         // visit the node
        int a = getMax(curr->left);         // left tree value
        int b = getMax(curr->right);        // right tree value
        return res = max(res, max(a, b));
    }
    int getMin(Node<int>* curr) {
        int res = INF;
        if (curr == nullptr) return INF;    // base condition
        res = min(res, curr->data);         // visit the node
        int a = getMin(curr->left);         // left tree value
        int b = getMin(curr->right);        // right tree value
        return res = min(res, min(a, b));
    }
};

// DFS
void BinaryTree::preOrder(Node<int>* curr) {
    if (curr == nullptr) return;     // base case
    printf("[%d]->", curr->data);    // visit the node
    preOrder(curr->left);
    preOrder(curr->right);
}

void BinaryTree::inOrder(Node<int>* curr) {
    if (curr == nullptr) return;     // base case
    inOrder(curr->left);
    printf("[%d]->", curr->data);    // visit the node
    inOrder(curr->right);
}

void BinaryTree::postOrder(Node<int>* curr) {
    if (curr == nullptr) return;     // base case
    postOrder(curr->left);
    postOrder(curr->right);
    printf("[%d]->", curr->data);    // visit the node
}

// DFS
void BinaryTree::preOrder_stack(Node<int>* curr) {
    if (curr == nullptr) return;
    std::stack<Node<int>*> S;
    S.push(curr);
    while (!S.empty()) {
        curr = S.top(); S.pop();
        printf("[%d]->", curr->data);    // visit the node
        if (curr->right != nullptr) { S.push(curr->right); }
        if (curr->left != nullptr) { S.push(curr->left); }
    }
}

// BFS
void BinaryTree::levelOrder(Node<int>* curr) {
    if (curr == nullptr) return;
    std::queue<Node<int>*> Q;
    Q.push(curr);
    while (!Q.empty()) {
        curr = Q.front(); Q.pop();
        printf("[%d]->", curr->data);    // visit the node
        if (curr->left != nullptr) { Q.push(curr->left); }
        if (curr->right != nullptr) { Q.push(curr->right); }
    }
}

// delete nodes in postorder
Node<int>* BinaryTree::clear_recur(Node<int>* curr) {
    if (curr == nullptr) return nullptr;
    curr->left = clear_recur(curr->left);
    curr->right = clear_recur(curr->right);
    delete curr;
    return nullptr;
}

// delete nodes in preorder
void BinaryTree::clear_stack() {
    if (root == nullptr) return;
    std::stack<Node<int>*> S;
    S.push(root);
    while (!S.empty()) {
        auto curr = S.top(); S.pop();
        if (curr->left != nullptr) S.push(curr->left);
        if (curr->right != nullptr) S.push(curr->right);
        delete curr;
    }
    root = nullptr;
}

// delete nodes in level order
void BinaryTree::clear_queue() {
    if (root == nullptr) return;
    std::queue<Node<int>*> Q;
    Q.push(root);
    while (!Q.empty()) {
        auto curr = Q.front(); Q.pop();
        if (curr->left != nullptr) Q.push(curr->left);
        if (curr->right != nullptr) Q.push(curr->right);
        delete curr;
    }
    root = nullptr;
}

