#include <cstdio>
#include "deque_swea.h"
#include "..\..\data.h"

DequeSWEA<Data> deq_swea;

void test_deque_swea(int option) {
    if (option == 0) return;
    Data d1{ 111, 1 }, d2{ 222, 2}, d3{ 333, 3 }, d4{ 444, 4 }, d5{ 555, 5 };
    auto& Q = deq_swea;

    printf("\n*** [Deque - Queue] ***\n");
    Q.push_back(d1);
    Q.push_back(d2);
    Q.push_back(d3);
    Q.push_back(d4);
    Q.push_back(d5);

    while (!Q.empty()) {
        auto cur = Q.front(); Q.pop_front();
        printf("(%d, %d)\n", cur.number, cur.id); 
    }

    printf("\n*** [Deque - Stack] ***\n");
    Q.push_front(d1);
    Q.push_front(d2);
    Q.push_front(d3);
    Q.push_front(d4);
    Q.push_front(d5);

    while (!Q.empty()) {
        auto cur = Q.front(); Q.pop_front();
        printf("(%d, %d)\n", cur.number, cur.id); 
    }
}

int main()
{
    test_deque_swea(1);

    return 0;
}