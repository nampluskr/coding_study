#include <cstdio>
#include "linked_list.h"

LinkedList_recur<int> lst1;
LinkedList_iter<int> lst2;
OrderedLinkedList_recur<int> lst3;
OrderedLinkedList_iter<int> lst4;

template<typename T>
void show(const T& l) {
    auto curr = l.head;
    if (curr == nullptr) return;

    printf(">> ");
    while (curr != nullptr) {
        printf("[%d]-", curr->data);
        curr = curr->next;
    }
    printf("Null\n");
}

// 10 - 6 - 12 - 4 - 8 - 15 - 14 - 20 - Null
Node<int>* create_linked_list() {
    auto n1 = new Node<int>{ 20, nullptr };
    auto n2 = new Node<int>{ 14, n1 };
    auto n3 = new Node<int>{ 15, n2 };
    auto n4 = new Node<int>{ 8, n3 };
    auto n5 = new Node<int>{ 4, n4 };
    auto n6 = new Node<int>{ 12, n5 };
    auto n7 = new Node<int>{ 6, n6 };
    auto head = new Node<int>{ 10, n7 };
    return head;
}

template<typename T>
void test_linked_list(T& lst) {
    lst.clear();
    lst.head = create_linked_list();
    show(lst);

    lst.clear();
    lst.insert(10); lst.insert(6);  lst.insert(12);
    lst.insert(4);  lst.insert(8);  lst.insert(15);
    lst.insert(14); lst.insert(20);
    show(lst);

    lst.remove(10); show(lst);
    lst.remove(20); show(lst);
    lst.remove(8);  show(lst);
}

void test_linked_list_recur() { test_linked_list(lst1); }
void test_linked_list_iter() { test_linked_list(lst2); }
void test_ordered_linked_list_recur() { test_linked_list(lst3); }
void test_ordered_linked_list_iter() { test_linked_list(lst4); }