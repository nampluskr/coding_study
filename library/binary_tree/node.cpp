#include "node.h"

Node<int>* root = nullptr;

void create_tree() {
    auto n1 = new_node<int>(4, nullptr, nullptr);
    auto n2 = new_node<int>(8, nullptr, nullptr);
    auto n3 = new_node<int>(6, n1, n2);
    auto n4 = new_node<int>(14, nullptr, nullptr);
    auto n5 = new_node<int>(20, nullptr, nullptr);
    auto n6 = new_node<int>(15, n4, n5);
    auto n7 = new_node<int>(12, nullptr, n6);
    root = new_node<int>(10, n3, n7);
}

void test_traversals(int option) {
    if (option == 0) return;
    clear(root);
    create_tree();
 
    printf("\n[Traversal - Preorder]\n");
    printf(">> "); preOrder(root); printf("\n");
    printf("\n[Traversal - Preorder (Stack)]\n");
    printf(">> "); preOrder_stack(root); printf("\n");
    printf("\n[Traversal - Ineorder]\n");
    printf(">> "); inOrder(root); printf("\n");
    printf("\n[Traversal - Postorder]\n");
    printf(">> "); postOrder(root); printf("\n");
    printf("\n[Traversal - Level Order (Queue)]\n");
    printf(">> "); levelOrder(root); printf("\n");
}

void test_operations(int option) {
    if (option == 0) return;
    clear(root);
    create_tree();

    printf("\n[Binary Tree - Operations]\n");
    printf(">> Count tree nodes   = %d\n", countNodes(root));       // 8
    printf(">> Count leaf nodes   = %d\n", countLeafNodes(root));   // 4
    printf(">> Count single nodes = %d\n", countSingleNodes(root)); // 4
    printf(">> Tree height        = %d\n", getHeight(root));        // 1
    printf(">> Sum of values      = %d\n", getSum(root));           // 89
    printf(">> Max of values      = %d\n", getMax(root));           // 20
    printf(">> Min of values      = %d\n", getMin(root));           // 4
}

void test_expression_tree(int option) {
    if (option == 0) return;

    auto n1 = new_node<int>(3, nullptr, nullptr);
    auto n2 = new_node<int>(2, nullptr, nullptr);
    auto n3 = new_node<int>('*', n1, n2);
    auto n4 = new_node<int>(10, nullptr, nullptr);
    auto n5 = new_node<int>(5, nullptr, nullptr);
    auto n6 = new_node<int>('/', n4, n5);
    root = new_node<int>('+', n3, n6);

    printf("\n[Binary Expression Tree]\n");
    printf(">> Result:   %d\n", evaluate(root));
}
