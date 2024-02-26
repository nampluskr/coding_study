#include "bst.h"
#include <cstdio>

BinarySearchTree_recur<int> bst1;
BinarySearchTree_iter<int> bst2;

void inorder(Node<int>* ptr) {
    if (ptr == nullptr) return;

    inorder(ptr->left);
    printf("%d ", ptr->data);
    inorder(ptr->right);
}

template<typename T>
void show(const T& tree) {
    printf(">> ");
    inorder(tree.root);
    printf("\n");
}

void test_bst_recur(int option) {
    if (option == 0) return;

    bst1.insert(10);
    bst1.insert(7);
    bst1.insert(5);
    bst1.insert(8);
    bst1.insert(15);
    bst1.insert(11);
    bst1.insert(18);
    show(bst1);

    (bst1.find(12) == nullptr) ? printf(">> Not Found.\n") : printf(">> Found!\n");
    (bst1.find(11) == nullptr) ? printf(">> Not Found.\n") : printf(">> Found!\n");
    printf(">> %d\n", bst1.find(11)->data);

    bst1.remove(11);
    show(bst1);

    bst1.remove(15);
    show(bst1);

    bst1.remove(10);
    show(bst1);
}

void test_bst_iter(int option) {
    if (option == 0) return;

    bst2.insert(10);
    bst2.insert(7);
    bst2.insert(5);
    bst2.insert(8);
    bst2.insert(15);
    bst2.insert(11);
    bst2.insert(18);
    show(bst2);

    (bst2.find(12) == nullptr) ? printf(">> Not Found.\n") : printf(">> Found!\n");
    (bst2.find(11) == nullptr) ? printf(">> Not Found.\n") : printf(">> Found!\n");
    printf(">> %d\n", bst2.find(11)->data);

    bst2.remove(11);
    show(bst2);

    bst2.remove(15);
    show(bst2);

    bst2.remove(10);
    show(bst2);
}