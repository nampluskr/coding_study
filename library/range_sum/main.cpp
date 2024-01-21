#include <cstdio>

extern void test_prefixSum(const int arr[], int size);
extern void test_fenwickSum(const int arr[], int size);
extern void test_fenwickSumRange(const int arr[], int size);
extern void test_sqrtSum(const int arr[], int size);
extern void test_sqrtSumRange(const int arr[], int size);
extern void test_segSum(const int arr[], int size);
extern void test_segSumRange(const int arr[], int size);

int arr[] = { 1, 3, 11, 6, 7, 10, 14, 9, 18, 16, 5, 4, 2, 8, 19 };
int size = 15;

int main()
{
    //printf("\n*** [Prefix Sum]\n");
    //test_prefixSum(arr, size);

    //printf("\n*** [Fenwick Tree]\n");
    //test_fenwickSum(arr, size);

    //printf("\n*** [Fenwick Tree - Range Update]\n");
    //test_fenwickSumRange(arr, size);

    //printf("\n*** [Sqrt Decomposition]\n");
    //test_sqrtSum(arr, size);

    //printf("\n*** [Sqrt Decomposition - Range Update]\n");
    //test_sqrtSumRange(arr, size);

    printf("\n*** [Segment Tree]\n");
    test_segSum(arr, size);

    printf("\n*** [Segment Tree - Range Update]\n");
    test_segSumRange(arr, size);

    return 0;
}