### [Medians] Min Heap + Max Heap

```cpp
#include <queue>
#include <cstdio>
using namespace std;

struct MedianHeap {
    priority_queue<int> minHeap, maxHeap;

    void clear() {
        while (!minHeap.empty()) minHeap.pop();
        while (!maxHeap.empty()) maxHeap.pop();
    }
    void push(int x) {
        maxHeap.push(x);
        int temp = maxHeap.top(); maxHeap.pop();
        minHeap.push(-temp);

        if (maxHeap.size() < minHeap.size()) {
            temp = -minHeap.top(); minHeap.pop();
            maxHeap.push(temp);
        }
    }
    void pop() {
        if (maxHeap.size() == minHeap.size())
            minHeap.pop();
        else
            maxHeap.pop();
    }
    int median() { 
        if (maxHeap.size() == minHeap.size())
            return -minHeap.top();
        else
            return maxHeap.top();
    }
    bool empty() { return maxHeap.empty() && minHeap.empty(); }

};

MedianHeap Q;

int main()
{
    int arr[] = { 5, 15, 1, 3, 2, 8, 7, 9, 10, 6, 11, 4 };
    int n = sizeof(arr) / sizeof(arr[0]);

    Q.clear();
    for (int i = 0; i < n; i++) { Q.push(arr[i]); }

    while (!Q.empty()) {
        int med = Q.median(); Q.pop();
        printf(">> median = %2d\n", med);
    }

    return 0;
}
```

### [Medians] Insertion Sort

```cpp
#include <cstdio>

int binarySearch(int arr[], float x, int low, int high) {
    if (low >= high) {
        return (x > arr[low]) ? (low + 1) : low;
    }

    int mid = (low + high) / 2;
    if (x == arr[mid])
        return mid + 1;
    else if (x > arr[mid])
        return binarySearch(arr, x, mid + 1, high);
    else
        return binarySearch(arr, x, low, mid - 1);
}

#define MAX_SIZE 100

struct MedianQueue {
    int arr[MAX_SIZE];
    int cnt = 0;

    void clear() { cnt == 0; }
    void push(int x) {
        if (empty()) { arr[cnt++] = x; }
        else {
            int j = cnt - 1;
            int pos = binarySearch(arr, x, 0, j);
            while (j >= pos) { arr[j + 1] = arr[j]; j--; }
            arr[j + 1] = x;
            cnt++;
        }
    }
    void pop() {
        for (int i = cnt / 2; i < cnt - 1; i++)
            arr[i] = arr[i + 1];
        cnt--;
    }
    bool empty() { return cnt == 0; }
    int median() { return arr[cnt / 2]; }
};

MedianQueue Q;


int main()
{
    int arr[] = { 5, 15, 1, 3, 2, 8, 7, 9, 10, 6, 11, 4 };
    int n = sizeof(arr) / sizeof(arr[0]);

    Q.clear();
    for (int i = 0; i < n; i++)
        Q.push(arr[i]);
    
    while (!Q.empty()) {
        int med = Q.median(); Q.pop();
        printf(">> median = %2d\n", med);
    }

    return 0;
}
```
