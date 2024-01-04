### [quick.h]

```cpp
#pragma once

inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

// Hoare Partition
int partition(int arr[], int left, int right) {
    int pivot = arr[left];
    int i = left + 1, j = right;

    while (i <= j) {
        while (i <= j && arr[i] <= pivot) { i++; }
        while (i <= j && pivot <= arr[j]) { j--; }
        if (i <= j) { swap(arr[i], arr[j]); }
    }
    swap(arr[left], arr[j]);
    return j;
}

// Lumuto Partition
//int partition(int arr[], int left, int right) {
//    int pivot = arr[right];
//    int i = left - 1;
//
//    for (int j = left; j < right; j++)
//        if (arr[j] <= pivot) { swap(arr[++i], arr[j]); }
//    swap(arr[++i], arr[right]);
//    return i;
//}


void quickSort(int arr[], int left, int right) {
    if (right <= left) return;

    int pIdx = partition(arr, left, right);
    quickSort(arr, left, pIdx - 1);
    quickSort(arr, pIdx + 1, right);
}

int quickSelect(int arr[], int k, int left, int right) {
    if (right <= left) return arr[left];

    int pIdx = partition(arr, left, right);
    if (k < pIdx) quickSelect(arr, k, left, pIdx - 1);
    else if (k > pIdx) quickSelect(arr, k, pIdx + 1, right);
    else return arr[pIdx];
}
```

### [test_quick.cpp]

```cpp
// https://notepad96.tistory.com/216
#include "quick.h"
#include <cstdio>
using namespace std;

const int N = 7;    // num. of data
int dataArray[N] = { 1, 7, 4, 3, 2, 9, 4 };
int arr[N];

int main() {
    // quick sort
    printf(">> Initial: ");
    for (int i = 0; i < N; i++) { arr[i] = dataArray[i]; }
    for (int i = 0; i < N; i++) { printf("%d ", arr[i]); }
    printf("\n");

    quickSort(arr, 0, N - 1);

    printf(">> Sorted: ");
    for (int i = 0; i < N; i++) { printf("%d ", arr[i]); }
    printf("\n");

    // quick select
    for (int i = 0; i < N; i++) { arr[i] = dataArray[i]; }
    int k = (N + 1) / 2;    // ceil(N / 2) median
    int num = quickSelect(arr, k - 1, 0, N - 1);
    printf(">> %d-th element: %d\n", k, num);

    return 0;
}
```
