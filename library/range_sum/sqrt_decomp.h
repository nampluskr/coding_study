#pragma once

#include "func.h"

template<int max_size>
struct SqrtDecomp {
    int arr[max_size];
    int N;
    int blocks[max_size];   // block range sum
    int bSize, bCnt;        // block size, number of blocks

    void init(int size) {
        N = size;
        bSize = sqrt(size);
        bCnt = ceil(size, bSize);
        clear();
    }
    void clear() {
        for (int i = 0; i < N; i++) { arr[i] = 0; }
        for (int i = 0; i < bCnt; i++) { blocks[i] = 0; }
    }
    void build(const int arr[], int size) {
        clear();
        for (int i = 0; i < size; i++) { updatePoint(i, arr[i]); }
    }
    void updatePoint(int idx, int diff) {
        arr[idx] += diff;
        blocks[idx / bSize] += diff;
    }
    int queryRange(int left, int right) {
        int res = 0;
        int s = left / bSize;
        int e = right / bSize;

        if (s == e) {
            for (int i = left; i <= right; i++) { res += arr[i]; }
            return res;
        }
        for (int i = left; i < (s + 1) * bSize; i++) { res += arr[i]; }
        for (int i = s + 1; i <= e - 1; i++) { res += blocks[i]; }
        for (int i = e * bSize; i <= right; i++) { res += arr[i]; }
        return res;
    }
};

struct Block {
    int base, sum;
};

template<int max_size>
struct SqrtDecompRange {
    int arr[max_size];
    int N;
    Block blocks[max_size]; // block base and sum
    int bSize, bCnt;        // block size, number of blocks

    void init(int size) {
        N = size;
        bSize = sqrt(size);
        bCnt = ceil(size, bSize);
        clear();
    }
    void clear() {
        for (int i = 0; i < bCnt; i++) { blocks[i] = { 0, 0 }; }
        for (int i = 0; i < N; i++) { arr[i] = 0; }
    }
    void build(const int arr[], int size) {
        clear();
        for (int i = 0; i < size; i++) { updatePoint(i, arr[i]); }
    }
    void updatePoint(int idx, int diff) {
        arr[idx] += diff;
        blocks[idx / bSize].sum += diff;
    }
    void updateRange(int left, int right, int diff) {
        int s = left / bSize;
        int e = right / bSize;

        if (s == e) {
            for (int i = left; i <= right; i++) { updatePoint(i, diff); }
            return;
        }
        for (int i = left; i < (s + 1) * bSize; i++) { updatePoint(i, diff); }
        for (int i = s + 1; i <= e - 1; i++) { 
            blocks[i].base += diff;
            blocks[i].sum += diff * bSize;
        }
        for (int i = e * bSize; i <= right; i++) { updatePoint(i, diff); }
    }
    int queryPoint(int idx) { return arr[idx] + blocks[idx / bSize].base; }
    int queryRange(int left, int right) {
        int res = 0;
        int s = left / bSize;
        int e = right / bSize;

        if (s == e) {
            for (int i = left; i <= right; i++) { res += queryPoint(i); }
            return res;
        }
        for (int i = left; i < (s + 1) * bSize; i++) { res += queryPoint(i); }
        for (int i = s + 1; i <= e - 1; i++) { res += blocks[i].sum; }
        for (int i = e * bSize; i <= right; i++) { res += queryPoint(i); }
        return res;
    }
};