#include <cstdio>
#include "heap.h"


struct Data {
    int value, idx;

    bool operator<(const Data& data) const {
        return (value < data.value) || (value == data.value && idx > data.idx);
    }
};

MaxHeap<Data, 10> PQ;

int main()
{
    PQ.push({ 10, 1 });
    PQ.push({ 30, 3 });
    PQ.push({ 20, 2 });
    PQ.push({ 40, 4 });
    PQ.push({ 50, 5 });

    while (!PQ.empty())
        PQ.pop();


    return 0;
}