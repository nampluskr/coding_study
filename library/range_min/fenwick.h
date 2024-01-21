#pragma once

#include "func.h"

#ifndef INF
#define INF 0x7fffffff
#endif

template<int max_size>
struct FenwickTree {
    int tree1[max_size + 1];    // prefix BIT
    int tree2[max_size + 1];    // suffix BIT
    int arr[max_size + 1];
    int N;

    void init(int size) { N = size; clear(); }
    void clear() { 
        for (int i = 1; i <= max_size; i++) { tree1[i] = tree2[i] = INF; }
    }
    void build(const int arr[], int size) {
        clear();
        for (int i = 0; i < size; i++) { updatePoint(i, arr[i]); }
    }
    void updatePoint(int idx, int value) {
        arr[idx + 1] = value;
        updateTree1(idx, value);
        updateTree2(idx, value);
    }
    void updateTree1(int idx, int value) {
        idx++;
        while (idx <= N) {
            tree1[idx] = min(tree1[idx], value);
            idx += idx & -idx;
        }
    }
    void updateTree2(int idx, int value) {
        idx++;
        while (idx > 0) {
            tree2[idx] = min(tree2[idx], value);
            idx -= idx & -idx;
        }
    }
    int queryRange(int left, int right) {
        left++; right++;
        int res = INF;
        int prev = left;
        int cur = prev + (prev & -prev);

        while (cur <= right) {
            res = min(res, tree2[prev]);
            prev = cur;
            cur = prev + (prev & -prev);
        }
        res = min(res, arr[prev]);
        prev = right;
        cur = prev - (prev & -prev);

        while (cur >= left) {
            res = min(res, tree1[prev]);
            prev = cur;
            cur = prev - (prev & -prev);
        }
        return res;
    }
};