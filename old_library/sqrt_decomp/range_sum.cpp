#include <cstdio>
#include "range_sum.h"

void test_rngsum1(int option) {
    if (option == 0) return;

    const int N = 10;
    SqrtDecompSumType1<N> rngsum1;
    int arr[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    printf("\n[ Sqrt Decomposition - Range Sum Type-1]\n");
    rngsum1.init();
    rngsum1.build(arr);

    printf("\n*** Range Sum ***\n");

    int left = 0, right = N - 1;
    int res = rngsum1.queryRange(left, right);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);

    rngsum1.updatePoint(2, 10);
    rngsum1.updatePoint(4, 10);
    res = rngsum1.queryRange(left, right);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);
}

void test_rngsum2(int option) {
    if (option == 0) return;

    const int N = 10;
    SqrtDecompSumType2<N> rngsum2;
    int arr[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    printf("\n[ Sqrt Decomposition - Range Sum Type-2]\n");
    rngsum2.init();
    rngsum2.build(arr);

    printf("\n*** Range Sum ***\n");

    int left = 0, right = N - 1;
    int res = rngsum2.queryRange(left, right);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);

    rngsum2.updatePoint(2, 10);
    rngsum2.updatePoint(4, 10);
    res = rngsum2.queryRange(left, right);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);

    rngsum2.updateRange(0, N - 1, 1);
    res = rngsum2.queryRange(left, right);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);
}