#include <cstdio>
#include "linked_list.h"


Node<int>* head = nullptr;
LinkedList<int> list;

void test_traversal() {
    auto n1 = new_node<int>(3, nullptr);
    auto n2 = new_node<int>(2, n1);
    auto n3 = new_node<int>(5, n2);
    auto n4 = new_node<int>(1, n3);
    head = new_node<int>(4, n4);

    // recursive
    preorder(head);  printf("\n");
    postorder(head); printf("\n");
    
    //// for loop
    //for (auto ptr = head; ptr != nullptr; ptr = ptr->next)
    //    printf("[%d]->", ptr->data);
    //printf("\n");

    //// while loop
    //auto ptr = head;
    //while (ptr != nullptr) { 
    //    printf("[%d]->", ptr->data);
    //    ptr = ptr->next;
    //}
    //printf("\n");
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
    list.head = list.insert(list.head, 3);
    list.head = list.insert(list.head, 5);
    preorder(list.head); printf("\n");

    Node<int>* ptr = nullptr;
    //ptr = list.find(4);
    //ptr = list.find(1);
    //ptr = list.find(5);
    //ptr = list.find(2);
    //ptr = list.find(3);
    //ptr = list.find(6);

    ptr = list.find(list.head, 4);
    ptr = list.find(list.head, 1);
    ptr = list.find(list.head, 5);
    ptr = list.find(list.head, 2);
    ptr = list.find(list.head, 3);
    ptr = list.find(list.head, 6);

    //list.head = list.remove(list.head, 4);
    //preorder(list.head); printf("\n");

    //list.head = list.remove(list.head, 5);
    //preorder(list.head); printf("\n");

    //list.head = list.remove(list.head, 3);
    //preorder(list.head); printf("\n");

    //list.head = list.remove(list.head, 1);
    //preorder(list.head); printf("\n");

    //list.head = list.remove(list.head, 2);
    //preorder(list.head); printf("\n");
}

int main()
{
    //printf("\n*** Traversal ***\n");
    //test_traversal();
    //
    //printf("\n*** Iterative ***\n");
    //test_sll_iterative();
    
    printf("\n*** Recursive ***\n");
    test_sll_recursive();

    return 0;
}
