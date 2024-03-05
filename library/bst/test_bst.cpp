#include "bst_recur.h"
#include "bst_iter.h"
#include <cstdio>

BinarySearchTree_recur<int> bst1;
BinarySearchTree_iter<int> bst2;

/*
          50
       /     \
      30      70
     /  \    /
   20   40  60
*/

void inorder(Node<int>* ptr) {
    if (ptr == nullptr) return;

    inorder(ptr->left);
    printf("[%d] ", ptr->data);
    inorder(ptr->right);
}

void show(Node<int>* ptr) {
    printf(">> ");
    inorder(ptr);
    printf("\n");
}


void test_bst_recur(int option) {
    if (option == 0) return;

    bst1.insert(50);
    bst1.insert(30);
    bst1.insert(20);
    bst1.insert(40);
    bst1.insert(70);
    bst1.insert(60);
    show(bst1.root);

    printf("\n- Delete leaf node (20):\n");
    bst1.remove(20);
    show(bst1.root);

    printf("\n- Delete single child node (70):\n");
    bst1.remove(70);
    show(bst1.root);

    printf("\n- Delete two children node (50):\n");
    bst1.remove(50);
    show(bst1.root);
}

void test_bst_iter(int option) {
    if (option == 0) return;

    bst2.insert(50);
    bst2.insert(30);
    bst2.insert(20);
    bst2.insert(40);
    bst2.insert(70);
    bst2.insert(60);
    show(bst2.root);

    printf("\n- Delete leaf node (20)\n");
    bst2.remove(20);
    show(bst2.root);

    printf("\n- Delete single child node (70)\n");
    bst2.remove(70);
    show(bst2.root);

    printf("\n- Delete two children node (50)\n");
    bst2.remove(50);
    show(bst2.root);
}