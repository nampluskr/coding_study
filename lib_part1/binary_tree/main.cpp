extern void test_traversals();
extern void test_clear();
extern void test_count_nodes();
extern void test_calculate_node_values();
extern void test_expression_tree();

int main()
{
    test_traversals();
    //test_clear();
    test_count_nodes();
    test_calculate_node_values();

    test_expression_tree();

    return 0;
}