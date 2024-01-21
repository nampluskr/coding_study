#include "sqrt_decomp.h"
#include <cstdio>

#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

SqrtDecomp<MAX_SIZE> sqrtSum;
SqrtDecompRange<MAX_SIZE> sqrtSumRange;

void test_sqrtSum(const int arr[], int size) {
    int left, right, res;

    sqrtSum.init(size);
    sqrtSum.build(arr, size);

    left = 1, right = 3;
    printf(">> sum[%2d, %2d] = %d\n", left, right, sqrtSum.queryRange(left, right));

    left = 3, right = 6;
    printf(">> sum[%2d, %2d] = %d\n", left, right, sqrtSum.queryRange(left, right));

    left = 9, right = 13;
    printf(">> sum[%2d, %2d] = %d\n", left, right, sqrtSum.queryRange(left, right));

    left = 0, right = size - 1;
    printf(">> sum[%2d, %2d] = %d\n", left, right, sqrtSum.queryRange(left, right));
}

void test_sqrtSumRange(const int arr[], int size) {
    int left, right, res;

    sqrtSumRange.init(size);
    sqrtSumRange.build(arr, size);

    sqrtSumRange.updateRange(0, size - 1, 1);

    left = 1, right = 3;
    printf(">> sum[%2d, %2d] = %d\n", left, right, sqrtSumRange.queryRange(left, right));

    left = 3, right = 6;
    printf(">> sum[%2d, %2d] = %d\n", left, right, sqrtSumRange.queryRange(left, right));

    left = 9, right = 13;
    printf(">> sum[%2d, %2d] = %d\n", left, right, sqrtSumRange.queryRange(left, right));

    left = 0, right = size - 1;
    printf(">> sum[%2d, %2d] = %d\n", left, right, sqrtSumRange.queryRange(left, right));
}