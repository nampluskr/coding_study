#include "array_list.h"
#include <cstdio>

ArrayList<int, 10> L;
ArrayStack<int, 10> S;
ArrayQueue<int, 10> Q;

template<typename T>
void printArray(const T& list) {
    if (list.cnt > 0) {
        for (int i = list.head; i <= list.tail; i++)
            printf("[%d]->", list.arr[i]);
    }
    printf("null\n");
}

void test_arrayList() {
    L.clear();
    L.push_front(1);
    L.push_front(2);
    L.push_front(3);
    L.push_front(4);
    printArray(L);

    L.clear();
    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    L.push_back(4);
    printArray(L);
}

void test_arrayStack() {
    S.clear();
    S.push(1);
    S.push(2);
    S.push(3);
    S.push(4);
    printArray(S);

    while (!S.empty()) {
        int data = S.top(); S.pop();
        printf(">> popped: %d\n", data);
    }
    printArray(S);
}

void test_arrayQueue() {
    Q.clear();
    Q.push(1);
    Q.push(2);
    Q.push(3);
    Q.push(4);
    printArray(Q);

    while (!Q.empty()) {
        int data = Q.front(); Q.pop();
        printf(">> popped: %d\n", data);
    }
    printArray(Q);
}