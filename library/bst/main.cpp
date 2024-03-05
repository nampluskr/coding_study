#include <cstdio>

extern void test_bst_recur(int);
extern void test_bst_iter(int);

int main()
{
    printf("\n*** Binary Search Tree [Recursive] ***\n");
    test_bst_recur(1);

    printf("\n*** Binary Search Tree [Iterative] ***\n");
    test_bst_iter(1);

    return 0;
}