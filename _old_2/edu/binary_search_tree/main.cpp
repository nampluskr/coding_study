#include <cstdio>
#include "binary_search_tree_iter.h"
#include "binary_search_tree_recur.h"
#include "..\..\data.h"

BinarySearchTreeIter<Data> bst_iter;
BinarySearchTreeRecur<Data> bst_recur;

template<typename T>
void inorder(T* cur) {
    if (cur == nullptr) return;
    inorder(cur->left);
    printf("(%d, %d) ", cur->data.number, cur->data.id);
    inorder(cur->right);
}

template<typename T>
void print(const T& bst) {
    printf(">> ");
    inorder(bst.root);
    printf("\n");
}

template<typename T>
void test_binary_search_tree(T& bst) {
    Data d1{ 111, 1 }, d2{ 222, 2}, d3{ 333, 3 }, d4{ 444, 4 }, d5{ 555, 5 };

    bst.clear();
    bst.insert(d3);
    bst.insert(d5);
    bst.insert(d1);
    bst.insert(d4);
    bst.insert(d2); print(bst);
    bst.insert(d3); print(bst);

    bst.erase(d3); print(bst);
    bst.erase(d1); print(bst);
    bst.erase(d5); print(bst);

    printf(">> %d\n", bst.find(d2));
    printf(">> %d\n", bst.find(d3));

    bst.clear(); print(bst);
    bst.insert(d3); print(bst);    
    bst.clear(); print(bst);

}

int main()
{
    printf("\n[Binary Search Tree - Iterative]\n");
    test_binary_search_tree(bst_iter);

    printf("\n[Binary Search Tree - Recursive]\n");
    test_binary_search_tree(bst_recur);

    return 0;
}