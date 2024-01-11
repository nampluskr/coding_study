#pragma once

#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

#include "func.h"

struct SegmentTree {
    int values[MAX_SIZE];
    int blocks[MAX_SIZE];   // block sum
    int bSize;              // block size
    int bCnt;               // number of blocks

    void clear(int size) {
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
        int s = left / bSize;   // first block index
        int e = right / bSize;  // last block index

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

struct SegmentTreeRange {
    int values[MAX_SIZE];
    int blocks[MAX_SIZE];
    int bSize;              // block size
    int bCnt;               // number of blocks

    void clear(int size) {
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
    int queryPoint() {}
    int queryRange(int left, int right) {
        int res = 0;
        int s = left / bSize;   // first block index
        int e = right / bSize;  // last block index

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