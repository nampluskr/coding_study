#include "prefix_sum.h"
#include <cstdio>

#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

PrefixSum<MAX_SIZE> prefixSum;

void test_prefixSum(const int arr[], int size) {
    int left, right, res;
    
    prefixSum.clear();
    prefixSum.build(arr, size);
    
    left = 1, right = 3;
    printf(">> sum[%2d, %2d] = %d\n", left, right, prefixSum.queryRange(left, right));

    left = 3, right = 6;
    printf(">> sum[%2d, %2d] = %d\n", left, right, prefixSum.queryRange(left, right));

    left = 9, right = 13;
    printf(">> sum[%2d, %2d] = %d\n", left, right, prefixSum.queryRange(left, right));

    left = 0, right = size - 1;
    printf(">> sum[%2d, %2d] = %d\n", left, right, prefixSum.queryRange(left, right));
}