#include "node.h"
#include <stack>

void preorder(Node<int>* ptr) {
    if (ptr == nullptr) { return; }
    printf("[%d]->", ptr->data);
    preorder(ptr->next);
}

void postorder(Node<int>* ptr) {
    if (ptr == nullptr) { return; }
    postorder(ptr->next);
    printf("[%d]->", ptr->data);
}

void preorder2(Node<int>* ptr) {
    std::stack<Node<int>*> S;
    S.push(ptr);

    while (!S.empty()) {
        ptr = S.top(); S.pop();
        printf("[%d]->", ptr->data);
        if (ptr->next != nullptr) { S.push(ptr->next); }
    }
}

Node<int>* head;
Node<int>* new_node(int data, Node<int>* next = nullptr) {
    Node<int>* node = new Node<int>{ data, next };
    return node;
}
Iterator<int> begin() { return Iterator<int>(head); }
Iterator<int> end() { return Iterator<int>(nullptr); }

void test_traversal() {
    auto n5 = new_node(5, nullptr);
    auto n4 = new_node(4, n5);
    auto n3 = new_node(3, n4);
    auto n2 = new_node(2, n3);
    auto n1 = new_node(1, n2);
    head = new_node(0, n1);

    printf(">> preorder (recursive):\n");
    preorder(head);     printf("null\n");
    
    printf(">> preorder (stack):\n");
    preorder2(head);    printf("null\n");

    printf(">> preorder (for loop):\n");
    for (auto ptr = head; ptr; ptr = ptr->next) {
        printf("[%d]->", ptr->data);
    }
    printf("null\n");

    printf(">> preorder (iterator):\n");
    for (auto iter = begin(); iter != end(); iter++) {
        printf("[%d]->", *iter);
    }
    printf("null\n");

    printf(">> preorder (while loop):\n");
    auto ptr = head;
    while (ptr != nullptr) { 
        printf("[%d]->", ptr->data);
        ptr = ptr->next;
    }
    printf("null\n");

    printf(">> postorder (recursive):\n");
    postorder(head);    printf("null\n");

}