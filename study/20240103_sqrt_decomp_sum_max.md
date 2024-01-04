## RangeMaxType2 와 RangeMaxType3 의 결과 상이 - 디버깅 할 것

### func.h

```cpp
#pragma once

#define INF 0x7fffffff

inline int get_min(int a, int b) { return (a < b) ? a : b; }
inline int get_max(int a, int b) { return (a < b) ? b : a; }
inline int ceil(int a, int b) { return (a + b - 1) / b; }
int sqrt(int n) { 
    double x1 = n;
    double x2 = (x1 + n / x1) / 2;
    while (x1 - x2 > 0.1) {
        x1 = x2;
        x2 = (x1 + n / x1) / 2;
    }
    return (int)x2;
}
```

### range_sum.h

```cpp
#pragma once

// Range Sum Type-1 (1) updatePoint (2) queryRange
// Range Sum Type-2 (1) updatePoint (2) updateRange (3) queryRange (4) queryPoint

#include "func.h"

template<int N>
struct RangeSumType1 {
    int blocks[N];      // block sum
    int* arr;
    int blockSize;
    int blockCnt;

    RangeSumType1() { init(); }
    void init() {
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) {
            blocks[i] = 0;    // default value
        }
    }
    void build(int arr[]) {
        this->arr = arr;
        for (int i = 0; i < blockCnt; i++) {
            blocks[i] = 0;    // default value
        }
        for (int i = 0; i < N; i++) {
            // update block
            blocks[i / blockSize] += arr[i];
        }
    }
    void updatePoint(int idx, int value) {
        arr[idx] += value;
        // update block
        blocks[idx / blockSize] += value;
    }
    int queryRange(int left, int right) {
        int res = 0;        // default value
        int s = left / blockSize;
        int e = right / blockSize;

        if (s == e) {
            for (int i = left; i <= right; i++) { res += arr[i]; }
            return res;
        }
        while (left / blockSize == s) { res += arr[left++]; }
        for (int i = s + 1; i <= e - 1; i++) {
            // query block
            res += blocks[i];
        }
        while (right / blockSize == e) { res += arr[right--]; }
        return res;
    }
};

template<int N>
struct RangeSumType2 {
    struct Block {
        int base;       // update range => query point
        int sum;        // update point/range => query range
    };
    Block blocks[N];
    int* arr;
    int blockSize;
    int blockCnt;

    RangeSumType2() { init(); }
    void init() {
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) {
            blocks[i] = { 0, 0 };    // default value
        }
    }
    void build(int arr[]) {
        this->arr = arr;
        for (int i = 0; i < blockCnt; i++) {
            blocks[i] = { 0, 0 };    // default value
        }
        for (int i = 0; i < N; i++) {
            // update block
            blocks[i / blockSize].sum += arr[i];
        }
    }

    void updatePoint(int idx, int value) {
        arr[idx] += value;
        // update block
        blocks[idx / blockSize].sum += value;
    }
    void updateRange(int left, int right, int value) {
        int s = left / blockSize;
        int e = right / blockSize;

        if (s == e) {
            for (int i = left; i <= right; i++) { updatePoint(i, value); }
            return;
        }
        while (left / blockSize == s) { updatePoint(left++, value); }
        for (int i = s + 1; i <= e - 1; i++) {
            // update block
            blocks[i].base += value;
            blocks[i].sum += value * blockSize;
        }
        while (right / blockSize == e) { updatePoint(right--, value); }
    }
    int queryPoint(int idx) {
        return arr[idx] + blocks[idx / blockSize].base;
    }
    int queryRange(int left, int right) {   
        int res = 0;
        int s = left / blockSize;
        int e = right / blockSize;

        if (s == e) {
            for (int i = left; i <= right; i++) { res += queryPoint(i); }
            return res;
        }
        while (left / blockSize == s) { res += queryPoint(left++); }
        for (int i = s + 1; i <= e - 1; i++) { 
            // query block
            res += blocks[i].sum;
        }
        while (right / blockSize == e) { res += queryPoint(right--); }
        return res;
    }

};
```

