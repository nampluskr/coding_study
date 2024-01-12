#include <cstdio>
#include "linked_list_ordered.h"


OrderedLinkedList<int> list;

void preorder(Node<int>* ptr) {
    if (ptr == nullptr) { return; }
    printf("[%d]->", ptr->data);    // visit the node
    preorder(ptr->next);
}

void test_sll_iterative() {
    list.insert(4);
    list.insert(1);
    list.insert(5);
    list.insert(2);
    list.insert(3);
    preorder(list.head); printf("\n");

    list.remove(4);
    preorder(list.head); printf("\n");

    list.remove(5);
    preorder(list.head); printf("\n");

    list.remove(3);
    preorder(list.head); printf("\n");

    list.remove(1);
    preorder(list.head); printf("\n");

    list.remove(2);
    preorder(list.head); printf("\n");
}

void test_sll_recursive() {
    list.head = list.insert(list.head, 4);
    list.head = list.insert(list.head, 1);
    list.head = list.insert(list.head, 5);
    list.head = list.insert(list.head, 2);
    list.head = list.insert(list.head, 3);
    preorder(list.head); printf("\n");

    //Node<int>* ptr = nullptr;
    //ptr = list.find(list.head, 4);
    //ptr = list.find(list.head, 1);
    //ptr = list.find(list.head, 5);
    //ptr = list.find(list.head, 2);
    //ptr = list.find(list.head, 3);
    //ptr = list.find(list.head, 6);

    list.head = list.remove(list.head, 6);
    preorder(list.head); printf("\n");

    list.head = list.remove(list.head, 4);
    preorder(list.head); printf("\n");

    list.head = list.remove(list.head, 5);
    preorder(list.head); printf("\n");

    list.head = list.remove(list.head, 3);
    preorder(list.head); printf("\n");

    list.head = list.remove(list.head, 1);
    preorder(list.head); printf("\n");

    list.head = list.remove(list.head, 2);
    preorder(list.head); printf("\n");
}

int main()
{
    printf("\n*** Iterative ***\n");
    test_sll_iterative();
    
    //printf("\n*** Recursive ***\n");
    //test_sll_recursive();

    return 0;
}