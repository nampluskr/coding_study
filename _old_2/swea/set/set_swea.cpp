#include <cstdio>
#include "set_swea.h"
#include "..\..\data.h"

SetSWEA<Data> s;

void inorder(SetSWEA<Data>::Node* node) {
    if (node == nullptr) return;
    inorder(node->left);
    printf("(%d, %d) ", node->key.number, node->key.id);
    inorder(node->right);
}

void print() {
    printf(">> ");
    inorder(s.root);
    printf("\n");
}

int main()
{
    Data k1{ 111, 1 }, k2{ 222, 2}, k3{ 333, 3 }, k4{ 444, 4 }, k5{ 555, 5 };

    s.clear();
    s.insert(k3);
    s.insert(k2);
    s.insert(k1);
    s.insert(k5);
    s.insert(k4); print();

    s.erase(k3); print();
    s.erase(k5); print();
    s.erase(k2); print();

    s.clear();    print();
    s.insert(k4); print();
    s.clear();    print();

    return 0;
}