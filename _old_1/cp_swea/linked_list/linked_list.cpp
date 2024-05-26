#include <iostream>
#include "linked_list.h"
#include "data.h"
using namespace std;

LinkedList<Data> L;

void test_linked_list() {
    L.clear();
    L.push_back({ 100, 1 });
    L.push_back({ 200, 2 });
    L.push_back({ 300, 3 });
    L.print();

    auto ret = L.find({ 100, 1 });
    if (ret != nullptr)
        cout << ret->data << endl;
    else
        cout << "Not found" << endl;

    ret = L.find({ 400, 4 });
    if (ret != nullptr)
        cout << ret->data << endl;
    else
        cout << "Not found" << endl;

    L.clear();
}