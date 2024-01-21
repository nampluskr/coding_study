#include "fenwick.h"
#include <cstdio>

#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

FenwickTree<MAX_SIZE> fenwickMin;

void test_fenwickMin(const int arr[], int size) {
    int left, right;

    fenwickMin.init(size);
    fenwickMin.build(arr, size);

    left = 1, right = 3;
    printf(">> Min[%2d, %2d] = %d\n", left, right, fenwickMin.queryRange(left, right));

    left = 3, right = 6;
    printf(">> Min[%2d, %2d] = %d\n", left, right, fenwickMin.queryRange(left, right));

    left = 9, right = 13;
    printf(">> Min[%2d, %2d] = %d\n", left, right, fenwickMin.queryRange(left, right));

    left = 0, right = size - 1;
    printf(">> Min[%2d, %2d] = %d\n", left, right, fenwickMin.queryRange(left, right));
}