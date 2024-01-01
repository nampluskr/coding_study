#pragma once

#include <vector>
using namespace std;

// Point Update -> Range Query (sum, min, max)
struct SegmentTree {
    vector<int> tree;
    int N;

    int merge(int left, int right) { return left + right; }     // range sum

    // recursive
    int buildRecur(const int arr[], int node, int start, int end) {
        if (start == end)
            return tree[node] = arr[start];
        int mid = start + (end - start) / 2;
        int leftVal = buildRecur(arr, node * 2, start, mid);
        int rightVal = buildRecur(arr, node * 2 + 1, mid + 1, end);
        return tree[node] = merge(leftVal, rightVal);
    }
    int queryRecur(int left, int right, int node, int start, int end) {
        if (right < start || end < left)
            return 0;   // default value
        if (left <= start && end <= right)
            return tree[node];

        int mid = start + (end - start) / 2;
        int leftVal = queryRecur(left, right, node * 2, start, mid);
        int rightVal = queryRecur(left, right, node * 2 + 1, mid + 1, end);
        return merge(leftVal, rightVal);
    }
    int updateRecur(int idx, int new_value, int node, int start, int end) {
        if (idx < start || end < idx)
            return tree[node];
        if (start == end)
            return tree[node] = new_value;

        int mid = start + (end - start) / 2;
        int leftVal = updateRecur(idx, new_value, node * 2, start, mid);
        int rightVal = updateRecur(idx, new_value, node * 2 + 1, mid + 1, end);
        return tree[node] = merge(leftVal, rightVal);
    }

    // inclusive
    void build(const int arr[], int size) {
        N = size;
        tree.resize(N * 4);
        buildRecur(arr, 1, 0, N - 1);
    }
    int query(int left, int right) {
        return queryRecur(left, right, 1, 0, N - 1);
    }
    int update(int idx, int new_value) {
        return updateRecur(idx, new_value, 1, 0, N - 1);
    }

};