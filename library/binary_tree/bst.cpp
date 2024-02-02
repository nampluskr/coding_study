#include "bst.h"

struct Data {
    int value, idx;

    bool operator==(const Data& data) const {
        return value == data.value && idx == data.idx;
    }
    bool operator<(const Data& data) const {
        return (value < data.value) || (value == data.value && idx > data.idx);
    }
};

BinarySearchTree_iter<Data> bst1;
BinarySearchTree_recur<Data> bst2;

void inOrder(Node<Data>* ptr) {
    if (ptr == nullptr) return;         // base case
    inOrder(ptr->left);
    printf("[%d]->", ptr->data.value);  // visit the node
    inOrder(ptr->right);
}

void test_bst_iter(int option) {
    if (option == 0) return;

    printf("\n[Binary Search Tree (Iterative)]\n");
    bst1.insert({ 10, 1 });
    bst1.insert({ 6, 2 });
    bst1.insert({ 4, 3 });
    bst1.insert({ 8, 4 });
    bst1.insert({ 12, 5 });
    bst1.insert({ 15, 6 });
    bst1.insert({ 14, 7 });
    bst1.insert({ 20, 8 });
    bst1.insert({ 20, 8 });
    printf(">> "); inOrder(bst1.root); printf("\n");

    bst1.remove({ 10, 1 });
    bst1.remove({ 8, 4 });
    printf(">> "); inOrder(bst1.root); printf("\n");

    while (bst1.root != nullptr) {
        bst1.remove(bst1.root->data);
    }
    printf(">> "); inOrder(bst1.root); printf("\n");
}

void test_bst_recur(int option) {
    if (option == 0) return;

    printf("\n[Binary Search Tree (Recursive)]\n");
    bst2.root = bst2.insert(bst2.root, { 10, 1 });
    bst2.root = bst2.insert(bst2.root, { 6, 2 });
    bst2.root = bst2.insert(bst2.root, { 4, 3 });
    bst2.root = bst2.insert(bst2.root, { 8, 4 });
    bst2.root = bst2.insert(bst2.root, { 12, 5 });
    bst2.root = bst2.insert(bst2.root, { 15, 6 });
    bst2.root = bst2.insert(bst2.root, { 14, 7 });
    bst2.root = bst2.insert(bst2.root, { 20, 8 });
    bst2.root = bst2.insert(bst2.root, { 20, 8 });
    printf(">> "); inOrder(bst2.root); printf("\n");

    bst2.root = bst2.remove(bst2.root, { 10, 1 });
    bst2.root = bst2.remove(bst2.root, { 8, 4 });
    printf(">> "); inOrder(bst2.root); printf("\n");

    while (bst2.root != nullptr) {
        bst2.root = bst2.remove(bst2.root, bst2.root->data);
    }
    printf(">> "); inOrder(bst2.root); printf("\n");
}