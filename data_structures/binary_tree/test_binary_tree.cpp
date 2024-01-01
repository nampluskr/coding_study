#include "binary_tree.h"

Node<int>* root;

/*
            10
        6       12
     4    8         15
                 14    20
*/

void init() {
    auto n1 = new_node<int>(4, nullptr, nullptr);
    auto n2 = new_node<int>(8, nullptr, nullptr);
    auto n3 = new_node<int>(6, n1, n2);
    auto n4 = new_node<int>(14, nullptr, nullptr);
    auto n5 = new_node<int>(20, nullptr, nullptr);
    auto n6 = new_node<int>(15, n4, n5);
    auto n7 = new_node<int>(12, nullptr, n6);
    root = new_node<int>(10, n3, n7);
}

void test_traversal() {
    printf("\n*** Preorder Traversal ***\n");
    printf(">> ");
    preorder(root);  printf("\n");

    printf("\n*** Preorder Traversal (Stack) ***\n");
    printf(">> ");
    preorder(root);  printf("\n");

    printf("\n*** Inorder Traversal ***\n");
    printf(">> ");
    inorder(root);   printf("\n");

    printf("\n*** Postorder Traversal ***\n");
    printf(">> ");
    postorder(root); printf("\n");

    printf("\n*** Level Order Traversal (Queue) ***\n");
    printf(">> ");
    level_order(root); printf("\n");
}

void test_count_nodes(){
    printf(">> Sum of value       = %d\n", sum_tree(root));     // 89
    printf(">> Max of value       = %d\n", max_tree(root));     // 20
    printf(">> Min of value       = %d\n", min_tree(root));     // 4
    printf(">> Count nodes        = %d\n", count_nodes(root));  // 8
    printf(">> Count leaf nodes   = %d\n", leaf_nodes(root));   // 4
    printf(">> Count single nodes = %d\n", single_nodes(root)); // 4
    printf(">> Tree height        = %d\n", height_tree(root));  // 1
}

void test_exp_tree() {
    auto n1 = new_node<int>(3, nullptr, nullptr);
    auto n2 = new_node<int>(2, nullptr, nullptr);
    auto n3 = new_node<int>('*', n1, n2);

    auto n4 = new_node<int>(10, nullptr, nullptr);
    auto n5 = new_node<int>(5, nullptr, nullptr);
    auto n6 = new_node<int>('/', n4, n5);

    root = new_node<int>('+', n3, n6);

    printf(">> Result: %d\n", evaluate(root));
}


int main()
{
    //init();
    //test_traversal();
    //test_count_nodes();

    test_exp_tree();
    root = clear<int>(root);

    return 0;
}
