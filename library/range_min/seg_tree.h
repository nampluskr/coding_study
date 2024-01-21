#pragma once

#include "func.h"

#ifndef MAX_SIZE
#define MAX_SIZE 1000000
#endif

#ifndef INF
#define INF 0x7ffffff
#endif

template<int max_size>
struct SegmentTreeMin {
    int tree[max_size * 4];
    int N;                          // tree size
    const int DEFAULT_VALUE = INF;  // for range min

    int merge(int a, int b) { return min(a, b); }
    void init(int size) { N = size * 4; clear(); }
    void clear() { for (int i = 0; i < N; i++) tree[i] = DEFAULT_VALUE; }

    // inclusive
    void build(const int arr[]) { build(1, 0, N - 1, arr); }
    void updatePoint(int idx, int delta) { updatePoint(1, 0, N - 1, idx, delta); }
    int queryRange(int left, int right) { return queryRange(1, 0, N - 1, left, right); }

    // recursive
    int build(int n, int s, int e, const int arr[]) {
        if (s == e) { return tree[n] = arr[s]; }

        int m = s + (e - s) / 2;
        int a = build(n * 2, s, m, arr);
        int b = build(n * 2 + 1, m + 1, e, arr);
        return tree[n] = merge(a, b);
    }
    int updatePoint(int n, int s, int e, int idx, int delta) {
        if (idx < s || e < idx) { return tree[n]; }
        if (s == e) { return tree[n] += delta; }

        int m = s + (e - s) / 2;
        int a = updatePoint(n * 2, s, m, idx, delta);
        int b = updatePoint(n * 2 + 1, m + 1, e, idx, delta);
        return tree[n] = merge(a, b);
    }
    int queryRange(int n, int s, int e, int left, int right) {
        if (right < s || e < left) { return DEFAULT_VALUE; }
        if (left <= s && e <= right) { return tree[n]; }

        int m = s + (e - s) / 2;
        int a = queryRange(n * 2, s, m, left, right);
        int b = queryRange(n * 2 + 1, m + 1, e, left, right);
        return merge(a, b);
    }
};

// Lazy Propagation
template<int max_size>
struct SegmentTreeMinRange {
    int tree[max_size * 4];
    int lazyValues[max_size * 4];
    bool lazyExist[max_size * 4];
    int N;                          // tree size
    const int DEFAULT_VALUE = INF;  // for range sum

    int merge(int a, int b) { return min(a, b); }
    int mergeBlock(int diff, int size) { return diff; }
    int pushDown(int n, int s, int e, int diff) {
        if (s == e) { return tree[n] += diff; }
        lazyExist[n] = true;
        lazyValues[n] += diff;
        return tree[n] += mergeBlock(diff, e - s + 1);
    }
    void init(int size) { N = size * 4; clear(); }
    void clear() {
        for (int i = 0; i < N; i++) {
            tree[i] = DEFAULT_VALUE;
            lazyValues[i] = 0;
            lazyExist[i] = false;
        }
    }

    // inclusive
    void build(const int arr[]) { build(1, 0, N - 1, arr); }
    void updatePoint(int idx, int diff) { updatePoint(1, 0, N - 1, idx, diff); }
    void updateRange(int left, int right, int diff) { updateRange(1, 0, N - 1, left, right, diff); }
    int queryPoint(int idx) { return queryPoint(1, 0, N - 1, idx); }
    int queryRange(int left, int right) { return queryRange(1, 0, N - 1, left, right); }

    // recursive
    int build(int n, int s, int e, const int arr[]);
    int updatePoint(int n, int s, int e, int idx, int diff);
    int updateRange(int n, int s, int e, int left, int right, int diff);
    int queryRange(int n, int s, int e, int left, int right);
};

template<int max_size>
int SegmentTreeMinRange<max_size>::build(int n, int s, int e, const int arr[]) {
    if (s == e) { return tree[n] = arr[s]; }

    int m = s + (e - s) / 2;
    int a = build(n * 2, s, m, arr);
    int b = build(n * 2 + 1, m + 1, e, arr);
    return tree[n] = merge(a, b);
}

template<int max_size>
int SegmentTreeMinRange<max_size>::updatePoint(int n, int s, int e, int idx, int diff) {
    if (idx < s || e < idx) { return tree[n]; }
    if (s == e) { return tree[n] += diff; }

    int m = s + (e - s) / 2;
    int a = updatePoint(n * 2, s, m, idx, diff);
    int b = updatePoint(n * 2 + 1, m + 1, e, idx, diff);
    return tree[n] = merge(a, b);
}

template<int max_size>
int SegmentTreeMinRange<max_size>::updateRange(int n, int s, int e, int left, int right, int diff) {
    if (right < s || e < left) { return tree[n]; }
    if (s == e) { return tree[n] += diff; }

    if (left <= s && e <= right) {
        lazyExist[n] = true;
        lazyValues[n] += diff;
        return tree[n] += mergeBlock(diff, e - s + 1);
    }
    int m = s + (e - s) / 2;
    if (lazyExist[n]) {
        lazyExist[n] = false;
        pushDown(n * 2, s, m, lazyValues[n]);
        pushDown(n * 2 + 1, m + 1, e, lazyValues[n]);
        lazyValues[n] = DEFAULT_VALUE;
    }
    int a = updateRange(n * 2, s, m, left, right, diff);
    int b = updateRange(n * 2 + 1, m + 1, e, left, right, diff);
    return tree[n] = merge(a, b);
}

template<int max_size>
int SegmentTreeMinRange<max_size>::queryRange(int n, int s, int e, int left, int right) {
    if (right < s || e < left) { return DEFAULT_VALUE; }
    if (left <= s && e <= right) { return tree[n]; }

    int m = s + (e - s) / 2;
    if (lazyExist[n]) {
        lazyExist[n] = false;
        pushDown(n * 2, s, m, lazyValues[n]);
        pushDown(n * 2 + 1, m + 1, e, lazyValues[n]);
        lazyValues[n] = DEFAULT_VALUE;
    }
    int a = queryRange(n * 2, s, m, left, right);
    int b = queryRange(n * 2 + 1, m + 1, e, left, right);
    return merge(a, b);
}