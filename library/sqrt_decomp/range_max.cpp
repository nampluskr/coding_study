#include <cstdio>
#include "range_max.h"

void test_rngmax1(int option) {
    if (option == 0) return;
    
    const int N = 10;
    SqrtDecompMaxType1<N> rngmax1;
    int arr[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    printf("\n[ Sqrt Decomposition - Range Max Type-1]\n");
    rngmax1.init();
    rngmax1.build(arr);

    printf("\n*** Range Max ***\n");
}

void test_rngmax2(int option) {
    if (option == 0) return;
}

void test_rngmax3(int option) {
    if (option == 0) return;
}