#include "sorting.h"
#include <cstdio>
#include <ctime>

/////////////////////////////////////////////////////////////////////
#ifndef MAX_SIZE
#define MAX_SIZE 1'000'000
#endif

unsigned long long seed = 1234;
int arr[MAX_SIZE];
int max_num = 100'000;
int size = 100'000;
int n = 10;             // show first n elements and last n elements

int rand(unsigned long long seed) {
    seed = seed * 25214903917ULL + 11ULL;
    return (seed >> 16) & 0x3fffffff;
}

void init(int arr[], int size, int seed, int max_num) {
    for (int i = 0; i < size; i++) {
        seed = rand(seed);
        arr[i] = seed % max_num;
    }
}

void show_result(int arr[], int size, int n) {
    if (n > 0) {
        printf(">> ");
        for (int i = 0; i < n; i++)
            printf("%d, ", arr[i]);
        printf("... ");
        for (int i = 0; i < n - 1; i++)
            printf("%d, ", arr[size - 1 - n + i]);
        printf("%d\n", arr[size - 1]);
    }
}

/////////////////////////////////////////////////////////////////////
// Basic sorting methods O(N^2)

void test_bubbleSort(int option) {
    if (option == 0) return;
    init(arr, size, seed, max_num);
    printf("\n[Bubble Sort] size = %d\n", size);

    clock_t start = clock();
    bubbleSort(arr, size);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, size, n);
}

void test_selectionSort(int option) {
    if (option == 0) return;
    init(arr, size, seed, max_num);
    printf("\n[Selection Sort] size = %d\n", size);

    clock_t start = clock();
    selectionSort(arr, size);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, size, n);
}

void test_insertionSort(int option) {
    if (option == 0) return;
    init(arr, size, seed, max_num);
    printf("\n[Insertion Sort] size = %d\n", size);

    clock_t start = clock();
    insertionSort(arr, size);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, size, n);
}

/////////////////////////////////////////////////////////////////////
// Fast sorting methods O(N log N)

void test_shellSort(int option) {
    if (option == 0) return;
    init(arr, size, seed, max_num);
    printf("\n[Shell Sort] size = %d\n", size);

    clock_t start = clock();
    shellSort(arr, size);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, size, n);
}

void test_mergeSort(int option) {
    if (option == 0) return;
    init(arr, size, seed, max_num);
    printf("\n[Shell Sort] size = %d\n", size);

    clock_t start = clock();
    mergeSort(arr, size);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, size, n);
}

void test_quickSort(int option) {
    if (option == 0) return;
    init(arr, size, seed, max_num);
    printf("\n[Shell Sort] size = %d\n", size);

    clock_t start = clock();
    quickSort(arr, size);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, size, n);
}


/////////////////////////////////////////////////////////////////////
// Special sorting methods O(N)

void test_countingSort(int option) {
    if (option == 0) return;
    init(arr, size, seed, max_num);
    printf("\n[Counting Sort] size = %d\n", size);

    clock_t start = clock();
    countingSort(arr, size, max_num);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, size, n);
}

void test_radixSort10(int option) {
    if (option == 0) return;
    init(arr, size, seed, max_num);
    printf("\n[Radix Sort (base 10)] size = %d\n", size);

    clock_t start = clock();
    radixSort10(arr, size);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, size, n);
}

void test_radixSort256(int option) {
    if (option == 0) return;
    init(arr, size, seed, max_num);
    printf("\n[Radix Sort (base 256)] size = %d\n", size);

    clock_t start = clock();
    radixSort256(arr, size);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    show_result(arr, size, n);
}