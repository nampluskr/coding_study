#include "search.h"
#include <cstdio>

/////////////////////////////////////////////////////////////////////
int arr[] = {1, 3, 5, 5, 7, 12, 14, 17, 18, 19, 26, 33, 34, 38, 55, 61};
int n = 16;

void show_result(int arr[], int n) {
        printf(">> ");
        for (int i = 0; i < n - 1; i++)
            printf("[%d]%d, ", i, arr[i]);
        printf("[%d]%d\n", n - 1, arr[n - 1]);
}

void test_linearSearch(int option) {
    if (option == 0) return;

    show_result(arr, n);
    int res, x = 12;

    printf("\n[Linear Search (Iterative)] n = %d\n", n);
    res = linearSearch(arr, n, x);
    printf(">> x = %2d: idx = %d\n", x, res);

    printf("\n[Linear Search (Recursive - forward)] n = %d\n", n);
    res = linearSearch_recur(arr, n, x, 0);
    printf(">> x = %2d: idx = %d\n", x, res);

    printf("\n[Linear Search (Recursive - backward)] n = %d\n", n);
    res = linearSearch_recur2(arr, n, x);
    printf(">> x = %2d: idx = %d\n", x, res);

    printf("\n[Sentinel Linear Search] n = %d\n", n);
    res = sentinelSearch(arr, n, x);
    printf(">> x = %2d: idx = %d\n", x, res);

    printf("\n[Linear Search (Transposition)] n = %d\n", n);
    res = linearSearch_recur2(arr, n, x);
    printf(">> x = %2d: idx = %d\n", x, res);

    printf("\n[Linear Search (Move to Front)] n = %d\n", n);
    res = linearSearch_recur2(arr, n, x);
    printf(">> x = %2d: idx = %d\n", x, res);
}


void test_binarySearch(int option) {
    if (option == 0) return;

    show_result(arr, n);
    int res, x;
    printf("\n[Binary Search (Iterative)] n = %d\n", n);
    
    x = 12, res = binarySearch(arr, n, x);
    printf(">> x = %2d: idx = %d\n", x, res);

    printf("\n[Binary Search (Recursive)] n = %d\n", n);
    res = binarySearch_recur(arr, 0, n - 1, x);
    printf(">> x = %2d: idx = %d\n", x, res);

    printf("\n[Lower / Upper Bound] n = %d\n", n);
    x = 5, res = lowerBound(arr, n, x);
    printf(">> x = %2d: Lower bound = %d\n", x, res);

    x = 5, res = parametricSearch(arr, 0, n - 1, x);
    printf(">> x = %2d: Lower bound = %d\n", x, res);

    x = 5, res = upperBound(arr, n, x);
    printf(">> x = %2d: Upper bound = %d\n", x, res);
}

void test_quickSelect(int option) {
    if (option == 0) return;

    show_result(arr, n);
    int res, k;

    printf("\n[Quick Select (Top-K)] n = %d\n", n);

    k = 1; quickSelect(arr, n, n - k);
    printf(">> Top-%d = %2d\n", k, arr[n - k]);

    k = 5; quickSelect(arr, n, n - k);
    printf(">> Top-%d = %2d\n", k, arr[n - k]);

    printf("\n[Quick Select (Bottom-K)] n = %d\n", n);

    k = 1; quickSelect(arr, n, k);
    printf(">> Bottom-%d = %2d\n", k, arr[k - 1]);

    k = 5; quickSelect(arr, n, k);
    printf(">> Bottom-%d = %2d\n", k, arr[k - 1]);

}