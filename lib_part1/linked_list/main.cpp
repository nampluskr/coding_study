#include <cstdio>

extern void test_linked_list_recur();
extern void test_linked_list_iter();
extern void test_ordered_linked_list_recur();
extern void test_ordered_linked_list_iter();

int main()
{
    printf("\n*** Linked List - Recursive\n");
    test_linked_list_recur();

    printf("\n*** Linked List - Iterative\n");
    test_linked_list_iter();

    printf("\n*** Ordered Linked List - Recursive\n");
    test_ordered_linked_list_recur();

    printf("\n*** Ordered Linked List - Iterative\n");
    test_ordered_linked_list_iter();

    return 0;
}