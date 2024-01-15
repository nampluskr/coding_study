#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

#include <cstdio>
#include "func.h"
#include "prefix_sum.h"
#include "sqrt_decomp.h"
#include "fenwick_tree.h"
#include "seg_tree.h"

#define MAX_NUM		100		    // max. value of element (0 <= x < MAX_NUM)

int seed = 24;
int arr[MAX_SIZE];
int size = 10;

void init(int arr[], int size, int seed, int max_size) {
    for (int i = 0; i < size; i++) {
        seed = rand(seed);
        arr[i] = seed % max_size;
    }
    for (int i = 0; i < size; i++) { printf("%d ", arr[i]); }
    printf("\n");
}

template<typename T>
void test_rangeSum(T& rngSum, const int arr[], int size) {
    int res, left, right;

    left = 0, right = size - 1;
    res = rngSum.queryRange(left, right);
    printf(">> Range[%2d, %2d]: Sum = %d\n", left, right, res);

    left = 0, right = ceil(size, 2) - 1;
    res = rngSum.queryRange(left, right);
    printf(">> Range[%2d, %2d]: Sum = %d\n", left, right, res);

    left = ceil(size, 2), right = size - 1;
    res = rngSum.queryRange(left, right);
    printf(">> Range[%2d, %2d]: Sum = %d\n", left, right, res);
}

PrefixSum preSum;
SqrtDecomp sqrtSum;
SqrtDecompRange sqrtSumRng;
FenwickTree fenwick;
FenwickTreeRange fenwickRng;
SegmentTree segSum;
SegmentTreeRange segSumRng;

int main()
{
    /////////////////////////////////////////////////////////////////
    printf("\n*** [Prefix Sum] ***\n");
    init(arr, size, seed, MAX_NUM);
    preSum.build(arr, size);
    test_rangeSum(preSum, arr, size);

    printf("\n[Range Update +10 (Point Update - Rebuild)]\n");
    for (int i = 0; i < size; i++) { arr[i] += 10; }
    preSum.build(arr, size);
    test_rangeSum(preSum, arr, size);

    ///////////////////////////////////////////////////////////////////
    //printf("\n*** [Sqrt Decomposition for Sum] ***\n");
    //init(arr, size, seed, MAX_NUM);
    //sqrtSum.build(arr, size);
    //test_rangeSum(sqrtSum, arr, size);

    //printf("\n[Range Update +10 (Point Update)]\n");
    //for (int i = 0; i < size; i++) { sqrtSum.updatePoint(i, 10); }
    //test_rangeSum(sqrtSum, arr, size);

    ///////////////////////////////////////////////////////////////////
    //printf("\n*** [Sqrt Decomposition for Sum (Range Update)] ***\n");
    //init(arr, size, seed, MAX_NUM);
    //sqrtSumRng.build(arr, size);
    //test_rangeSum(sqrtSumRng, arr, size);

    //printf("\n[Range Update +10 (Range Update)]\n");
    //sqrtSumRng.updateRange(0, size - 1, 10);
    //test_rangeSum(sqrtSumRng, arr, size);

    /////////////////////////////////////////////////////////////////
    //printf("\n*** [Fenwick Tree for Sum] ***\n");
    //init(arr, size, seed, MAX_NUM);
    //fenwick.build(arr, size);
    //test_rangeSum(fenwick, arr, size);

    //printf("\n[Range Update +10 (Point Update)]\n");
    //for (int i = 0; i < size; i++) { fenwick.updatePoint(i, 10); }
    //test_rangeSum(fenwick, arr, size);

    /////////////////////////////////////////////////////////////////
    //printf("\n*** [Fenwick Tree for Sum (Range Update)] ***\n");
    //init(arr, size, seed, MAX_NUM);
    //fenwickRng.build(arr, size);
    //test_rangeSum(fenwickRng, arr, size);

    //printf("\n[Range Update +10 (Range Update)]\n");
    //fenwickRng.updateRange(0, size - 1, 10);
    //test_rangeSum(fenwickRng, arr, size);

    /////////////////////////////////////////////////////////////////
    printf("\n*** [Segment Tree for Sum] ***\n");
    init(arr, size, seed, MAX_NUM);
    segSum.build(arr, size);
    test_rangeSum(segSum, arr, size);

    printf("\n[Range Update +10 (Point Update)]\n");
    for (int i = 0; i < size; i++) { segSum.updatePoint(i, 10); }
    test_rangeSum(segSum, arr, size);

    /////////////////////////////////////////////////////////////////
    printf("\n*** [Segment Tree for Sum (Range Update)] ***\n");
    init(arr, size, seed, MAX_NUM);
    segSumRng.build(arr, size);
    test_rangeSum(segSumRng, arr, size);

    printf("\n[Range Update +10 (Range Update)]\n");
    segSumRng.updateRange(0, size - 1, 10);
    test_rangeSum(segSumRng, arr, size);

    return 0;
}
