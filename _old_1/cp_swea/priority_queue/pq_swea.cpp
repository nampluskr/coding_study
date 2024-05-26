#include <iostream>
#include "data.h"
#include "pq_swea.h"

using namespace std;

PrioirtyQueue<Data> pq;

void test_pq_swea(int option) {
    if (option == 0) return;
    cout << "*** [User] Priority Queue" << endl;

    pq.clear();
    pq.push({ 400, 4 });
    pq.push({ 200, 2 });
    pq.push({ 300, 3 });
    pq.push({ 100, 1 });
    pq.push({ 500, 5 }); 

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        cout << cur << endl;
    }
    cout << endl;
}