#pragma once

#include "..\priority_queue\priority_queue.h"

template<typename T, int max_size>
struct DoubleEndedPQ {
    struct MaxData {
        T data;
        int idx;
        bool operator<(const MaxData& max) const { return data < max.data; }
    };
    struct MinData {
        T data;
        int idx;
        bool operator<(const MinData& min) const { return data > min.data; }
    };
    PriorityQueue<MaxData, max_size> maxHeap;
    PriorityQueue<MinData, max_size> minHeap;
    bool popped[max_size];
    int idx = 0;
    int cnt = 0;

    void clear() {
        while (!maxHeap.empty()) maxHeap.pop();
        while (!minHeap.empty()) minHeap.pop();
        for (int i = 0; i < max_size; i++) popped[i] = {};
        idx = cnt = 0;
    }
    template<typename Heap>
    void refresh(Heap& Q) {
        while (!Q.empty() && popped[Q.top().idx]) Q.pop();
    }
    void push(const T& data) {
        maxHeap.push({ data, idx });
        minHeap.push({ data, idx });
        popped[idx++] = false;
        cnt++;
    }
    void popTop() {
        refresh(maxHeap);
        auto top = maxHeap.top(); maxHeap.pop();
        popped[top.idx] = true;
        cnt--;
    }
    void popBottom() {
        refresh(minHeap);
        auto bottom = minHeap.top(); maxHeap.pop();
        popped[bottom.idx] = true;
        cnt--;
    }
    T top() {
        refresh(maxHeap);
        return maxHeap.top().data;
    }
    T bottom() {
        refresh(minHeap);
        return minHeap.top().data;
    }
    bool empty() { return cnt == 0; }
};