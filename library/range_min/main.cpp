#include <cstdio>

extern void test_fenwickMin(const int arr[], int size);
extern void test_sqrtMin(const int arr[], int size);
extern void test_sqrtMinRange(const int arr[], int size);
extern void test_sqrtMinRange2(const int arr[], int size);
extern void test_segMin(const int arr[], int size);
extern void test_segMinRange(const int arr[], int size);

int arr[] = { 1, 3, 11, 6, 7, 10, 14, 9, 18, 16, 5, 4, 2, 8, 19 };
int size = 15;

int main()
{
    printf("\n*** [Fenwick Tree (Prefix/Suffix)]\n");
    test_fenwickMin(arr, size);

    printf("\n*** [Sqrt Decomposition]\n");
    test_sqrtMin(arr, size);

    printf("\n*** [Sqrt Decomposition - Range Update]\n");
    test_sqrtMinRange(arr, size);

    printf("\n*** [Sqrt Decomposition - Range Update]\n");
    test_sqrtMinRange2(arr, size);

    printf("\n*** [Segment Tree]\n");
    test_segMin(arr, size);

    printf("\n*** [Segment Tree - Range Update]\n");
    test_segMinRange(arr, size);

    return 0;
}