#include "ordered_linked_list.h"
#include "node.h"
#include <cstdio>

OrderedLinkedListIterative<int> listIter;
OrderedLinkedListRecursive<int> listRecur;

void test_orderedlistIter() {
    listIter.clear();

    printf(">> insert:\n");
    listIter.insert(1); preorder(listIter.head); printf("->null\n");
    listIter.insert(3); preorder(listIter.head); printf("->null\n");
    listIter.insert(2); preorder(listIter.head); printf("->null\n");

    printf(">> remove:\n");
    listIter.remove(4); preorder(listIter.head); printf("->null\n");
    listIter.remove(2); preorder(listIter.head); printf("->null\n");
    listIter.remove(3); preorder(listIter.head); printf("->null\n");
    listIter.remove(1); preorder(listIter.head); printf("->null\n");
}

void test_orderedlistRecur() {
    printf(">> insert:\n");
    listRecur.head = listRecur.clear(listRecur.head);
    listRecur.head = listRecur.insert(listRecur.head, 1); preorder(listRecur.head); printf("->null\n");
    listRecur.head = listRecur.insert(listRecur.head, 3); preorder(listRecur.head); printf("->null\n");
    listRecur.head = listRecur.insert(listRecur.head, 2); preorder(listRecur.head); printf("->null\n");

    printf(">> remove:\n");
    listRecur.head = listRecur.remove(listRecur.head, 4); preorder(listRecur.head); printf("->null\n");
    listRecur.head = listRecur.remove(listRecur.head, 2); preorder(listRecur.head); printf("->null\n");
    listRecur.head = listRecur.remove(listRecur.head, 3); preorder(listRecur.head); printf("->null\n");
    listRecur.head = listRecur.remove(listRecur.head, 1); preorder(listRecur.head); printf("->null\n");
}