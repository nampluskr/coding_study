#pragma once

// func.cpp
extern int sqrt(int);
extern int ceil(int, int);

// point update / range query
template<int N>
struct SqrtDecompSumType1 {
    int blocks[N];      // block sum
    int blockSize;
    int blockCnt;
    int values[N];

    void init() {
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) { blocks[i] = 0; }
        for (int i = 0; i < N; i++) { values[i] = 0; }
    }
    void build(const int arr[]) {
        for (int i = 0; i < N; i++) { updatePoint(i, arr[i]); }
    }
    void updatePoint(int idx, int value);
    int queryRange(int left, int right);
};

template<int N>
void SqrtDecompSumType1<N>::updatePoint(int idx, int value) {
    values[idx] += value;
    // update block
    blocks[idx / blockSize] += value;
}

template<int N>
int SqrtDecompSumType1<N>::queryRange(int left, int right) {
    int res = 0;
    int s = left / blockSize;   // the first block index
    int e = right / blockSize;  // the last block index

    if (s == e) {
        for (int i = left; i <= right; i++) { res += values[i]; }
        return res;
    }
    for (int i = left; i < (s + 1) * blockSize; i++)
        res += values[i];
    for (int i = s + 1; i <= e - 1; i++)
        res += blocks[i];
    for (int i = e * blockSize; i <= right; i++)
        res += values[i];
    return res;
}


// point update / range update -> query range
template<int N>
struct SqrtDecompSumType2 {
    struct Block {
        int base, sum;
    };
    Block blocks[N];    // { base, sum }
    int blockSize;
    int blockCnt;
    int values[N];

    void init() {
        blockSize = sqrt(N);
        blockCnt = ceil(N, blockSize);
        for (int i = 0; i < blockCnt; i++) { blocks[i] = { 0, 0 }; }
        for (int i = 0; i < N; i++) { values[i] = 0; }
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
void SqrtDecompSumType2<N>::updatePoint(int idx, int value) {
    values[idx] += value;
    // update block
    blocks[idx / blockSize].sum += value;
}

template<int N>
void SqrtDecompSumType2<N>::updateRange(int left, int right, int value) {
    int s = left / blockSize;   // the first block index
    int e = right / blockSize;  // the last block index

    if (s == e) {
        for (int i = left; i <= right; i++) { updatePoint(i, value); }
        return;
    }
    for (int i = left; i < (s + 1) * blockSize; i++)
        updatePoint(i, value);
    for (int i = s + 1; i <= e - 1; i++) { 
        // update block
        blocks[i].base += value;
        blocks[i].sum += value * blockSize;
    }
    for (int i = e * blockSize; i <= right; i++)
        updatePoint(i, value);
}

template<int N>
int SqrtDecompSumType2<N>::queryPoint(int idx) {
    return values[idx] + blocks[idx / blockSize].base;
}

template<int N>
int SqrtDecompSumType2<N>::queryRange(int left, int right) {
    int res = 0;
    int s = left / blockSize;   // the first block index
    int e = right / blockSize;  // the last block index

    if (s == e) {
        for (int i = left; i <= right; i++) { res += queryPoint(i); }
        return res;
    }
    for (int i = left; i < (s + 1) * blockSize; i++)
        res += queryPoint(i);
    for (int i = s + 1; i <= e - 1; i++)
        res += blocks[i].sum;
    for (int i = e * blockSize; i <= right; i++)
        res += queryPoint(i);
    return res;
}