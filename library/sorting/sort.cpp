#include "sort.h"
#include <cstdio>
#include <ctime>

/////////////////////////////////////////////////////////////////////
#ifndef MAX_SIZE
#define MAX_SIZE 1'000'000
#endif

unsigned long long seed = 23;
int arr[MAX_SIZE];
int max_num = 100'000;
int n = 1'000'000;          // number of array elements
int num = 5;                // show first n elements and last n elements

int rand(unsigned long long seed) {
    seed = seed * 25214903917ULL + 11ULL;
    return (seed >> 16) & 0x3fffffff;
}

void init(int arr[], int n, int seed, int max_num) {
    for (int i = 0; i < n; i++) {
        seed = rand(seed);
        arr[i] = seed % max_num;
    }
}

void show_result(int arr[], int n, int num) {
    if (num > 0) {
        printf(">> ");
        for (int i = 0; i < num; i++)
            printf("%d, ", arr[i]);
        printf("... ");
        for (int i = 0; i < num - 1; i++)
            printf("%d, ", arr[n - 1 - num + i]);
        printf("%d\n", arr[n - 1]);
    }
} 

/////////////////////////////////////////////////////////////////////
// Basic sorting methods O(N^2)

void test_bubbleSort(int option) {
    if (option == 0) return;
    init(arr, n, seed, max_num);
    printf("\n[Bubble Sort (Iterative)] n = %d\n", n);

    clock_t start = clock();
    bubbleSort(arr, n);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, n, num);

    init(arr, n, seed, max_num);
    printf("\n[Bubble Sort (Recursive)] n = %d\n", n);

    start = clock();
    bubbleSort_recur(arr, n);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, n, num);
}

void test_selectionSort(int option) {
    if (option == 0) return;
    init(arr, n, seed, max_num);
    printf("\n[Selection Sort (Iterative)] n = %d\n", n);

    clock_t start = clock();
    selectionSort(arr, n);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, n, num);

    init(arr, n, seed, max_num);
    printf("\n[Selection Sort (Recursive)] n = %d\n", n);

    start = clock();
    selectionSort_recur(arr, n);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, n, num);
}

void test_insertionSort(int option) {
    if (option == 0) return;
    init(arr, n, seed, max_num);
    printf("\n[Insertion Sort (Iterative)] n = %d\n", n);

    clock_t start = clock();
    insertionSort(arr, n);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, n, num);

    init(arr, n, seed, max_num);
    printf("\n[Insertion Sort (Recursive)] n = %d\n", n);

    start = clock();
    insertionSort_recur(arr, n);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, n, num);
}

/////////////////////////////////////////////////////////////////////
// Fast sorting methods O(N log N)

void test_shellSort(int option) {
    if (option == 0) return;
    init(arr, n, seed, max_num);
    printf("\n[Shell Sort] n = %d\n", n);

    clock_t start = clock();
    shellSort(arr, n);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, n, num);
}

void test_mergeSort(int option) {
    if (option == 0) return;
    init(arr, n, seed, max_num);
    printf("\n[Merge Sort (Top-down)] n = %d\n", n);

    clock_t start = clock();
    mergeSort(arr, n);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, n, num);

    init(arr, n, seed, max_num);
    printf("\n[Merge Sort (Bottom-up)] n = %d\n", n);

    start = clock();
    mergeSort2(arr, n);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, n, num);
}

void test_quickSort(int option) {
    if (option == 0) return;
    init(arr, n, seed, max_num);
    printf("\n[Quick Sort (Recursive)] n = %d\n", n);

    clock_t start = clock();
    quickSort(arr, n);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, n, num);

    init(arr, n, seed, max_num);
    printf("\n[Quick Sort (Iterative)] n = %d\n", n);

    start = clock();
    quickSort_iter(arr, 0, n - 1);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, n, num);
}


/////////////////////////////////////////////////////////////////////
// Special sorting methods O(N)

void test_countingSort(int option) {
    if (option == 0) return;
    init(arr, n, seed, max_num);
    printf("\n[Counting Sort] n = %d\n", n);

    clock_t start = clock();
    countingSort(arr, n, max_num);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, n, num);
}

void test_radixSort10(int option) {
    if (option == 0) return;
    init(arr, n, seed, max_num);
    printf("\n[Radix Sort (base 10)] n = %d\n", n);

    clock_t start = clock();
    radixSort10(arr, n);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, n, num);
}

void test_radixSort256(int option) {
    if (option == 0) return;
    init(arr, n, seed, max_num);
    printf("\n[Radix Sort (base 256)] n = %d\n", n);

    clock_t start = clock();
    radixSort256(arr, n);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, n, num);
}