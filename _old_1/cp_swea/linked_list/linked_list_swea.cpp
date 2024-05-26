#include <cstdio>
#include "linked_list_swea.h"

LinkedList<int> li1;

void print_list() {
    auto& li = li1;
    auto cur = li.head->next;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

void test_linkedlist_swea(int option) {
    if (option == 0) return;
    printf("*** [SWEA] Linked List\n");
    auto& li = li1;

    // Test codes:
    li.clear(); 
    li.insert(10);
    li.insert(20);
    li.insert(20);
    li.insert(30);
    li.insert(30);
    li.insert(30);
    print_list();

    li.clear();
    li.insert(10);
    li.insert(20);
    li.insert(20);
    li.insert(30);
    li.insert(30);
    li.insert(30);
    print_list();

    printf(">> %d elements is deleted.\n", li.erase(30));
    printf(">> %d elements is deleted.\n", li.erase(20));
    printf(">> %d elements is deleted.\n", li.erase(10));
    print_list();
}
