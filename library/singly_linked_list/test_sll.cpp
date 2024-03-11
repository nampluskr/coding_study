#include <cstdio>
#include "unordered_sll_iter.h"

void inorder(Node<int>* ptr) {
    if (ptr == nullptr) return;

    printf("[%d] ", ptr->data);
    inorder(ptr->next);
}

void show(Node<int>* ptr) {
    printf(">> ");
    inorder(ptr);
    printf("\n");
}

void test_unordered_sll_iter(int option) {
    if (option == 0) return;

    UnorderedLinkedList_iter<int> sll1;
    sll1.insert(10);
    sll1.insert(50);
    sll1.insert(30);
    sll1.insert(20);
    sll1.insert(40);
    show(sll1.head);

    printf("\n>> Remove 10:\n");
    sll1.remove(10);
    show(sll1.head);

    printf("\n>> Remove 30:\n");
    sll1.remove(30);
    show(sll1.head);

    printf("\n>> Remove 40:\n");
    sll1.remove(40);
    show(sll1.head);
}
