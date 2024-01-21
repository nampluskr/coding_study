#pragma once

#include "func.h"

#ifndef MAX_SIZE
#define MAX_SIZE 1000000
#endif

#ifndef INF
#define INF 0x7ffffff
#endif

template<int max_size>
struct SqrtDecompMin {
    int arr[max_size];
    int N;                  // number of array elements
    int blocks[max_size];   // blcok min
    int bSize, bCnt;        // block size, number of blocks

    void init(int size) {
        N = size;
        bSize = sqrt(size);
        bCnt = ceil(size, bSize);
        clear();
    }
    void clear() {
        for (int i = 0; i < N; i++) { arr[i] = 0; }
        for (int i = 0; i < bCnt; i++) { blocks[i] = INF; }
    }
    void build(const int arr[], int size) {
        clear();
        for (int i = 0; i < size; i++) { updatePoint(i, arr[i]); }
    }
    void updatePoint(int idx, int delta) {
        arr[idx] += delta;

        int bIdx = idx / bSize;
        int left = bIdx * bSize;
        int right = min((bIdx + 1) * bSize - 1, N - 1);
        blocks[bIdx] = INF;
        for (int i = left; i <= right; i++)
            blocks[bIdx] = min(blocks[bIdx], arr[i]);
    }
    int queryRange(int left, int right) {
        int res = INF;
        int s = left / bSize;
        int e = right / bSize;

        if (s == e) {
            for (int i = left; i <= right; i++)
                res = min(res, arr[i]);
            return res;
        }
        for (int i = left; i < (s + 1) * bSize; i++) { res = min(res, arr[i]); }
        for (int i = s + 1; i <= e - 1; i++) { res = min(res, blocks[i]); }
        for (int i = e * bSize; i <= right; i++) { res = min(res, arr[i]); }
        return res;
    }
};


template<int max_size>
struct SqrtDecompMinRange {
    struct Block {
        int base, min;
    };
    int arr[max_size];
    int N;                  // number of array elements
    Block blocks[max_size]; // block base, min
    int bSize, bCnt;        // block size, number of blocks

    void init(int size) {
        N = size;
        bSize = sqrt(size);
        bCnt = ceil(size, bSize);
        clear();
    }
    void clear() {
        for (int i = 0; i < N; i++) { arr[i] = 0; }
        for (int i = 0; i < bCnt; i++) { blocks[i] = { 0, INF }; }
    }
    void build(const int arr[], int size) {
        clear();
        for (int i = 0; i < size; i++) { updatePoint(i, arr[i]); }
    }
    void updatePoint(int idx, int delta) {
        arr[idx] += delta;

        int bIdx = idx / bSize;
        int left = bIdx * bSize;
        int right = min((bIdx + 1) * bSize - 1, N - 1);
        blocks[bIdx].min = INF;
        for (int i = left; i <= right; i++)
            blocks[bIdx].min = min(blocks[bIdx].min, queryPoint(i));
    }
    void updateRange(int left, int right, int delta) {
        int s = left / bSize;
        int e = right / bSize;

        if (s == e) {
            for (int i = left; i <= right; i++) { updatePoint(i, delta); }
            return;
        }
        for (int i = left; i < (s + 1) * bSize; i++) { updatePoint(i, delta); }
        for (int i = s + 1; i <= e - 1; i++) {
            blocks[i].base += delta;
            blocks[i].min += delta;
        }
        for (int i = e * bSize; i <= right; i++) { updatePoint(i, delta); }
    }
    int queryPoint(int idx) {
        return arr[idx] + blocks[idx / bSize].base;
    }
    int queryRange(int left, int right) {
        int res = INF;
        int s = left / bSize;
        int e = right / bSize;

        if (s == e) {
            for (int i = left; i <= right; i++) { res = min(res, queryPoint(i)); }
            return res;
        }
        for (int i = left; i < (s + 1) * bSize; i++) { res = min(res, queryPoint(i)); }
        for (int i = s + 1; i <= e - 1; i++) { res = min(res, blocks[i].min); }
        for (int i = e * bSize; i <= right; i++) { res = min(res, queryPoint(i)); }
        return res;
    }
};

template<int max_size>
struct SqrtDecompMinRange2 {
    struct Pair {
        int idx, value;
    };
    struct Block {
        int base;
        Pair min;
    };
    int arr[max_size];
    int N;                  // number of array elements
    Block blocks[max_size]; // block base, min
    int bSize, bCnt;        // block size, number of blocks

    void init(int size) {
        N = size;
        bSize = sqrt(size);
        bCnt = ceil(size, bSize);
        clear();
    }
    void clear() {
        for (int i = 0; i < N; i++) { arr[i] = 0; }
        for (int i = 0; i < bCnt; i++) { blocks[i] = { 0, { -1, INF } }; }
    }
    void build(const int arr[], int size) {
        clear();
        for (int i = 0; i < size; i++) { updatePoint(i, arr[i]); }
    }
    void updatePoint(int idx, int delta) {
        arr[idx] += delta;

        int bIdx = idx / bSize;
        if (idx == blocks[bIdx].min.idx) {
            int left = bIdx * bSize;
            int right = min((bIdx + 1) * bSize - 1, N - 1);
            blocks[bIdx].min.value = INF;
            for (int i = left; i <= right; i++)
                if (queryPoint(i) < blocks[bIdx].min.value)
                    blocks[bIdx].min = { idx, queryPoint(i) };
        }
        else {
            if (queryPoint(idx) < blocks[bIdx].min.value)
                blocks[bIdx].min = { idx, queryPoint(idx) };
        }
    }
    void updateRange(int left, int right, int delta) {
        int s = left / bSize;
        int e = right / bSize;

        if (s == e) {
            for (int i = left; i <= right; i++) { updatePoint(i, delta); }
            return;
        }
        for (int i = left; i < (s + 1) * bSize; i++) { updatePoint(i, delta); }
        for (int i = s + 1; i <= e - 1; i++) {
            blocks[i].base += delta;
            blocks[i].min.value += delta;
        }
        for (int i = e * bSize; i <= right; i++) { updatePoint(i, delta); }
    }
    int queryPoint(int idx) {
        return arr[idx] + blocks[idx / bSize].base;
    }
    int queryRange(int left, int right) {
        int res = INF;
        int s = left / bSize;
        int e = right / bSize;

        if (s == e) {
            for (int i = left; i <= right; i++) { res = min(res, queryPoint(i)); }
            return res;
        }
        for (int i = left; i < (s + 1) * bSize; i++) { res = min(res, queryPoint(i)); }
        for (int i = s + 1; i <= e - 1; i++) { res = min(res, blocks[i].min.value); }
        for (int i = e * bSize; i <= right; i++) { res = min(res, queryPoint(i)); }
        return res;
    }
};