### range_max.h

```cpp
#pragma once

// Range Max Type-1 (1) updatePoint (2) queryRange
// Range Max Type-2 (1) updatePoint (2) updateRange (3) queryRange (4) queryPoint
// Range Max Type-3 (1) updatePoint(optimized) (2) updateRange (3) queryRange (4) queryPoint

#include "func.h"

template<int N>
struct RangeMaxType1 {
    int blocks[N];      // block max value
    int* arr;
    int blockSize;
    int blockCnt;

    RangeMaxType1() { init(); }
    void init() {
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) {
            blocks[i] = -INF;    // default value
        }
    }
    void build(int arr[]) {
        this->arr = arr;
        for (int i = 0; i < blockCnt; i++) {
            blocks[i] = -INF;    // default value
        }
        for (int i = 0; i < N; i++) {
            // update block
            int bIdx = i / blockSize;
            if (blocks[bIdx] < arr[i]) { blocks[bIdx] = arr[i]; };
        }
    }
    void updatePoint(int idx, int value) {
        arr[idx] += value;

        // update block for values [left, right]
        int bIdx = idx / blockSize;
        int left = bIdx * blockSize;
        int right = get_min((bIdx + 1) * blockSize - 1, N - 1);
        blocks[bIdx] = -INF;
        for (int i = left; i <= right; i++) {
            blocks[bIdx] = get_max(blocks[bIdx], arr[idx]);
        }
    }
    int queryRange(int left, int right) {
        int res = -INF;    // max default
        int s = left / blockSize;
        int e = right / blockSize;

        if (s == e) {
            for (int i = left; i <= right; i++) {
                if (res < arr[i]) { res = arr[i]; }
            }
            return res;
        }
        while (left / blockSize == s) {
            if (res < arr[left]) { res = arr[left]; }
            left++;
        }
        for (int i = s + 1; i <= e - 1; i++) {
            // query block
            if (res < blocks[i]) { res = blocks[i]; }
        }
        while (right / blockSize == e) {
            if (res < arr[right]) { res = arr[right]; }
            right--;
        }
        return res;
    }
};

template<int N>
struct RangeMaxType2 {
    struct Block {
        int base;       // update range => query point
        int max;        // update point/range => query range
    };
    Block blocks[N];
    int* arr;
    int blockSize;
    int blockCnt;

    RangeMaxType2() { init(); }
    void init() {
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) {
            blocks[i] = { 0, -INF };    // default value
        }
    }
    void build(int arr[]) {
        this->arr = arr;
        for (int i = 0; i < blockCnt; i++) {
            blocks[i] = { 0, -INF };    // default value
        }
        for (int i = 0; i < N; i++) {
            // update block
            int bIdx = i / blockSize;
            blocks[bIdx].base = 0;
            if (blocks[bIdx].max < arr[i]) { blocks[bIdx].max = arr[i]; };
        }
    }
    void updatePoint(int idx, int value) {
        arr[idx] += value;

        // update block for values [left, right]
        int bIdx = idx / blockSize;
        int left = bIdx * blockSize;
        int right = get_min((bIdx + 1) * blockSize - 1, N - 1);
        blocks[bIdx].max = -INF;
        for (int i = left; i <= right; i++) {
            blocks[bIdx].max = get_max(blocks[bIdx].max, queryPoint(idx));
        }
    }
    void updateRange(int left, int right, int value) {
        int s = left / blockSize;
        int e = right / blockSize;

        if (s == e) {
            for (int i = left; i <= right; i++) { updatePoint(i, value); }
            return;
        }
        while (left / blockSize == s) { updatePoint(left++, value); }
        for (int i = s + 1; i <= e - 1; i++) {
            // update block
            blocks[i].base += value;
            blocks[i].max += value;
        }
        while (right / blockSize == e) { updatePoint(right--, value); }
    }
    int queryPoint(int idx) {
        return arr[idx] + blocks[idx / blockSize].base;
    }
    int queryRange(int left, int right) {
        int res = -INF;    // max default
        int s = left / blockSize;
        int e = right / blockSize;

        if (s == e) {
            for (int i = left; i <= right; i++) {
                if (res < queryPoint(i)) { res = queryPoint(i); }
            }
            return res;
        }
        while (left / blockSize == s) { 
            if (res < queryPoint(left)) { res = queryPoint(left); }
            left++;
        }
        for (int i = s + 1; i <= e - 1; i++) {
            // query block
            if (res < blocks[i].max) { res = blocks[i].max; }
        }
        while (right / blockSize == e) {
            if (res < queryPoint(right)) { res = queryPoint(right); }
            right--;
        }
        return res;
    }
};


template<int N>
struct RangeMaxType3 {
    struct Pair {
        int idx, value;
    };
    struct Block {
        int base;       // update range => query point
        Pair max;        // update point/range => query range
    };
    Block blocks[N];
    int* arr;
    int blockSize;
    int blockCnt;

    RangeMaxType3() { init(); }
    void init() {
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) {
            blocks[i].base = 0;             // default value
            blocks[i].max = { -1, -INF };   // default value
        }
    }
    void build(int arr[]) {
        this->arr = arr;
        for (int i = 0; i < blockCnt; i++) {
            blocks[i].base = 0;             // default value
            blocks[i].max = { -1, -INF };   // default value
        }
        for (int i = 0; i < N; i++) {
            // update block
            int bIdx = i / blockSize;
            if (blocks[bIdx].max.value < arr[i]) {
                blocks[bIdx].max = { i, arr[i] };
            };
        }
    }
    void updatePoint(int idx, int value) {
        arr[idx] += value;

        // update block for values [left, right]
        int bIdx = idx / blockSize;
        if (idx != blocks[bIdx].max.idx) {
            if (blocks[bIdx].max.value < queryPoint(idx)) {
                blocks[bIdx].max = { idx, queryPoint(idx) };
            };
        }
        else {
            int left = bIdx * blockSize;
            int right = get_min((bIdx + 1) * blockSize - 1, N - 1);
            blocks[bIdx].max.value = -INF;
            for (int i = left; i <= right; i++) {
                if (blocks[bIdx].max.value < queryPoint(i)) {
                    blocks[bIdx].max = { i, queryPoint(i) };
                };
            }
        }
    }
    void updateRange(int left, int right, int value) {
        int s = left / blockSize;
        int e = right / blockSize;

        if (s == e) {
            for (int i = left; i <= right; i++) { updatePoint(i, value); }
            return;
        }
        while (left / blockSize == s) { updatePoint(left++, value); }
        for (int i = s + 1; i <= e - 1; i++) {
            // update block
            blocks[i].base += value;
            blocks[i].max.value += value;
        }
        while (right / blockSize == e) { updatePoint(right--, value); }
    }
    int queryPoint(int idx) {
        return arr[idx] + blocks[idx / blockSize].base;
    }
    int queryRange(int left, int right) {
        int res = -INF;    // max default
        int s = left / blockSize;
        int e = right / blockSize;

        if (s == e) {
            for (int i = left; i <= right; i++) {
                if (res < queryPoint(i)) { res = queryPoint(i); }
            }
            return res;
        }
        while (left / blockSize == s) {
            if (res < queryPoint(left)) { res = queryPoint(left); }
            left++;
        }
        for (int i = s + 1; i <= e - 1; i++) {
            // query block
            if (res < blocks[i].max.value) { res = blocks[i].max.value; }
        }
        while (right / blockSize == e) {
            if (res < queryPoint(right)) { res = queryPoint(right); }
            right--;
        }
        return res;
    }
};
```

