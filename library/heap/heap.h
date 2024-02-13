#pragma once

template<typename T>
void swap(T& a, T& b) { T temp = a; a = b; b = temp; }

template<typename T, int max_size>
struct PriorityQueue {
    T heap[max_size];
    int cnt = 0;

    void clear() { cnt = 0; }
    void push(const T& data) { heap[++cnt] = data; siftUp(cnt); }
    void pop() { swap(heap[1], heap[cnt--]); siftDown(1); }
    bool empty() { return cnt == 0; }
    T top() { return heap[1]; }
    int size() { return cnt; }

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
    void heapify(const T arr[], int size) {
        clear();
        for (int i = 0; i < size; i++) { heap[++cnt] = arr[i]; }
        for (int i = cnt / 2; i >= 1; i--) { siftDown(i); }
    }
};

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
        bool operator>(const MinData& min) const { return data > min.data; }
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

template<typename T, int max_size>
struct MedianPQ {
    struct MaxData {
        T data;
        MaxData(const T& data) { this->data = data; }
        bool operator<(const MaxData& max) const { return data < max.data; }
    };
    struct MinData {
        T data;
        MinData(const T& data) { this->data = data; }
        bool operator>(const MinData& min) const { return data > min.data; }
    };
    PriorityQueue<MaxData, max_size> leftHeap;
    PriorityQueue<MinData, max_size> rightHeap;

    void clear() {
        while (!leftHeap.empty()) leftHeap.pop();
        while (!rightHeap.empty()) rightHeap.pop();
    }
    void push(const T& data) {
        if (leftHeap.size() == rightHeap.size()) {
            rightHeap.push(data);
            auto top = rightHeap.top(); rightHeap.pop();
            leftHeap.push(top);
        }
        else if (leftHeap.size() > rightHeap.size()) {
            leftHeap.push(data);
            auto top = leftHeap.top(); leftHeap.top();
            rightHeap.push(top);
        }
    }
    void pop() {
        if (leftHeap.size() == rightHeap.size()) {
            rightHeap.pop();
        }
        else if (leftHeap.size() > rightHeap.size()) {
            leftHeap.pop();
        }
    }
    T median() {
        if (leftHeap.size() == rightHeap.size()) {
            return rightHeap.top();
        }
        else if (leftHeap.size() > rightHeap.size()) {
            return leftHeap.top();
        }
    }
    bool empty() { return leftHeap.empty() && rightHeap.empty(); }
};