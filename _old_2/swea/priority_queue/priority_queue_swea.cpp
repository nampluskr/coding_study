#include <cstdio>
#include "priority_queue_swea.h"
#include "..\..\data.h"

PriorityQueueSWEA<Data> pq_swea;

void test_priority_queue_swea(int option) {
    if (option == 0) return;
    Data d1{ 111, 1 }, d2{ 222, 2}, d3{ 333, 3 }, d4{ 444, 4 }, d5{ 555, 5 };
    auto& pq = pq_swea;

    pq.push(d3);
    pq.push(d2);
    pq.push(d1);
    pq.push(d5);
    pq.push(d4);

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        printf("(%d, %d)\n", cur.number, cur.id);
    }
}

int main()
{
    test_priority_queue_swea(1);

    return 0;
}