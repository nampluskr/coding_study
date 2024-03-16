#include <cstdio>
#include "bst.h"

BST_recur<int> bst1;
BST_recur<int> bst2;

void inorder(Node<int>* curr) {
    if (curr == nullptr) return;
    inorder(curr->left);
    printf("[%d] ", curr->data);
    inorder(curr->right);
}

template<typename T>
void show(const T& bst) {
    printf(">> ");
    inorder(bst.root);
    printf("\n");
}

template<typename T>
void test_bst(T& bst) {
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(1);
    bst.insert(9);
    show(bst);

    bst.remove(1); show(bst);
    bst.remove(9); show(bst);
    bst.remove(5); show(bst);
}

void test_bst_recur() { test_bst(bst1); }
void test_bst_iter() { test_bst(bst2); }