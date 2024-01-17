#pragma once

template<typename T>
void swap(T& a, T& b) { T temp = a; a = b; b = temp; }

template<typename T, int max_size>
struct MaxHeap {
    T heap[max_size];
    int cnt = 0;

    void clear() { cnt = 0; }
    void push(const T& data) { heap[++cnt] = data; siftUp(cnt); }
    void pop() { swap(heap[1], heap[cnt--]); siftDown(1); }
    bool empty() { return cnt == 0; }
    T top() { return heap[1]; }

    void siftUp(int cur) {
        int parent = cur / 2;
        while (parent >= 1) {
            if (heap[cur] < heap[parent]) break;
            swap(heap[cur], heap[parent]);
            cur = parent; parent = cur / 2;
        }
    }
    void siftDown(int cur) {
        int child = cur * 2;
        while (child <= cnt) {
            if (child + 1 <= cnt && heap[child] < heap[child + 1]) child++;
            if (heap[child] < heap[cur]) break;
            swap(heap[child], heap[cur]);
            cur = child; child = cur * 2;
        }
    }
    void heapify() {
        for (int i = cnt / 2; i >= 1; i--) { siftDown(i); }
    }
};