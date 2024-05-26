#include <cstdio>
#include "ordered_linked_list_iter.h"
#include "ordered_linked_list_recur.h"
#include "..\..\data.h"

OrderedLinkedListIter<Data> li_iter;
OrderedLinkedListRecur<Data> li_recur;

template<typename T>
void print(const T& li) {
    printf(">> ");
    auto cur = li.head;
    while (cur != nullptr) {
        printf("(%d, %d) ", cur->data.number, cur->data.id);
        cur = cur->next;
    }
    printf("\n");
}

template<typename T>
void test_linked_list(T& li) {
    Data d1{ 111, 1 }, d2{ 222, 2}, d3{ 333, 3 }, d4{ 444, 4 }, d5{ 555, 5 };

    li.clear();
    li.insert(d3);
    li.insert(d1);
    li.insert(d5);
    li.insert(d2);
    li.insert(d4);
    li.insert(d3); print(li);

    li.erase(d3); print(li);
    li.erase(d1); print(li);
    li.erase(d5); print(li);

    printf(">> %d\n", li.find(d2));
    printf(">> %d\n", li.find(d3));

    li.clear(); print(li);
    li.insert(d3); print(li);
    li.clear(); print(li);
}

int main()
{
    printf("\n[Ordered Linked List - Iterative]\n");
    test_linked_list(li_iter);

    printf("\n[Ordered Linked List - Recursive]\n");
    test_linked_list(li_recur);

    return 0;
}