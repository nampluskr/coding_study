#include <cstdio>
#include "binary_tree.h"

BinaryTree bt;          // binary tree

Node<int>* create_binary_tree() {
    Node<int>* root;    // root node of binary tree

    auto n1 = new Node<int>{ 4, nullptr, nullptr };
    auto n2 = new Node<int>{ 8, nullptr, nullptr };
    auto n3 = new Node<int>{ 6, n1, n2 };
    auto n4 = new Node<int>{ 14, nullptr, nullptr };
    auto n5 = new Node<int>{ 20, nullptr, nullptr };
    auto n6 = new Node<int>{ 15, n4, n5 };
    auto n7 = new Node<int>{ 12, nullptr, n6 };

    root = new Node<int>{ 10, n3, n7 };
    return root;
}

void test_traversals() {
    bt.clear();
    bt.root = create_binary_tree();

    printf("\n* Preorder:\n");
    printf(">> "); bt.preOrder(bt.root); printf("\n");

    printf("\n* Preorder (Stack):\n");
    printf(">> "); bt.preOrder_stack(bt.root); printf("\n");

    printf("\n* Ineorder:\n");
    printf(">> "); bt.inOrder(bt.root); printf("\n");

    printf("\n* Postorder:\n");
    printf(">> "); bt.postOrder(bt.root); printf("\n");

    printf("\n* Level Order (Queue):\n");
    printf(">> "); bt.levelOrder(bt.root); printf("\n");
}

void test_clear() {
    bt.clear();
    bt.root = create_binary_tree();

    printf("\n* Ineorder:\n");
    printf(">> "); bt.inOrder(bt.root); printf("\n");

    bt.clear_stack();
    printf("\n* Ineorder:\n");
    printf(">> "); bt.inOrder(bt.root); printf("\n");

    bt.root = create_binary_tree();
    printf("\n* Ineorder:\n");
    printf(">> "); bt.inOrder(bt.root); printf("\n");

    bt.clear_queue();
    printf("\n* Ineorder:\n");
    printf(">> "); bt.inOrder(bt.root); printf("\n");
}

void test_count_nodes() {
    bt.clear();
    bt.root = create_binary_tree();

    printf("\n* Count nodes:\n");
    printf(">> Total nodes   = %d\n", bt.countNodes(bt.root));       // 8
    printf(">> Leaf nodes    = %d\n", bt.countLeafNodes(bt.root));   // 4
    printf(">> Single nodes  = %d\n", bt.countSingleNodes(bt.root)); // 4
    printf(">> Tree height   = %d\n", bt.getHeight(bt.root));        // 1
}

void test_calculate_node_values() {
    bt.clear();
    bt.root = create_binary_tree();

    printf("\n* Caculate node values:\n");
    printf(">> Sum of values = %d\n", bt.getSum(bt.root));     // 89
    printf(">> Max of values = %d\n", bt.getMax(bt.root));     // 20
    printf(">> Min of values = %d\n", bt.getMin(bt.root));     // 4

}

BinaryTree et;         // binary expression tree

Node<int>* create_expression_tree() {
    Node<int>* root;    // root node of expression tree

    auto n1 = new Node<int>{ 3, nullptr, nullptr };
    auto n2 = new Node<int>{ 2, nullptr, nullptr };
    auto n3 = new Node<int>{ '*', n1, n2 };
    auto n4 = new Node<int>{ 10, nullptr, nullptr };
    auto n5 = new Node<int>{ 5, nullptr, nullptr };
    auto n6 = new Node<int>{ '/', n4, n5 };
    root = new Node<int>{ '+', n3, n6 };

    return root;
}

int evaluate(Node<int>* curr) {
    if (curr == nullptr) return 0;      // base condition
    if (curr->left == nullptr && curr->right == nullptr)
        return curr->data;

    int op = curr->data;
    int a = evaluate(curr->left);
    int b = evaluate(curr->right);
    printf(">> Evaluate: %d %c %d\n", a, op, b);

    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
}

void test_expression_tree() {
    et.clear();
    et.root = create_expression_tree();

    printf("\n* Ineorder:\n");
    printf(">> "); et.inOrder(et.root); printf("\n");

    printf("\n* Binary Expression Tree:\n");
    printf(">> Result:   %d\n", evaluate(et.root));
}