#include <iostream>
#include "data.h"
#include "set_swea.h"
using namespace std;

Set<Data> s2;

void search(Set<Data>& s, const Data& data) {
    auto res = s.find(data);
    if (res == nullptr)
        cout << data << ": Not found.\n";
    else
        cout << data << ": Found.\n";
}

void test_set_swea(int option) {
    if (option == 0) return ;
    cout << "*** [STL] Set" << endl;

    s2.clear();

    // insert(key)
    s2.insert({ 200, 2 });
    s2.insert({ 500, 5 });
    s2.insert({ 300, 3 });
    s2.insert({ 100, 1 });
    s2.insert({ 400, 4 });

    cout << "Max = " << s2.back() << endl;
    cout << "Max = " << s2.front() << endl;


    // find(key)
    search(s2, { 200, 2 });
    search(s2, { 300, 2 });

    // // erase(key)
    cout << " >> Erase" << endl;
    s2.erase({ 200, 2 });
    s2.erase({ 300, 2 });
    search(s2, { 200, 2 });

    s2.clear();
}