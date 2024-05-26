#include <cstdio>
#include "..\..\data.h"
#include "linked_list_swea.h"

LinkedListSWEA<Data> lls;

void print(const LinkedListSWEA<Data>& ll) {
    printf(">> ");
    auto cur = ll.head->next;
    while (cur != NULL) {
        printf("(%d, %d) ", cur->data.number, cur->data.id);
        cur = cur->next;
    }
    printf("\n");
}

void test_linkedlist_swea(int option) {
    if (option == 0) return;
    Data d1{ 111, 1 }, d2{ 222, 2}, d3{ 333, 3 }, d4{ 444, 4 }, d5{ 555, 5 };

    lls.clear();
    lls.insert(d1);
    lls.insert(d2);
    lls.insert(d3);
    lls.insert(d4);
    lls.insert(d5);
    print(lls);

    lls.erase(d3); print(lls);
    lls.erase(d1); print(lls);
    lls.erase(d5); print(lls);

    lls.clear(); print(lls);
}