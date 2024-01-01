#include <cstdio>
#include "bst.h"

struct Data {
    int value, idx;
    bool operator==(const Data& data) const {
        return value == data.value && idx == data.idx;
    }
    bool operator<(const Data& data) const {
        return (value < data.value) || (value == data.value && idx > data.idx);
    }
};

BinarySearchTree<Data> bst;

void test_bst_iterative() {
    bst.insert({ 10, 1 });
    bst.insert({ 6, 2 });
    bst.insert({ 4, 3 });
    bst.insert({ 8, 4 });
    bst.insert({ 12, 5 });
    bst.insert({ 15, 6 });
    bst.insert({ 14, 7 });
    bst.insert({ 20, 8 });

    bst.remove({ 10, 1 });
    bst.remove({ 8, 4 });

    while (bst.root != nullptr) {
        bst.remove(bst.root->data);
    }
}

void test_bst_recursive() {
    bst.root = bst.insert(bst.root, { 10, 1 });
    bst.root = bst.insert(bst.root, { 6, 2 });
    bst.root = bst.insert(bst.root, { 4, 3 });
    bst.root = bst.insert(bst.root, { 8, 4 });
    bst.root = bst.insert(bst.root, { 12, 5 });
    bst.root = bst.insert(bst.root, { 15, 6 });
    bst.root = bst.insert(bst.root, { 14, 7 });
    bst.root = bst.insert(bst.root, { 20, 8 });
    bst.root = bst.insert(bst.root, { 20, 8 });

    bst.root = bst.remove(bst.root, { 10, 1 });
    bst.root = bst.remove(bst.root, { 8, 4 });

    while (bst.root != nullptr) {
        bst.root = bst.remove(bst.root, bst.root->data);
    }
}

int main()
{
    //test_bst_iterative();

    test_bst_recursive();

    return 0;
}