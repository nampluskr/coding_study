#pragma once 

#define MAX 100

template<typename T>
struct DequeSWEA {
    T arr[MAX];
    int head = -1;
    int tail = 0;
    int size = MAX;

    void clear() {
        head = -1;
        tail = 0;
        size = MAX;
    }

    bool full() {
        return ((head == 0 && tail == size - 1) || head == tail + 1);
    }

    bool empty() {
        return (head == -1);
    }

    void push_front(const T& value) {
        if (head == -1) {
            head = tail = 0;
        }
        else if (head == 0) {
            head = size - 1;
        } else {
            head = head - 1;
        }
        arr[head] = value;
    }

    void push_back(const T& value) {
        if (head == -1) {
            head = tail = 0;
        } else if (tail == size - 1) {
            tail = 0;
        } else {
            tail = tail + 1;
        }
        arr[tail] = value;
    }

    T front() {
        return arr[head];
    }

    T back() {
        return arr[tail];
    }

    void pop_front() {
        if (head == tail) {
            head = -1;
            tail = -1;
        } else if (head == size - 1) {
            head = 0;
        } else {
            head = head + 1;
        }
    }

    void pop_back() {
        if (head == tail) {
            head = -1;
            tail = -1;
        } else if (tail == 0) {
            tail = size - 1;
        } else {
            tail = tail - 1;
        }
    }
};