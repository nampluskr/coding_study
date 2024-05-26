#include <cstdio>
#include "map_swea.h"
#include "..\..\data.h"

MapSWEA<Data, int> m;

void inorder(MapSWEA<Data, int>::Node* node) {
    if (node == nullptr) return;
    inorder(node->left);
    printf("(%d, %d):%d  ", node->key.number, node->key.id, node->value);
    inorder(node->right);
}

void print() {
    printf(">> ");
    inorder(m.root);
    printf("\n");
}

int main()
{
    Data k1{ 111, 1 }, k2{ 222, 2}, k3{ 333, 3 }, k4{ 444, 4 }, k5{ 555, 5 };
    int v1{100}, v2{200}, v3{300}, v4{400}, v5{500};

    m.clear();
    m.insert(k3, v3);
    m.insert(k2, v2);
    m.insert(k1, v1);
    m.insert(k5, v5);
    m.insert(k4, v4);
    print();

    m.erase(k3); print();
    m.erase(k5); print();
    m.erase(k2); print();

    m.clear();   print();

    return 0;
}