#include "seg_tree.h"
#include <cstdio>

#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

SegmentTreeMin<MAX_SIZE> segMin;
SegmentTreeMinRange<MAX_SIZE> segMinRange;

void test_segMin(const int arr[], int size) {
    int left, right;

    segMin.init(size);
    segMin.build(arr);

    left = 1, right = 3;
    printf(">> Min[%2d, %2d] = %d\n", left, right, segMin.queryRange(left, right));

    left = 3, right = 6;
    printf(">> Min[%2d, %2d] = %d\n", left, right, segMin.queryRange(left, right));

    left = 9, right = 13;
    printf(">> Min[%2d, %2d] = %d\n", left, right, segMin.queryRange(left, right));

    left = 0, right = size - 1;
    printf(">> Min[%2d, %2d] = %d\n", left, right, segMin.queryRange(left, right));
}

void test_segMinRange(const int arr[], int size) {
    int left, right;

    segMinRange.init(size);
    segMinRange.build(arr);

    segMinRange.updateRange(0, size - 1, 1);

    left = 1, right = 3;
    printf(">> Min[%2d, %2d] = %d\n", left, right, segMinRange.queryRange(left, right));

    left = 3, right = 6;
    printf(">> Min[%2d, %2d] = %d\n", left, right, segMinRange.queryRange(left, right));

    left = 9, right = 13;
    printf(">> Min[%2d, %2d] = %d\n", left, right, segMinRange.queryRange(left, right));

    left = 0, right = size - 1;
    printf(">> Min[%2d, %2d] = %d\n", left, right, segMinRange.queryRange(left, right));
}