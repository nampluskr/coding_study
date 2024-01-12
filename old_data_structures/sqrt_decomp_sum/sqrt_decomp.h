#pragma once


inline int ceil(int a, int b) { return (a + b - 1) / b; }
int sqrt(int n) {
    double x1 = n;
    double x2 = (x1 + n / x1) / 2;
    while (x1 - x2 > 0.1) {
        x1 = x2;
        x2 = (x1 + n / x1) / 2;
    }
    return x2;
}

template<int N>
struct RangeSumType1 {
    int values[N];
    int blocks[N];      // block sum
    int blockSize;      // block size
    int blockCnt;       // num. of blocks

    void clear() {
        for (int i = 0; i < N; i++) { values[i] = 0; }
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) { blocks[i] = {}; }
    }
    void updatePoint(int idx, int value) {
        values[idx] += value;
        blocks[idx / blockSize] += value;
    }
    int queryRange(int left, int right) {
        int res = 0;
        int s = left / blockSize;   // first block index
        int e = right / blockSize;  // last block index

        if (s == e) {
            for (int i = left; i <= right; i++) { res += values[i]; }
            return res;
        }
        while (left / blockSize == s) { res += values[left++]; }
        for (int i = s + 1; i <= e - 1; i++) { res += blocks[i]; }
        while (right / blockSize == e) { res += values[right--]; }
        return res;
    }
};

struct Block {
    int base, sum;
};

template<int N>
struct RangeSumType2 {
    int values[N];
    Block blocks[N];    // block base, sum
    int blockSize;      // block size
    int blockCnt;       // num. of blocks

    void clear() {
        for (int i = 0; i < N; i++) { values[i] = 0; }
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) { blocks[i] = { 0, 0 }; }
    }
    void updatePoint(int idx, int value) {
        values[idx] += value;
        // update block;
        blocks[idx / blockSize].sum += value;
    }
    void updateRange(int left, int right, int value) {
        int s = left / blockSize;   // first block index
        int e = right / blockSize;  // last block index

        if (s == e) {
            for (int i = left; i <= right; i++) { updatePoint(i, value); }
            return;
        }
        while (left / blockSize == s) { updatePoint(left++, value); }
        for (int i = s + 1; i <= e - 1; i++) {
            // update blocks
            blocks[i].base += value;
            blocks[i].sum += value * blockSize;
        }
        while (right / blockSize == e) { updatePoint(right--, value); }
    }
    int queryPoint(int idx) {
        return values[idx] + blocks[idx / blockSize].base;
    }
    int queryRange(int left, int right) {
        int res = 0;
        int s = left / blockSize;   // first block index
        int e = right / blockSize;  // last block index

        if (s == e) {
            for (int i = left; i <= right; i++) { res += queryPoint(i); }
            return res;
        }
        while (left / blockSize == s) { res += queryPoint(left++); }
        for (int i = s + 1; i <= e - 1; i++) { res += blocks[i].sum; }
        while (right / blockSize == e) { res += queryPoint(right--); }
        return res;
    }
};