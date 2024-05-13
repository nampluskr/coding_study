#include <iostream>
#include "map_swea.h"
using namespace std;

Map<int, int> map2;

void search(Map<int, int>& m, int key) {
    auto res = m.find(key);
    if (res == nullptr)
        cout << key << ": Not found.\n";
    else
        cout << key << ": Found.\n";
}

void test_map_swea(int option) {
    if (option == 0) return;
    cout << "*** [STL] Map" << endl;

    map2.clear();

    // emplace(key, value)
    cout << " >> Insert" << endl;
    map2.emplace(100, 10);
    map2.emplace(200, 20);
    map2.emplace(300, 30);
    map2.emplace(400, 40);

    // find(key)
    cout << " >> Find" << endl;
    search(map2, 200);
    search(map2, 400);

    // erase(key)
    cout << " >> Erase" << endl;
    map2.erase(200);
    map2.erase(400);
    search(map2, 200);

    // access
    cout << " >> Access" << endl;
    cout << map2[100] << endl;
    cout << map2[200] << endl;
}