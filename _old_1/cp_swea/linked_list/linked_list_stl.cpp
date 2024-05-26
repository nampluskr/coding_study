#include <cstdio>
#include <list>
#include <algorithm>
using namespace std;

/*
li.insert(iter, x)
li.erase(iter)
*/

list<int> li0;

void print_list_stl() {
    auto& li = li0;
    for (const auto& x : li)
        printf("%d ", x);
    printf("\n");
}

void test_linkedlist_stl(int option) {
    if (option == 0) return;
    printf("*** [STL] Linked List\n");
    auto& li = li0;

    li.clear();
    li.insert(li.begin(), 10);
    li.insert(li.begin(), 20);
    li.insert(li.begin(), 20);
    li.insert(li.begin(), 30);
    li.insert(li.begin(), 30);
    li.insert(li.begin(), 30);
    print_list_stl();

    li.erase(find(li.begin(), li.end(), 10));
    li.erase(find(li.begin(), li.end(), 20));
    li.erase(find(li.begin(), li.end(), 30));
    print_list_stl();

}
