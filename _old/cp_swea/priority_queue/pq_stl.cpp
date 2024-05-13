#include <iostream>
#include "data.h"
#include <queue>

using namespace std;

priority_queue<Data> umap;

void test_pq_stl(int option) {
    if (option == 0) return;
    cout << "*** [STL] Priority Queue" << endl;

    //umap.clear();
    umap.push({ 400, 4 });
    umap.push({ 200, 2 });
    umap.push({ 300, 3 });
    umap.push({ 100, 1 });
    umap.push({ 500, 5 });

    while (!umap.empty()) {
        auto cur = umap.top(); umap.pop();
        cout << cur << endl;
    }
    cout << endl;
}