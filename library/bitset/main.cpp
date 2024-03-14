#include <cstdio>
#include "bitset.h"

#define MAX_SIZE    10

BitSet<MAX_SIZE> a, b, c;

void show(const BitSet<MAX_SIZE>& bit) {
    for (int i = 0; i < MAX_SIZE; i++)
        printf("%d", bit[i]);
    printf("\n");
}

int main()
{
    a.set(1);
    a.set(3);
    a.set(5);
    show(a);

    b.set(2);
    b.set(5);
    show(b);

    c = a | b;
    show(c);

    return 0;
}