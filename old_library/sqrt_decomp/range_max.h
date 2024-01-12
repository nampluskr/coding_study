#pragma once

// func.cpp
extern int sqrt(int);
extern int ceil(int, int);
extern int min(int, int);
extern int max(int, int);

#define INF 0x7fffffff

 //point update / range query
template<int N>
struct SqrtDecompMaxType1 {
    int blocks[N];      // block max
    int blockSize;
    int blockCnt;
    int values[N];

    void init() {
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) { blocks[i] = { -INF }; }
    }
    void build(const int arr[]) {
        for (int i = 0; i < N; i++) { updatePoint(i, arr[i]); }
    }
    void updatePoint(int idx, int value);
    int queryRange(int left, int right);
};

template<int N>
void SqrtDecompMaxType1<N>::updatePoint(int idx, int value) {
    values[idx] += value;

    int bIdx = idx / blockSize;
    int left = bIdx * blockSize;                        // the first index
    int right = min((bIdx + 1) * blockSize - 1, N - 1); // the last index
    blocks[bIdx] = -INF;
    for (int i = left; i <= right; i++) {
        if (blocks[bIdx] < value) { blocks[bIdx] = value; }
    }
}

template<int N>
int SqrtDecompMaxType1<N>::queryRange(int left, int right) {
    int res = -INF;
    int s = left / blockSize;   // the first block index
    int e = right / blockSize;  // the last block index

    if (s == e) {
        for (int i = left; i <= right; i++)
            res = max(res, values[i]);
        return res;
    }
    for (int i = left; i < (s + 1) * blockSize; i++) 
        res = max(res, values[i]);
    for (int i = s + 1; i <= e - 1; i++)
        res = max(res, blocks[i]);
    for (int i = e * blockSize; i <= right; i++)
        res = max(res, values[i]);
    return res;
}

//point update / range update -> range query
template<int N>
struct SqrtDecompMaxType2 {
    struct Block {
        int base, max;
    };
    Block blocks[N];      // block { base, max }
    int blockSize;
    int blockCnt;
    int values[N];

    void init() {
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) { blocks[i] = { -INF }; }
    }
    void build(const int arr[]) {
        for (int i = 0; i < N; i++) { updatePoint(i, arr[i]); }
    }
    void updatePoint(int idx, int value);
    void updateRange(int left, int right, int value);
    int queryPoint(int idx);
    int queryRange(int left, int right);
};

template<int N>
void SqrtDecompMaxType2<N>::updatePoint(int idx, int value) {
    values[idx] += value;

    int bIdx = idx / blockSize;
    int left = bIdx * blockSize;                        // the first index
    int right = min((bIdx + 1) * blockSize - 1, N - 1); // the last index
    blocks[bIdx] = -INF;
    for (int i = left; i <= right; i++) {
        if (blocks[bIdx].max < value) { blocks[bIdx].max = value; }
    }
}

template<int N>
void SqrtDecompMaxType2<N>::updateRange(int left, int right, int value) {
    int s = left / blockSize;   // the first block index
    int e = right / blockSize;  // the last block index

    if (s == e) {
        for (int i = left; i <= right; i++)
            updatePoint(i, value);
        return;
    }
    for (int i = left; i < (s + 1) * blockSize; i++)
        updatePoint(i, value);
    for (int i = s + 1; i <= e - 1; i++) {
        blocks[i].base += value;
        blocks[i].max += value;
    }
    for (int i = e * blockSize; i <= right; i++)
        updatePoint(i, value);
}

template<int N>
int SqrtDecompMaxType2<N>::queryPoint(int idx) {
    return values[idx] + blocks[idx / blockSize].base;
}

template<int N>
int SqrtDecompMaxType2<N>::queryRange(int left, int right) {
    int res = -INF;
    int s = left / blockSize;   // the first block index
    int e = right / blockSize;  // the last block index

    if (s == e) {
        for (int i = left; i <= right; i++)
            res = max(res, queryPoint(i));
        return res;
    }
    for (int i = left; i < (s + 1) * blockSize; i++)
        res = max(res, queryPoint(i));
    for (int i = s + 1; i <= e - 1; i++)
        res = max(res, blocks[i].max);
    for (int i = e * blockSize; i <= right; i++)
        res = max(res, queryPoint(i));
    return res;
}

//point update / range update -> range query
template<int N>
struct SqrtDecompMaxType3 {
    struct Pair {
        int idx, value;
    };
    struct Block {
        int base;
        Pair max;
    };
    Block blocks[N];      // block { base, { idx, value } }
    int blockSize;
    int blockCnt;
    int values[N];

    void init() {
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) 
            blocks[i] = { 0, { 0, -INF} };
    }
    void build(const int arr[]) {
        for (int i = 0; i < N; i++) { updatePoint(i, arr[i]); }
    }
    void updatePoint(int idx, int value);
    void updateRange(int left, int right, int value);
    int queryPoint(int idx);
    int queryRange(int left, int right);
};

template<int N>
void SqrtDecompMaxType3<N>::updatePoint(int idx, int value) {
    values[idx] += value;

    int bIdx = idx / blockSize;
    if (idx != blocks[bIdx].max.idx) {
        if (blocks[bIdx].max.value < value)
            blocks[bIdx].max = { idx, value };
    }
    else {
        int left = bIdx * blockSize;
        int right = min((bIdx + 1) * blockSize - 1, N - 1);
        blocks[bIdx].max.value = -INF;
        for (int i = left; i <= right; i++) {
            if (blocks[bIdx].max.value < value) 
                blocks[bIdx].max = { i, value };
        }
    }
}

template<int N>
void SqrtDecompMaxType3<N>::updateRange(int left, int right, int value) {
    int s = left / blockSize;   // the first block index
    int e = right / blockSize;  // the last block index

    if (s == e) {
        for (int i = left; i <= right; i++) { updatePoint(i, value); }
        return;
    }
    for (int i = left; i < (s + 1) * blockSize; i++) { updatePoint(i, value); }
    for (int i = s + 1; i <= e - 1; i++) {
        blocks[i].base += value;
        blocks[i].max.value += value;
    }
    for (int i = e * blockSize; i <= right; i++) { updatePoint(i, value); }
}

template<int N>
int SqrtDecompMaxType3<N>::queryPoint(int idx) {
    return values[idx] + blocks[idx / blockSize].base;
}

template<int N>
int SqrtDecompMaxType3<N>::queryRange(int left, int right) {
    int res = -INF;
    int s = left / blockSize;   // the first block index
    int e = right / blockSize;  // the last block index

    if (s == e) {
        for (int i = left; i <= right; i++) { res = max(res, queryPoint(i)); }
        return res;
    }
    for (int i = left; i < (s + 1) * blockSize; i++)
        res = max(res, queryPoint(i));
    for (int i = s + 1; i <= e - 1; i++)
        res = max(res, blocks[i].max.value);
    for (int i = e * blockSize; i <= right; i++)
        res = max(res, queryPoint(i));
    return res;
}