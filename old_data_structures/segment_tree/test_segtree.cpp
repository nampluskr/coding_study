#include "segtree.h"
#include <cstdio>

const int N = 5;
int arr[N] = { 1, 2, 3, 4, 5 };
SegmentTree<N> seg;

int main()
{
    seg.build(arr);
    printf("Range Sum [0, 4] = %d\n", seg.query(0, 4));

    //for (int i = 0; i < N; i++) { seg.update(i, 1); }
    seg.update(0, 4, 1);
    printf("Range Sum [0, 4] = %d\n", seg.query(0, 4));

    //for (int i = 0; i < N; i++) { seg.update(i, 1); }
    seg.update(0, 5, 1);
    printf("Range Sum [0, 4] = %d\n", seg.query(0, 4));


    return 0;
}
