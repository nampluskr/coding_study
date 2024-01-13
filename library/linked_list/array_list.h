#pragma once

template<typename Type, int max_size>
struct ArrayList {
    Type arr[max_size * 2];
    int head = max_size - 1;
    int tail = max_size - 1;
    int cnt = 0;

    void clear() { head = tail = max_size - 1; cnt = 0; }
    void push_back(const Type& data) {
        if (cnt == max_size) return;
        if (head == -1) { head++; }
        arr[++tail] = data; cnt++;
    }
    void push_front(const Type& data) {
        if (cnt == max_size) return;
        if (head == max_size - 1) { tail--; }
        arr[--head] = data; cnt++;
    }
    void pop_back() {
        tail--; cnt--;
        if (tail < head) { head = tail = max_size - 1; }
    }
    void pop_front() {
        head++; cnt--;
        if (tail < head) { head = tail = max_size - 1; }
    }
    bool empty() { return cnt == 0; }  // head == max_size - 1
    Type front() { return arr[head]; }
    Type back() { return arr[tail]; }
    int size() { return cnt; }
};

template<typename Type, int max_size>
struct ArrayStack {
    Type arr[max_size];
    int head = -1;
    int tail = -1;
    int cnt = 0;

    void clear() { head = tail = -1; cnt = 0; }
    void push(const Type& data) {
        if (cnt == max_size) return;
        if (head == -1) { head++; }
        arr[++tail] = data; cnt++;
    }
    void pop() {
        tail--; cnt--;
        if (tail < head) { head = tail = -1; }
    }
    bool empty() { return cnt == 0; }  // head == - 1
    Type top() { return arr[tail]; }
    int size() { return cnt; }
};


template<typename Type, int max_size>
struct ArrayQueue {
    Type arr[max_size];
    int head = -1;
    int tail = -1;
    int cnt = 0;

    void clear() { head = tail = -1; cnt = 0; }
    void push(const Type& data) {
        if (cnt == max_size) return;
        if (head == -1) { head++; }
        arr[++tail] = data; cnt++;
    }
    void pop() {
        head++; cnt--;
        if (head > tail) { head = tail = -1; }
    }
    bool empty() { return cnt == 0; }  // head == - 1
    Type front() { return arr[head]; }
    int size() { return cnt; }
};