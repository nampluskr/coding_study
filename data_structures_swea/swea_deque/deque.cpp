#include<stdio.h>

#define MAX 10

template<typename T>
struct Deque {
    T arr[MAX];
    int front;
    int rear;
    int size;

    void dequeInit(int n=MAX) {
        front = -1;
        rear = 0;
        size = n;
    }

    bool isFull() {
        return ((front == 0 && rear == size - 1) || front == rear + 1);
    }

    bool isEmpty() {
        return (front == -1);
    }

    void insertFront(const T& value) {
        if (isFull()) {
            printf("Overflow\n");
        }

        if (front == -1) {
            front = rear = 0;
        }
        else if (front == 0) {
            front = size - 1;
        }
        else {
            front = front - 1;
        }

        arr[front] = value;
    }

    void insertRear(const T& value) {
        if (isFull()) {
            printf("Overflow\n");
        }

        if (front == -1) {
            front = rear = 0;
        }
        else if (rear == size - 1) {
            rear = 0;
        }
        else {
            rear = rear + 1;
        }

        arr[rear] = value;
    }

    T getFront() {
        // if (isEmpty()) {
        //     printf("Underflow\n");
        //     return -1;
        // }
        return arr[front];
    }

    T getRear() {
        // if (isEmpty() || rear < 0) {
        //     printf("Underflow\n");
        //     return -1;
        // }
        return arr[rear];
    }

    void deleteFront() {
        if (isEmpty()) {
            printf("Underflow\n");
            return;
        }

        if (front == rear) {
            front = -1;
            rear = -1;
        }
        else if (front == size - 1) {
            front = 0;
        }
        else {
            front = front + 1;
        }
    }

    void deleteRear() {
        if (isEmpty()) {
            printf("Underflow\n");
            return;
        }

        if (front == rear) {
            front = -1;
            rear = -1;
        }
        else if (rear == 0) {
            rear = size - 1;
        }
        else {
            rear = rear - 1;
        }
    }
};

struct Data {
    int value, id;
};

template<typename T>
struct Stack: Deque<T> {
    int cnt = 0;
    void clear() { dequeInit(); cnt = 0; }
    void push(const T& data) { insertFront(data); cnt++; }
    void pop() { deleteFront(); cnt--; }
    bool empty() { return isEmpty(); }
    T top() { return getFront(); }
    int size() { return cnt; }
};

template<typename T>
struct Queue: Deque<T> {
    int cnt = 0;
    void clear() { dequeInit(); cnt = 0; }
    void push(const T& data) { insertRear(data); cnt++; }
    void pop() { deleteFront(); cnt--; }
    bool empty() { return isEmpty(); }
    T front() { return getFront(); }
    int size() { return cnt; }
};

// Deque<Data> Q;
Stack<Data> S;
Queue<Data> Q;

int main()
{
    S.clear();
    S.push({ 10, 1 });
    S.push({ 20, 2 });
    S.push({ 30, 3 });

    while (!S.empty()) {
        auto cur = S.top(); S.pop();
        printf("(%d, %d)\n", cur.value, cur.id);
    }

    Q.clear();
    Q.push({ 10, 1 });
    Q.push({ 20, 2 });
    Q.push({ 30, 3 });

    while (!Q.empty()) {
        auto cur = Q.front(); Q.pop();
        printf("(%d, %d)\n", cur.value, cur.id);
    }

    return 0;
}