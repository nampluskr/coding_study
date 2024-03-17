#include <cstdio>

extern void test_bst_recur();
extern void test_bst_iter();

int main()
{
    printf("\n*** Binary Search Tree - [Recursive]\n");
    test_bst_recur();

    printf("\n*** Binary Search Tree - [Iterative]\n");
    test_bst_iter();

    return 0;
}