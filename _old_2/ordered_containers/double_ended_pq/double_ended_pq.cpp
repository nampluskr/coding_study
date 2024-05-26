#include <cstdio>
#include "double_ended_pq.h"
#include "..\..\data.h"

DoubleEndedPQ<Data, 20> depq;

void test_double_ended_pq(int option) {
    if (option == 0) return;
    Data d1{ 111, 1 }, d2{ 222, 2}, d3{ 333, 3 }, d4{ 444, 4 }, d5{ 555, 5 };
    auto& Q = depq;

    printf("\n*** [Double Ended Priority Queue - top()] ***\n");
    Q.push(d3);
    Q.push(d1);
    Q.push(d5);
    Q.push(d2);
    Q.push(d4);

    while (!Q.empty()) {
        auto cur = Q.top(); Q.popTop();
        printf("(%d, %d)\n", cur.number, cur.id);
    }

    printf("\n*** [Double Ended Priority Queue - bottom()] ***\n");
    Q.push(d3);
    Q.push(d1);
    Q.push(d5);
    Q.push(d2);
    Q.push(d4);

    while (!Q.empty()) {
        auto cur = Q.bottom(); Q.popBottom();
        printf("(%d, %d)\n", cur.number, cur.id);
    }
}

int main()
{
    test_double_ended_pq(1);

    return 0;
}