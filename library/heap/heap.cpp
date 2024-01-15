#include "heap.h"
#include <cstdio>
#include <ctime>

#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

#define MAX_NUM     10

unsigned long long seed = 7;
int arr[MAX_SIZE];
int size = 100;

MaxHeap<int> pq;
const int K = 10;

int rand(unsigned long long seed) {
    seed = seed * 25214903917ULL + 11ULL;
    return (seed >> 16) & 0x3fffffff;
}

void init(int arr[], int size, int seed, int max_num) {
    for (int i = 0; i < size; i++) {
        seed = rand(seed);
        arr[i] = seed % max_num;
    }
    //for (int i = 0; i < size; i++) { printf("%d ", arr[i]); }
    //printf("\n");
}

/////////////////////////////////////////////////////////////////////
void test_heapSort() {
    init(arr, size, seed, MAX_NUM);
    pq.clear();
    clock_t start = clock();

    // push N times: O(NlogN)
    for (int i = 0; i < size; i++)
        pq.push(arr[i]);

    // pop K times: O(KlogN)
    int cnt = 0;
    while (!pq.empty() && cnt < K) {
        int data = pq.top(); pq.pop();
        cnt++;
        printf(">> popped [%2d]: %d\n", cnt, data);
    }
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
}

void test_heapify() {
    init(arr, size, seed, MAX_NUM);
    pq.clear();
    clock_t start = clock();

    // O(N)
    pq.heapify(arr, size);

    // pop K times: O(KlogN)
    int cnt = 0;
    while (!pq.empty() && cnt < K) {
        int data = pq.top(); pq.pop();
        cnt++;
        printf(">> popped [%2d]: %d\n", cnt, data);
    }
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
}

void test_topK1() {
    init(arr, size, seed, MAX_NUM);
    pq.clear();
    clock_t start = clock();

    // push N times: O(NlogK)
    for (int i = 0; i < size; i++) {
        pq.push(-arr[i]);
        if (pq.size() > K) { pq.pop(); }
    }

    // pop K times: O(KlogK)
    int cnt = 0;
    while (!pq.empty() && cnt < K) {
        int data = -pq.top(); pq.pop();
        cnt++;
        printf(">> popped [%2d]: %d\n", cnt, data);
    }
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
}

void test_topK2() {
    init(arr, size, seed, MAX_NUM);
    pq.clear();
    clock_t start = clock();

    // push N times: O(N + KlogK)
    for (int i = 0; i < size; i++) {
        if (pq.size() < K) { pq.push(-arr[i]); }
        else if (-arr[i] < pq.top()) {
            pq.heap[1] = -arr[i];
            pq.siftDown(1);
        }
    }

    // pop K times: O(KlogK)
    int cnt = 0;
    while (!pq.empty() && cnt < K) {
        int data = -pq.top(); pq.pop();
        cnt++;
        printf(">> popped [%2d]: %d\n", cnt, data);
    }
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
}