### test_sqrt_decomp.cpp

```cpp

#include <cstdio>
#include "range_max.h"
#include "range_sum.h"

#define N   10

int arr[N] = {};

RangeSumType1<N> rngSum1;
RangeSumType2<N> rngSum2;
RangeMaxType1<N> rngMax1;
RangeMaxType2<N> rngMax2;
RangeMaxType3<N> rngMax3;


void test_RangeSumType1() {
    int res;
    rngSum1.init();
    
    for (int i = 0; i < N; i++) { arr[i] = i + 1; }
    rngSum1.build(arr);

    res = rngSum1.queryRange(0, 9);
    printf(">> Range [0, 9]: sum = %2d\n", res);

    rngSum1.updatePoint(0, 10);
    res = rngSum1.queryRange(0, 9);
    printf(">> Range [0, 9]: sum = %2d\n", res);

    rngSum1.updatePoint(9, 10);
    res = rngSum1.queryRange(0, 9);
    printf(">> Range [0, 9]: sum = %2d\n", res);
}

void test_RangeSumType2() {
    int res;
    rngSum2.init();
    rngSum2.build(arr);

    res = rngSum2.queryRange(0, 9);
    printf(">> Range [0, 9]: sum = %2d\n", res);

    rngSum2.updateRange(0, 9, 1);
    res = rngSum2.queryRange(0, 9);
    printf(">> Range [0, 9]: sum = %2d\n", res);

    rngSum2.updateRange(0, 2, 1);
    res = rngSum2.queryRange(0, 9);
    printf(">> Range [0, 9]: sum = %2d\n", res);

    rngSum2.updatePoint(9, -10);
    res = rngSum2.queryRange(0, 9);
    printf(">> Range [0, 9]: sum = %2d\n", res);
}

void test_RangeMaxType1() {
    int res;
    rngMax1.init();

    for (int i = 0; i < N; i++) { arr[i] = i + 1; }
    rngMax1.build(arr);

    res = rngMax1.queryRange(0, 9);
    printf(">> Range [0, 9]: max = %2d\n", res);

    rngMax1.updatePoint(0, 10);
    res = rngMax1.queryRange(0, 9);
    printf(">> Range [0, 9]: sum = %2d\n", res);

    rngMax1.updatePoint(9, 10);
    res = rngMax1.queryRange(0, 9);
    printf(">> Range [0, 9]: sum = %2d\n", res);
}

void test_RangeMaxType2() {
    int res;
    rngMax2.init();

    for (int i = 0; i < N; i++) { arr[i] = i + 1; }
    rngMax2.build(arr);

    res = rngMax2.queryRange(0, 9);
    printf(">> Range [0, 9]: max = %2d\n", res);

    rngMax2.updateRange(0, 4, 10);
    res = rngMax2.queryRange(0, 9);
    printf(">> Range [0, 9]: max = %2d\n", res);

    rngMax2.updateRange(5, 9, 10);
    res = rngMax2.queryRange(0, 9);
    printf(">> Range [0, 9]: max = %2d\n", res);

    rngMax2.updatePoint(9, -10);
    res = rngMax2.queryRange(0, 9);
    printf(">> Range [0, 9]: max = %2d\n", res);
}

void test_RangeMaxType3() {
    int res;
    rngMax3.init();

    for (int i = 0; i < N; i++) { arr[i] = i + 1; }
    rngMax3.build(arr);

    res = rngMax3.queryRange(0, 9);
    printf(">> Range [0, 9]: max = %2d\n", res);

    rngMax3.updateRange(0, 4, 10);
    res = rngMax3.queryRange(0, 9);
    printf(">> Range [0, 9]: max = %2d\n", res);

    rngMax3.updateRange(5, 9, 10);
    res = rngMax3.queryRange(0, 9);
    printf(">> Range [0, 9]: max = %2d\n", res);

    rngMax3.updatePoint(9, -10);
    res = rngMax3.queryRange(0, 9);
    printf(">> Range [0, 9]: max = %2d\n", res);
}

int main()
{
    //printf("\n*** Range Sum Type-1 ***\n");
    //test_RangeSumType1();
    //
    //printf("\n*** Range Sum Type-2 ***\n");
    //test_RangeSumType2();

    printf("\n*** Range Max Type-1 ***\n");
    test_RangeMaxType1();

    printf("\n*** Range Max Type-2 ***\n");
    test_RangeMaxType2();

    printf("\n*** Range Max Type-3 ***\n");
    test_RangeMaxType3();

    return 0;
}
```
