#pragma once

#include "..\priority_queue\priority_queue.h"

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