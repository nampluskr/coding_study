#pragma once

#define INF 0x7fffffff

inline int get_max(int a, int b) { return (a < b) ? b : a; }
inline int get_min(int a, int b) { return (a < b) ? a : b; }
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
struct RangeMaxType1 {
    int values[N];
    int blocks[N];      // block max
    int blockSize;      // block size
    int blockCnt;       // num. of blocks

    void clear() {
        for (int i = 0; i < N; i++) { values[i] = 0; }
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) { blocks[i] = -INF; }
    }
    void updatePoint(int idx, int value) {
        values[idx] += value;

        // update blcok
        int bIdx = idx / blockSize;
        int left = bIdx * blockSize;
        int right = get_min((bIdx + 1) * blockSize - 1, N - 1);

        blocks[bIdx] = -INF;
        for (int i = left; i <= right; i++) {
            if (blocks[bIdx] < values[i]) { blocks[bIdx] = values[i]; }
        }
    }
    int queryRange(int left, int right) {
        int res = -INF;
        int s = left / blockSize;   // first block index
        int e = right / blockSize;  // last block index

        if (s == e) {
            for (int i = left; i <= right; i++) { 
                if (res < values[i]) { res = values[i]; }
            }
            return res;
        }
        while (left / blockSize == s) {
            if (res < values[left]) { res = values[left]; }
            left++;
        }
        for (int i = s + 1; i <= e - 1; i++) { 
            if (res < blocks[i]) { res = blocks[i]; }
        }
        while (right / blockSize == e) {
            if (res < values[right]) { res = values[right]; }
            right--;
        }
        return res;
    }
};

template<int N>
struct RangeMaxType2 {
    struct Block {
        int base, max;
    };
    int values[N];
    Block blocks[N];    // block base, max
    int blockSize;      // block size
    int blockCnt;       // num. of blocks

    void clear() {
        for (int i = 0; i < N; i++) { values[i] = 0; }
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) { blocks[i] = { 0, -INF }; }
    }
    void updatePoint(int idx, int value) {
        values[idx] += value;

        // update blcok
        int bIdx = idx / blockSize;
        int left = bIdx * blockSize;
        int right = get_min((bIdx + 1) * blockSize - 1, N - 1);

        blocks[bIdx].max = -INF;
        for (int i = left; i <= right; i++) {
            if (blocks[bIdx].max < queryPoint(i)) {
                blocks[bIdx].max = queryPoint(i);
            }
        }
    }
    void updateRange(int left, int right, int value) {
        int s = left / blockSize;   // first block index
        int e = right / blockSize;  // last block index

        if (s == e) {
            for (int i = left; i <= right; i++) { updatePoint(i, value); }
            return;
        }
        while (left / blockSize == s) { updatePoint(left, value); left++; }
        for (int i = s + 1; i <= e - 1; i++) {
            blocks[i].base += value;
            blocks[i].max += value;
        }
        while (right / blockSize == e) { updatePoint(right, value); right--; }
    }
    int queryPoint(int idx) {
        return values[idx] + blocks[idx / blockSize].base;
    }
    int queryRange(int left, int right) {
        int res = -INF;
        int s = left / blockSize;   // first block index
        int e = right / blockSize;  // last block index

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
            if (res < blocks[i].max) { res = blocks[i].max; }
        }
        while (right / blockSize == e) {
            if (res < queryPoint(right)) { res = queryPoint(right); }
            right--;
        }
        return res;
    }
};

struct Pair {
    int idx, value;
};

template<int N>
struct RangeMaxType3 {
    struct Block {
        int base;
        Pair max;
    };
    int values[N];
    Block blocks[N];    // block base, { max idx, max value }
    int blockSize;      // block size
    int blockCnt;       // num. of blocks

    void clear() {
        for (int i = 0; i < N; i++) { values[i] = 0; }
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) { blocks[i] = { 0, { -1, -INF } }; }
    }
    void updatePoint(int idx, int value) {
        values[idx] += value;

        // update blcok
        int bIdx = idx / blockSize;
        if (idx != blocks[bIdx].max.idx) {
            if (blocks[bIdx].max.value < queryPoint(idx)) {
                blocks[bIdx].max = { idx, queryPoint(idx) };
            }
        }
        else {
            int left = bIdx * blockSize;
            int right = get_min((bIdx + 1) * blockSize - 1, N - 1);

            blocks[bIdx].max.value = -INF;
            for (int i = left; i <= right; i++) {
                if (blocks[bIdx].max.value < queryPoint(i)) {
                    blocks[bIdx].max = { i, queryPoint(i) };
                }
            }
        }
    }
    void updateRange(int left, int right, int value) {
        int s = left / blockSize;   // first block index
        int e = right / blockSize;  // last block index

        if (s == e) {
            for (int i = left; i <= right; i++) { updatePoint(i, value); }
            return;
        }
        while (left / blockSize == s) { updatePoint(left, value); left++; }
        for (int i = s + 1; i <= e - 1; i++) {
            blocks[i].base += value;
            blocks[i].max.value += value;
        }
        while (right / blockSize == e) { updatePoint(right, value); right--; }
    }
    int queryPoint(int idx) {
        return values[idx] + blocks[idx / blockSize].base;
    }
    int queryRange(int left, int right) {
        int res = -INF;
        int s = left / blockSize;   // first block index
        int e = right / blockSize;  // last block index

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
            if (res < blocks[i].max.value) { res = blocks[i].max.value; }
        }
        while (right / blockSize == e) {
            if (res < queryPoint(right)) { res = queryPoint(right); }
            right--;
        }
        return res;
    }
};