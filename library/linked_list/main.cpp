#include <cstdio>

extern void test_traversal();
extern void test_linkedList();

extern void test_list();
extern void test_stack();
extern void test_queue();

extern void test_listIter();
extern void test_listRecur();

extern void test_orderedlistIter();
extern void test_orderedlistRecur();

extern void test_arrayList();
extern void test_arrayStack();
extern void test_arrayQueue();

int main()
{
    //printf("\n*** [Linked List Traversal]\n");
    //test_traversal();

    printf("\n*** [Linked List]\n");
    test_linkedList();

    //printf("\n*** [List]\n");
    //test_list();

    //printf("\n*** [Stack]\n");
    //test_stack();

    //printf("\n*** [Queue]\n");
    //test_queue();

    //printf("\n*** [Array List]\n");
    //test_arrayList();

    //printf("\n*** [Array Stack]\n");
    //test_arrayStack();

    //printf("\n*** [Array Queue]\n");
    //test_arrayQueue();

    //printf("\n*** [Linked List (Iterative)]\n");
    //test_listIter();

    //printf("\n*** [Linked List (Recursive)]\n");
    //test_listRecur();

    //printf("\n*** [OrderedLinked List (Iterative)]\n");
    //test_orderedlistIter();

    //printf("\n*** [OrderedLinked List (Recursive)]\n");
    //test_orderedlistRecur();

    return 0;
}
    