#include <cstdio>
#include <iostream>
#include <deque>
using namespace std;

deque<int> dq0;

void test_deque_stl(int option) {
    if (option == 0) return;
    cout << "*** [STL] Deque" << endl;

    auto& dq = dq0;

    dq.clear();
    dq.push_front(50);
    dq.push_front(30);
    dq.push_front(20);
    dq.push_back(60);
    dq.push_back(70);

    cout << ">> Pop from the front:\n";
    while (!dq.empty()) {
        int cur = dq.front(); dq.pop_front();
        printf("%d (size=%d)\n", cur, dq.size());
    }

    dq.clear();
    dq.push_front(50);
    dq.push_front(30);
    dq.push_front(20);
    dq.push_back(60);
    dq.push_back(70);

    cout << ">> Pop from the back:\n";
    while (!dq.empty()) {
        int cur = dq.back(); dq.pop_back();
        printf("%d (size=%d)\n", cur, dq.size());
    }
    cout << endl;
}
