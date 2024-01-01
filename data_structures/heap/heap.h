#pragma once

template<typename T, int max_size>
struct MaxHeap {
    T heap[max_size];
    int heapSize = 0;

    void clear() { heapSize = 0; }
    void push(const T& data);
    void pop();
    bool empty() { heapSize == 0; }
    T top() { return heap[1]; }
    int size() { return heapSize; }
};

template<typename T, int max_size>
void MaxHeap<T, max_size>::push(const T& data) {
}

template<typename T, int max_size>
void MaxHeap<T, max_size>::pop() {
}