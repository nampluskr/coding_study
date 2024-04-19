#include <stdio.h>

#define MAX_SIZE 100

template<typename T>
struct PriorityQueue {
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
            printf("queue is full!");
            return 0;
        }

        heap[heapSize] = value;

        int current = heapSize;
        while (current > 0 && heap[current] < heap[(current - 1) / 2])
        {
            auto temp = heap[(current - 1) / 2];
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
                child = heap[current * 2 + 1] < heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
            }

            if (heap[current] < heap[child])
            {
                break;
            }

            auto temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;
            current = child;
        }
        return 1;
    }

    // ==============================================================================
    void clear() { heapInit(); }
    void push(const T& value) { heapPush(value); }
    void pop() { T temp; heapPop(&temp); }
    bool empty() { return heapSize == 0; }
    T top() { return heap[0]; }
    int size() { return heapSize; }
};

struct Data {
    int value, id;
    bool operator<(const Data& data) const {
        return (value > data.value) || (value == data.value && id < data.id);
    }
};

PriorityQueue<Data> Q;

int main()
{
    Q.clear();
    Q.push({ 200, 20 });
    Q.push({ 100, 10 });
    Q.push({ 300, 30 });
    Q.push({ 100, 10 });

    while (!Q.empty()) {
        auto top = Q.top(); Q.pop();
        printf("(%d, %d)\n", top.value, top.id);
    }


    return 0;
}