#include "fenwick.h"
#include <cstdio>

#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

FenwickTree<MAX_SIZE> bitSum;
FenwickTreeRange<MAX_SIZE> bitSumRange;

void test_fenwickSum(const int arr[], int size) {
    int left, right, res;

    bitSum.init(size);
    bitSum.build(arr, size);

    left = 1, right = 3;
    printf(">> sum[%2d, %2d] = %d\n", left, right, bitSum.queryRange(left, right));

    left = 3, right = 6;
    printf(">> sum[%2d, %2d] = %d\n", left, right, bitSum.queryRange(left, right));

    left = 9, right = 13;
    printf(">> sum[%2d, %2d] = %d\n", left, right, bitSum.queryRange(left, right));

    left = 0, right = size - 1;
    printf(">> sum[%2d, %2d] = %d\n", left, right, bitSum.queryRange(left, right));
}

void test_fenwickSumRange(const int arr[], int size) {
    int left, right, res;

    bitSumRange.init(size);
    bitSumRange.build(arr, size);

    bitSumRange.updateRange(0, size-1, 1);

    left = 1, right = 3;
    printf(">> sum[%2d, %2d] = %d\n", left, right, bitSumRange.queryRange(left, right));

    left = 3, right = 6;
    printf(">> sum[%2d, %2d] = %d\n", left, right, bitSumRange.queryRange(left, right));

    left = 9, right = 13;
    printf(">> sum[%2d, %2d] = %d\n", left, right, bitSumRange.queryRange(left, right));

    left = 0, right = size - 1;
    printf(">> sum[%2d, %2d] = %d\n", left, right, bitSumRange.queryRange(left, right));
}