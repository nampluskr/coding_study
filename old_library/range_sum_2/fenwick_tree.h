#pragma once

#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

struct FenwickTree {
    int tree[MAX_SIZE + 1];
    int treeSize;

    void init(int size) {
        treeSize = size;    
        for (int i = 0; i <= treeSize; i++) { tree[i] = 0; }
    }
    void build(const int arr[], int size) {
        treeSize = size;    // N = size + 1; ???
        for (int i = 0; i < size; i++) { updatePoint(i, arr[i]); }
    }
    void updatePoint(int idx, int diff) {
        idx++;
        while (idx <= treeSize) {
            tree[idx] += diff;
            idx += idx & -idx;      // 최하위 bit 추가
        }  
    }
    int prefixSum(int idx) {
        idx++;
        int res = 0;
        while (idx > 0) {
            res += tree[idx];       // 최하위 bit 제거
            idx &= idx - 1;
        }
        return res;
    }
    int queryRange(int left, int right) {
        int res = prefixSum(right);
        if (left > 0) { res -= prefixSum(left - 1); }
        return res;
    }
};

struct FenwickTreeRange {
    FenwickTree mulFwkTree;
    FenwickTree addFwkTree;

    void init(int size) {
        mulFwkTree.init(size);
        addFwkTree.init(size);
    }
    void build(const int arr[], int size) {
        mulFwkTree.treeSize = size;
        addFwkTree.treeSize = size;
        addFwkTree.build(arr, size);
    }
    void updatePoint(int idx, int diff) {
        mulFwkTree.updatePoint(idx, diff);
        addFwkTree.updatePoint(idx, diff * (1 - idx));
    }
    void updateRange(int left, int right, int diff) {
        updatePoint(left, diff);
        updatePoint(right + 1, -diff);
    }
    int prefixSum(int idx) {
        return addFwkTree.prefixSum(idx) + mulFwkTree.prefixSum(idx) * idx;
    }
    int queryRange(int left, int right) {
        return prefixSum(right) - prefixSum(left - 1);
    }
};