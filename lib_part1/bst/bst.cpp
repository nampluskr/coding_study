#include <cstdio>
#include "bst.h"

BinarySearchTree_recur<int> bst1;
BinarySearchTree_iter<int> bst2;

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
    printf("* Insert nodes:\n");
    bst.insert(10);
    bst.insert(6);  bst.insert(12);
    bst.insert(4);  bst.insert(8);
    bst.insert(12); bst.insert(15);
    bst.insert(14); bst.insert(20);
    show(bst);

    //bst.insert(8);  show(bst);

    printf("* Min element: %d\n", bst.findMinNode(bst.root)->data);
    printf("* Max element: %d\n", bst.findMaxNode(bst.root)->data);

    printf("* Remove nodes:\n");
    bst.remove(10); show(bst);
    bst.remove(4);  show(bst);
    bst.remove(20); show(bst);

    printf("* Clear all nodes:\n");
    bst.clear();    show(bst);
}

void test_bst_recur() { test_bst(bst1); }
void test_bst_iter() { test_bst(bst2); }