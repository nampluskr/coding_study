#include <cstdio>

extern void test_bst_recur(int);
extern void test_bst_iter(int);

int main()
{
    int option;

    option = 1;

    printf("\n*** Binary Search Tree [Recursive]\n");
    test_bst_recur(option);

    printf("\n*** Binary Search Tree [Iterative]\n");
    test_bst_iter(option);
}