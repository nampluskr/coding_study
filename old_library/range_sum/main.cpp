#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

#include <cstdio>
#define MAX_NUM     100     // 0 <= x < MAX_NUM

extern void test_prefixSum(int arr[], int size, int seed, int max_num);
extern void test_segSum(int arr[], int size, int seed, int max_num);

int seed = 11;
int arr[MAX_SIZE];
int size = 10;

int main()
{
    printf("\n*** [Prefix Sum] ***\n");
    test_prefixSum(arr, size, seed, MAX_NUM);

    printf("\n*** [Segment Tree for Sum] ***\n");
    test_segSum(arr, size, seed, MAX_NUM);

    return 0;
}