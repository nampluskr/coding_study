#include <cstdio>
#include "sqrt_decpm.h"

const int N = 10;
int arr[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

RangeMaxType1<N> rngmax1;
RangeMaxType2<N> rngmax2;
RangeMaxType3<N> rngmax3;

void test_rngmax1() {
    rngmax1.clear();
    for (int i = 0; i < N; i++) { rngmax1.updatePoint(i, arr[i]); }

    int res = rngmax1.queryRange(0, 9);
    printf("Range [0, 9]: max = %2d\n", res);

    rngmax1.updatePoint(4, 10);
    res = rngmax1.queryRange(0, 9);
    printf("Range [0, 9]: max = %2d\n", res);

    rngmax1.updatePoint(7, 10);
    res = rngmax1.queryRange(0, 9);
    printf("Range [0, 9]: max = %2d\n", res);
}

void test_rngmax2() {
    rngmax2.clear();
    for (int i = 0; i < N; i++) { rngmax2.updatePoint(i, arr[i]); }

    int res = rngmax2.queryRange(0, 9);
    printf("Range [0, 9]: max = %2d\n", res);

    //rngmax2.updatePoint(4, 10);
    rngmax2.updateRange(0, 4, 10);
    res = rngmax2.queryRange(0, 9);
    printf("Range [0, 9]: max = %2d\n", res);

    //rngmax2.updatePoint(7, 10);
    rngmax2.updateRange(5, 9, 10);
    res = rngmax2.queryRange(0, 9);
    printf("Range [0, 9]: max = %2d\n", res);
}

void test_rngmax3() {
    rngmax3.clear();
    for (int i = 0; i < N; i++) { rngmax3.updatePoint(i, arr[i]); }

    int res = rngmax3.queryRange(0, 9);
    printf("Range [0, 9]: max = %2d\n", res);

    //rngmax3.updatePoint(4, 10);
    rngmax3.updateRange(0, 4, 10);
    res = rngmax3.queryRange(0, 9);
    printf("Range [0, 9]: max = %2d\n", res);

    //rngmax3.updatePoint(7, 10);
    rngmax3.updateRange(5, 9, 10);
    res = rngmax3.queryRange(0, 9);
    printf("Range [0, 9]: max = %2d\n", res);
}

int main()
{
    printf("\n*** Range Max Type-1 ***\n");
    test_rngmax1();

    printf("\n*** Range Max Type-2 ***\n");
    test_rngmax2();

    printf("\n*** Range Max Type-3 ***\n");
    test_rngmax3();

    return 0;
}