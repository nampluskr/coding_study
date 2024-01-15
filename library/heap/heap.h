#pragma once

#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

template<typename T>
void swap(T& a, T& b) { T temp = a; a = b; b = temp; }

template<typename T>
struct MaxHeap {
    T heap[MAX_SIZE];
    int heapSize = 0;

    void clear() { 
        heapSize = 0; 
        //for (int i = 0; i < MAX_SIZE; i++) heap[i] = 0;
    }
    void push(const T& data) {
        if (heapSize == MAX_SIZE - 1) { return; }
        heapSize++;
        heap[heapSize] = data;
        siftUp(heapSize);

    }
    void pop() {
        if (heapSize == 0) { return; }
        swap(heap[1], heap[heapSize]);
        heapSize--;
        siftDown(1);
    }
    bool empty() { return heapSize == 0; }
    T top() { return heap[1]; }
    int size() { return heapSize; }

    void siftUp(int idx) {
        int cur = idx;
        int parent = cur / 2;
        while (parent >= 1) {
            if (heap[cur] < heap[parent]) break;
            swap(heap[cur], heap[parent]);
            cur = parent;
            parent = cur / 2;
        }
    } 
    void siftDown(int idx) {
        int cur = idx;
        int child = cur * 2;
        while (child <= heapSize) {
            if (child + 1 <= heapSize && heap[child] < heap[child + 1]) child++;
            if (heap[child] < heap[cur]) break;
            swap(heap[child], heap[cur]);
            cur = child;
            child = cur * 2;
        }
    }
    void heapify(const T arr[], int size) {
        heapSize = 0;
        for (int i = 0; i < size; i++)
            heap[++heapSize] = arr[i];
        for (int i = heapSize / 2; i >= 1; i--)
            siftDown(i);
    }
};