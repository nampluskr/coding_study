#include <cstdio>
#include "sqrt_decomp.h"

const int N = 10;
int arr[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

RangeSumType1<N> rngsum1;
RangeSumType2<N> rngsum2;

void test_rngsum1() {
    rngsum1.clear();
    for (int i = 0; i < N; i++) { rngsum1.updatePoint(i, arr[i]); }

    int res = rngsum1.queryRange(0, 9);
    printf("Range [0, 9]: sum = %2d\n", res);

    rngsum1.updatePoint(2, 10);
    res = rngsum1.queryRange(0, 9);
    printf("Range [0, 9]: sum = %2d\n", res);

    rngsum1.updatePoint(8, -10);
    res = rngsum1.queryRange(0, 9);
    printf("Range [0, 9]: sum = %2d\n", res);
}

void test_rngsum2() {
    rngsum2.clear();
    for (int i = 0; i < N; i++) { rngsum2.updatePoint(i, arr[i]); }

    int res = rngsum2.queryRange(0, 9);
    printf("Range [0, 9]: sum = %2d\n", res);

    rngsum2.updateRange(0, 9, 10);
    res = rngsum2.queryRange(0, 9);
    printf("Range [0, 9]: sum = %2d\n", res);

    rngsum2.updateRange(0, 4, -10);
    res = rngsum2.queryRange(0, 9);
    printf("Range [0, 9]: sum = %2d\n", res);
}

int main()
{
    printf("\n*** Range Sum Type-1 ***\n");
    test_rngsum1();
    
    printf("\n*** Range Sum Type-1 ***\n");
    test_rngsum2();

    return 0;
}