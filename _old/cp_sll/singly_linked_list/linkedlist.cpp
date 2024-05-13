#include <iostream>
#include "linkedlist.h"
#include "../data.h"

LinkedList<Data> li;

void init_list(LinkedList<Data>& li) {
    li.push_back({ 10, 1 });
    li.push_back({ 20, 2 });
    li.push_back({ 30, 3 });
    li.push_back({ 40, 4 });
    li.push_back({ 50, 5 });
}

void test_linkedlist(int option){
    if (option == 0) return;

    printf("\n*** Push/Pop elements:\n");
    li.clear();
    init_list(li);
    print_list(li);

    while(!li.empty()) {
        auto cur = li.front(); li.pop_front();
        printf("%s ", cur.str().c_str());
        print_list(li);
    }

    printf("\n*** Erase elements:\n");
    li.clear();
    init_list(li);
    print_list(li);

    li.erase({ 20, 2 }); print_list(li);
    li.erase({ 30, 3 }); print_list(li);
    li.erase({ 40, 4 }); print_list(li);
}

int main()
{
    test_linkedlist(1);

    return 0;
}