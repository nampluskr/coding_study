#include <iostream>
#include "data.h"
#include <set>
using namespace std;

set<Data> s1;

void search(set<Data>& s, const Data& data) {
    auto res = s.find(data);
    if (res == s.end())
        cout << data << ": Not found.\n";
    else
        cout << data << ": Found.\n";
}

void test_set_stl(int option) {
    if (option == 0) return ;
    cout << "*** [STL] Set" << endl;

    s1.clear();

    // insert(key)
    s1.insert({ 200, 2 });
    s1.insert({ 500, 5 });
    s1.insert({ 300, 3 });
    s1.insert({ 100, 1 });
    s1.insert({ 400, 4 });

    cout << "Max = " << *(--s1.end()) << endl;
    cout << "Min = " << *s1.begin() << endl;

    // find(key)
    search(s1, { 200, 2 });
    search(s1, { 300, 2 });

    // // erase(key)
    cout << " >> Erase" << endl;
    s1.erase({ 200, 2 });
    s1.erase({ 300, 2 });
    search(s1, { 200, 2 });

    s1.clear();
}