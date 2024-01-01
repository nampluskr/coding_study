#include "segtree.h"
#include <vector>
using namespace std;

SegmentTree seg;

int main()
{
    int arr[] = { 1, 3, 11, 6, 7, 10, 14, 9, 18, 16, 5, 4, 2, 8, 19 };
    int size = 15;

    seg.build(arr, size);
    printf("Range Sum[5 - 8] = %d\n", seg.query(5, 8));

    seg.update(5, 13);  // arr[5]: 10 -> 13
    printf("Range Sum[5 - 8] = %d\n", seg.query(5, 8));


    return 0;
}