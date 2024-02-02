extern void test_traversals(int);
extern void test_operations(int);
extern void test_expression_tree(int);

extern void test_bst_iter(int);
extern void test_bst_recur(int);

int main()
{
    int opt;

    opt = 0;
    test_traversals(opt);

    opt = 0;
    test_operations(opt);

    opt = 0;
    test_expression_tree(opt);

    opt = 1;
    test_bst_iter(opt);
    test_bst_recur(opt);

    return 0;
}

