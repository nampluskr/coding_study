#pragma once

#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

#include "func.h"   // sqrt(), ceil()

// Point Update => Range Query
struct SqrtDecomp {
    int values[MAX_SIZE];
    int blocks[MAX_SIZE];   // block range sum
    int bSize;              // block size
    int bCnt;               // number of blocks

    void init(int size) {
        bSize = sqrt(size);
        bCnt = ceil(size, bSize);
        for (int i = 0; i < bCnt; i++) { blocks[i] = 0; }
        for (int i = 0; i < size; i++) { values[i] = 0; }
    }
    void build(const int arr[], int size) {
        bSize = sqrt(size);
        bCnt = ceil(size, bSize);
        for (int i = 0; i < bCnt; i++) { blocks[i] = 0; }
        for (int i = 0; i < size; i++) { updatePoint(i, arr[i]); }
    }
    void updatePoint(int idx, int diff) {
        values[idx] += diff;
        blocks[idx / bSize] += diff;
    }
    int queryRange(int left, int right) {
        int res = 0;
        int s = left / bSize;
        int e = right / bSize;

        if (s == e) {
            for (int i = left; i <= right; i++) { res += values[i]; }
            return res;
        }
        for (int i = left; i < (s + 1) * bSize; i++) { res += values[i]; }
        for (int i = s + 1; i <= e - 1; i++) { res += blocks[i]; }
        for (int i = e * bSize; i <= right; i++) { res += values[i]; }
        return res;
    }
};

// Point/Range Update => Point/Range Query
struct SqrtDecompRange {
    struct Block {
        int base, sum;
    };
    int values[MAX_SIZE];
    Block blocks[MAX_SIZE]; // block { base, sum }
    int bSize;              // block size
    int bCnt;               // number of blocks

    void init(int size) {
        bSize = sqrt(size);
        bCnt = ceil(size, bSize);
        for (int i = 0; i < bCnt; i++) { blocks[i] = {}; }
        for (int i = 0; i < size; i++) { values[i] = 0; }
    }
    void build(const int arr[], int size) {
        bSize = sqrt(size);
        bCnt = ceil(size, bSize);
        for (int i = 0; i < bCnt; i++) { blocks[i] = {}; }
        for (int i = 0; i < size; i++) { updatePoint(i, arr[i]); }
    }
    void updatePoint(int idx, int diff) {
        values[idx] += diff;
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
    int queryPoint(int idx) {
        return values[idx] + blocks[idx / bSize].base;
    }
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