#include "seg_tree.h"
#include <cstdio>

#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

SegmentTree<MAX_SIZE> segSum;
SegmentTreeRange<MAX_SIZE> segSumRange;

void test_segSum(const int arr[], int size) {
    int left, right, res;

    segSum.init(size);
    segSum.build(arr);

    left = 1, right = 3;
    printf(">> sum[%2d, %2d] = %d\n", left, right, segSum.queryRange(left, right));

    left = 3, right = 6;
    printf(">> sum[%2d, %2d] = %d\n", left, right, segSum.queryRange(left, right));

    left = 9, right = 13;
    printf(">> sum[%2d, %2d] = %d\n", left, right, segSum.queryRange(left, right));

    left = 0, right = size - 1;
    printf(">> sum[%2d, %2d] = %d\n", left, right, segSum.queryRange(left, right));
}

void test_segSumRange(const int arr[], int size) {
    int left, right, res;

    segSumRange.init(size);
    segSumRange.build(arr);
    segSumRange.updateRange(0, size - 1, 1);

    left = 1, right = 3;
    printf(">> sum[%2d, %2d] = %d\n", left, right, segSumRange.queryRange(left, right));

    left = 3, right = 6;
    printf(">> sum[%2d, %2d] = %d\n", left, right, segSumRange.queryRange(left, right));

    left = 9, right = 13;
    printf(">> sum[%2d, %2d] = %d\n", left, right, segSumRange.queryRange(left, right));

    left = 0, right = size - 1;
    printf(">> sum[%2d, %2d] = %d\n", left, right, segSumRange.queryRange(left, right));
}