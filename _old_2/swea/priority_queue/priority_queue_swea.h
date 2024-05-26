#pragma once

/*
min. heap -> max. heap: a < b -> b < a
*/

#define MAX_SIZE 1000

template<typename T>
struct PriorityQueueSWEA {
    T heap[MAX_SIZE];
    int heapSize = 0;

    void heapInit(void)
    {
        heapSize = 0;
    }

    int heapPush(const T& value)
    {
        if (heapSize + 1 > MAX_SIZE)
        {
            // printf("queue is full!");
            return 0;
        }
        heap[heapSize] = value;
        int current = heapSize;

        while (current > 0 && heap[(current - 1) / 2] < heap[current])
        {
            T temp = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = heap[current];
            heap[current] = temp;
            current = (current - 1) / 2;
        }
        heapSize = heapSize + 1;
        return 1;
    }

    int heapPop(T *value)
    {
        if (heapSize <= 0)
        {
            return -1;
        }
        *value = heap[0];
        heapSize = heapSize - 1;
        heap[0] = heap[heapSize];

        int current = 0;
        while (current * 2 + 1 < heapSize)
        {
            int child;
            if (current * 2 + 2 == heapSize)
            {
                child = current * 2 + 1;
            }
            else
            {
                child = heap[current * 2 + 2] < heap[current * 2 + 1] ? current * 2 + 1 : current * 2 + 2;
            }
            if (heap[child] < heap[current])
            {
                break;
            }
            T temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;
            current = child;
        }
        return 1;
    }

    // user code
    void clear() { heapInit(); }
    void push(const T& data) { heapPush(data); }
    void pop() { T temp; heapPop(&temp); }
    bool empty() { return heapSize == 0; }
    T top() { return heap[0]; }
};