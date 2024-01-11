#include "segment_tree.h"
#include "func.h"
#include <cstdio>

SegmentTree segSum;
SegmentTreeRange segSumRange;

//template<typename T>
//void print_rangeSum(T& rngSum, int left, int right) {
//    int res = rngSum.queryRange(left, right);
//    printf(">> Range[%2d, %2d]: Sum = %d\n", left, right, res);
//}

void test_segSum(int arr[], int size, int seed, int max_num) {
    for (int i = 0; i < size; i++) {
        seed = rand(seed);
        arr[i] = seed % max_num;
    }
    for (int i = 0; i < size; i++) { printf("%d ", arr[i]); }
    printf("\n");

    // initial
    segSum.build(arr, size);

    printf("\n[Initial]\n");
    print_rangeSum(segSum, 0, size - 1);
    print_rangeSum(segSum, 0, ceil(size, 2) - 1);
    print_rangeSum(segSum, ceil(size, 2), size - 1);

    // point update
    printf("\n[Range Update +10 (Point Update - Rebuild)]\n");
    for (int i = 0; i < size; i++) { segSum.updatePoint(i, 10); }

    print_rangeSum(segSum, 0, size - 1);
    print_rangeSum(segSum, 0, ceil(size, 2) - 1);
    print_rangeSum(segSum, ceil(size, 2), size - 1);
}