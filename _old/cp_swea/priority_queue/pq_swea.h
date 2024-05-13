/*
1. comment: error check codes
2. Min. Heap (A < B) -> Max. Heap (B < A)
3. tempalte<typename T>
4. int temp -> auto temp
5. const T& value -> const T& value
6. int* value -> T* value
*/

#define MAX_SIZE 1000

template<typename T>
struct PrioirtyQueue {
    T heap[MAX_SIZE];
    int heapSize = 0;
    
    void heapInit(void)
    {
        heapSize = 0;
    }
    
    int heapPush(const T& value)
    {
        // if (heapSize + 1 > MAX_SIZE)
        // {
        //     printf("queue is full!");
        //     return 0;
        // }
    
        heap[heapSize] = value;
    
        int current = heapSize;
        while (current > 0 && heap[(current - 1) / 2] < heap[current]) 
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
        // if (heapSize <= 0)
        // {
        //     return -1;
        // }
    
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
    
            auto temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;
    
            current = child;
        }
        return 1;
    }

    // User methods
    void clear() { heapInit(); }
    void push(const T& value) { heapPush(value); }
    void pop() { T temp; heapPop(&temp); }
    bool empty() { return heapSize == 0; }
    T top() { return heap[0]; }
    int size() { return heapSize; }
};