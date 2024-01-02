#include <cstdio>
#include "sqrt_decom.h"

const int N = 10;
int arr[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
SqrtDecomp<N> P;


int main()
{
    Data res;
    P.init(arr);
    res = P.query(0, 9);
    printf("Range [0, 9]: sum = %2d, min = %2d, max = %3d\n", res.sum, res.min, res.max);

    //for (int i = 0; i < N; i++) { P.update(i, 1); }
    P.update(0, 9, 1);
    res = P.query(0, 9);
    printf("Range [0, 9]: sum = %2d, min = %2d, max = %3d\n", res.sum, res.min, res.max);

    //for (int i = 0; i < N; i++) { P.update(i, 1); }
    P.update(0, 9, 1);
    res = P.query(0, 9);
    printf("Range [0, 9]: sum = %2d, min = %2d, max = %3d\n", res.sum, res.min, res.max);

    return 0;
}