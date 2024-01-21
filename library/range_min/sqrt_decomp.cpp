#include "sqrt_decomp.h"
#include <cstdio>

#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

SqrtDecompMin<MAX_SIZE> sqrtMin;
SqrtDecompMinRange<MAX_SIZE> sqrtMinRange;
SqrtDecompMinRange<MAX_SIZE> sqrtMinRange2;

void test_sqrtMin(const int arr[], int size) {
    int left, right;

    sqrtMin.init(size);
    sqrtMin.build(arr, size);

    left = 1, right = 3;
    printf(">> Min[%2d, %2d] = %d\n", left, right, sqrtMin.queryRange(left, right));

    left = 3, right = 6;
    printf(">> Min[%2d, %2d] = %d\n", left, right, sqrtMin.queryRange(left, right));

    left = 9, right = 13;
    printf(">> Min[%2d, %2d] = %d\n", left, right, sqrtMin.queryRange(left, right));

    left = 0, right = size - 1;
    printf(">> Min[%2d, %2d] = %d\n", left, right, sqrtMin.queryRange(left, right));
}

void test_sqrtMinRange(const int arr[], int size) {
    int left, right;

    sqrtMinRange.init(size);
    sqrtMinRange.build(arr, size);

    sqrtMinRange.updateRange(0, size - 1, 1);

    left = 1, right = 3;
    printf(">> Min[%2d, %2d] = %d\n", left, right, sqrtMinRange.queryRange(left, right));

    left = 3, right = 6;
    printf(">> Min[%2d, %2d] = %d\n", left, right, sqrtMinRange.queryRange(left, right));

    left = 9, right = 13;
    printf(">> Min[%2d, %2d] = %d\n", left, right, sqrtMinRange.queryRange(left, right));

    left = 0, right = size - 1;
    printf(">> Min[%2d, %2d] = %d\n", left, right, sqrtMinRange.queryRange(left, right));
}

void test_sqrtMinRange2(const int arr[], int size) {
    int left, right;

    sqrtMinRange.init(size);
    sqrtMinRange.build(arr, size);

    sqrtMinRange.updateRange(0, size - 1, 1);

    left = 1, right = 3;
    printf(">> Min[%2d, %2d] = %d\n", left, right, sqrtMinRange.queryRange(left, right));

    left = 3, right = 6;
    printf(">> Min[%2d, %2d] = %d\n", left, right, sqrtMinRange.queryRange(left, right));

    left = 9, right = 13;
    printf(">> Min[%2d, %2d] = %d\n", left, right, sqrtMinRange.queryRange(left, right));

    left = 0, right = size - 1;
    printf(">> Min[%2d, %2d] = %d\n", left, right, sqrtMinRange.queryRange(left, right));
}