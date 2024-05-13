#pragma once

/*
1. error check -> comment
2. template<typename T>
3. int value -> const T& value
4. getFront(), getRear() -> int -> T
5. head -> head, tail -> back
6. size -> max_size
*/

#define MAX 100

template<typename T>
struct Deque {
    T arr[MAX];
    int head;
    int tail;
    int max_size;

    void dequeInit(int n) {
        head = -1;
        tail = 0;
        max_size = n;
    }

    bool isFull() {
        return ((head == 0 && tail == max_size - 1) || head == tail + 1);
    }

    bool isEmpty() {
        return (head == -1);
    }

    void insertFront(const T& value) {
        //if (isFull()) {
        //    printf("Overflow\n");
        //}

        if (head == -1) {
            head = tail = 0;
        }
        else if (head == 0) {
            head = max_size - 1;
        }
        else {
            head = head - 1;
        }

        arr[head] = value;
    }

    void insertRear(const T& value) {
        //if (isFull()) {
        //    printf("Overflow\n");
        //}

        if (head == -1) {
            head = tail = 0;
        }
        else if (tail == max_size - 1) {
            tail = 0;
        }
        else {
            tail = tail + 1;
        }

        arr[tail] = value;
    }

    T getFront() {
        //if (isEmpty()) {
        //    printf("Underflow\n");
        //    return -1;
        //}
        return arr[head];
    }

    T getRear() {
        //if (isEmpty() || tail < 0) {
        //    printf("Underflow\n");
        //    return -1;
        //}
        return arr[tail];
    }

    void deleteFront() {
        //if (isEmpty()) {
        //    printf("Underflow\n");
        //    return;
        //}

        if (head == tail) {
            head = -1;
            tail = -1;
        }
        else if (head == max_size - 1) {
            head = 0;
        }
        else {
            head = head + 1;
        }
    }

    void deleteRear() {
        //if (isEmpty()) {
        //    printf("Underflow\n");
        //    return;
        //}

        if (head == tail) {
            head = -1;
            tail = -1;
        }
        else if (tail == 0) {
            tail = max_size - 1;
        }
        else {
            tail = tail - 1;
        }
    }

    // User defined methods
    int cnt = 0;
    void clear() { dequeInit(MAX); cnt = 0; }
    void push_front(const T& data) { insertFront(data); cnt++; }
    void push_back(const T& data) { insertRear(data); cnt++; }
    void pop_front() { deleteFront(); cnt--; }
    void pop_back() { deleteRear(); cnt--; }
    T front() { return getFront(); }
    T back() { return getRear(); }
    bool empty() { return isEmpty(); }
    int size() { return cnt; }
};
