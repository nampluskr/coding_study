#include "prefix_sum.h"
#include "func.h"
#include <cstdio>

PrefixSum preSum;

void test_prefixSum(int arr[], int size, int seed, int max_num) {
    for (int i = 0; i < size; i++) {
        seed = rand(seed);
        arr[i] = seed % max_num;
    }

    for (int i = 0; i < size; i++) { printf("%d ", arr[i]); }
    printf("\n");

    int res, left, right;

    // initial
    preSum.build(arr, size);

    printf("\n[Initial]\n");
    left = 0, right = size - 1;
    res = preSum.queryRange(left, right);
    printf(">> Range[%2d, %2d]: Sum = %d\n", left, right, res);

    left = 0, right = ceil(size, 2) - 1;
    res = preSum.queryRange(left, right);
    printf(">> Range[%2d, %2d]: Sum = %d\n", left, right, res);

    left = ceil(size, 2), right = size - 1;
    res = preSum.queryRange(left, right);
    printf(">> Range[%2d, %2d]: Sum = %d\n", left, right, res);

    // point update
    printf("\n[Range Update +10 (Point Update - Rebuild)]\n");
    for (int i = 0; i < size; i++) { arr[i] += 10; }
    preSum.build(arr, size);

    left = 0, right = size - 1;
    res = preSum.queryRange(left, right);
    printf(">> Range[%2d, %2d]: Sum = %d\n", left, right, res);

    left = 0, right = ceil(size, 2) - 1;
    res = preSum.queryRange(left, right);
    printf(">> Range[%2d, %2d]: Sum = %d\n", left, right, res);

    left = ceil(size, 2), right = size - 1;
    res = preSum.queryRange(left, right);
    printf(">> Range[%2d, %2d]: Sum = %d\n", left, right, res);
}