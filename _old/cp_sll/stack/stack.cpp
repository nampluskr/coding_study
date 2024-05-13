#include <iostream>
#include "stack.h"
#include "../data.h"

Stack<Data> q;

void init_list(Stack<Data>& q) {
    q.push({ 10, 1 });
    q.push({ 20, 2 });
    q.push({ 30, 3 });
    q.push({ 40, 4 });
    q.push({ 50, 5 });
}

void test_linkedlist(int option){
    if (option == 0) return;

    printf("\n*** Push/Pop elements:\n");
    q.clear();
    init_list(q);
    print_list(q);

    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        printf(">> Popped %s: ", cur.str().c_str());
        print_list(q);
    }

    printf("\n*** Erase elements:\n");
    q.clear();
    init_list(q);
    print_list(q);

    q.erase({ 20, 2 }); print_list(q);
    q.erase({ 30, 3 }); print_list(q);
    q.erase({ 40, 4 }); print_list(q);
}

int main()
{
    test_linkedlist(1);

    return 0;
}