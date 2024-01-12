#pragma once

template<typename T>
inline void swap(T& a, T& b) { T temp = a; a = b; b = temp; }

template<typename T, int max_size>
struct MaxHeap {
    T heap[max_size];
    int heapSize = 0;

    // 기본 함수
    void clear() { heapSize = 0; }
    void push(const T& data);
    void pop();
    bool empty() { return heapSize == 0; }
    T top() { return heap[1]; }
    int size() { return heapSize; }

    // 추가 함수
    void siftUp(int cur);
    void siftDown(int cur);
    void heapity(const T arr[], int size);
};

template<typename T, int max_size>
void MaxHeap<T, max_size>::push(const T& data) {
    if (heapSize == max_size - 1) return;   // 예외 처리

    heapSize++;
    heap[heapSize] = data;

    // Sift up
    int cur = heapSize;
    int parent = cur / 2;
    while (parent >= 1) {
        if (heap[cur] < heap[parent]) break;

        swap(heap[parent], heap[cur]);
        cur = parent;
        parent = cur / 2;
    }
}

template<typename T, int max_size>
void MaxHeap<T, max_size>::pop() {
    if (heapSize == 0) return;      // 예외 처리

    swap(heap[1], heap[heapSize]);
    heapSize--;

    // Sift down
    siftDown(1);
    int cur = 1;
    int child = cur * 2;
    while (child + 1 <= heapSize) {
        if (heap[child] < heap[child + 1]) child++;
        if (heap[child] < heap[cur]) break;

        swap(heap[cur], heap[child]);
        cur = child;
        child = cur * 2;
    }
}

template<typename T, int max_size>
void MaxHeap<T, max_size>::siftUp(int cur) {
    int cur = heapSize;
    int parent = cur / 2;
    while (parent >= 1) {
        if (heap[cur] < heap[parent]) break;

        swap(heap[parent], heap[cur]);
        cur = parent;
        parent = cur / 2;
    }
}

template<typename T, int max_size>
void MaxHeap<T, max_size>::siftDown(int cur) {
    int cur = 1;
    int child = cur * 2;
    while (child + 1 <= heapSize) {
        if (heap[child] < heap[child + 1]) child++;
        if (heap[child] < heap[cur]) break;

        swap(heap[cur], heap[child]);
        cur = child;
        child = cur * 2;
    }
}

template<typename T, int max_size>
void MaxHeap<T, max_size>::heapity(const T arr[], int size) {
    // deep copy
    for (int i = 0; i < size; i++)
        heap[1 + i] = arr[i];
    // heapity
    for (int i = size / 2; i >= 1; i--)
        siftDown(i);
}