#include <cstdio>
#include "..\..\data.h"
#include "linked_list.h"

LinkedList<Data> ll;

void print(const LinkedList<Data>& ll) {
    printf(">> ");
    auto cur = ll.head;
    while (cur != NULL) {
        printf("(%d, %d) ", cur->data.number, cur->data.id);
        cur = cur->next;
    }
    printf("\n");
}

void test_linkedlist(int option) {
    if (option == 0) return;
    Data d1{ 111, 1 }, d2{ 222, 2}, d3{ 333, 3 }, d4{ 444, 4 }, d5{ 555, 5 };

    ll.clear();
    ll.insert(d1);
    ll.insert(d2);
    ll.insert(d3);
    ll.insert(d4);
    ll.insert(d5);
    print(ll);

    ll.erase(d3); print(ll);
    ll.erase(d1); print(ll);
    ll.erase(d5); print(ll);

    ll.clear(); print(ll);
}
