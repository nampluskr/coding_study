#include <iostream>
#include <map>
using namespace std;

map<int, int> map1;

void search(map<int, int>& m, int key) {
    auto res = m.find(key);
    if (res == m.end())
        cout << key << ": Not found.\n";
    else
        cout << key << ": Found.\n";
}

void test_map_stl(int option) {
    if (option == 0) return;
    cout << "*** [STL] Map" << endl;

    map1.clear();

    // emplace(key, value)
    cout << " >> Insert" << endl;
    map1.emplace(100, 10);
    map1.emplace(200, 20);
    map1.insert({ 300, 30 });
    map1.insert({ 400, 40 });

    // find(key)
    cout << " >> Find" << endl;
    search(map1, 200);
    search(map1, 400);

    // erase(key)
    cout << " >> Erase" << endl;
    map1.erase(200);
    map1.erase(400);
    search(map1, 200);

    // access
    cout << " >> Access" << endl;
    cout << map1[100] << endl;
    cout << map1[200] << endl;
}