#pragma once

#define INF 0x7fffffff

extern int min(int, int);
extern int max(int, int);

const int DEFAULT_VALUE = 0;
int merge(int a, int b) { return a + b; }

template<int N>
struct SegTree {
    int tree[N * 4];

    void init() { 
        for (int i = 0; i < N * 4; i++) { tree[i] = DEFAULT_VALUE; }
    }

    // inclusive
    void build(const int arr[]) {
        build(1, 0, N - 1, arr);
    }
    void updatePoint(int idx, int diff) {
        updatePoint(1, 0, N - 1, idx, diff);
    }
    void updateRange(int left, int right, int diff) {
        updateRange(1, 0, N - 1, left, right, diff);
    }
    int queryPoint(int idx) {
        return queryPoint(1, 0, N - 1, idx);
    }
    int queryRange(int left, int right) {
        return queryRange(1, 0, N - 1, left, right);
    }

    // recursive
    int build(int n, int s, int e, const int arr[]);
    int updatePoint(int n, int s, int e, int idx, int diff);
    int updateRange(int n, int s, int e, int left, int right, int diff);
    int queryPoint(int n, int s, int e, int idx);
    int queryRange(int n, int s, int e, int left, int right);
};

template<int N>
int SegTree<N>::build(int n, int s, int e, const int arr[]) {
    if (s == e) { return tree[n] = arr[s]; }

    int m = s + (e - s) / 2;
    int a = build(n * 2, s, m, arr);
    int b = build(n * 2 + 1, m + 1, e, arr);
    return tree[n] = merge(a, b);
}

template<int N>
int SegTree<N>::updatePoint(int n, int s, int e, int idx, int diff) {
    if (idx < s || e < idx) { return tree[n]; }
    if (s == e) { return tree[n] += diff; }

    int m = s + (e - s) / 2;
    int a = updatePoint(n * 2, s, m, idx, diff);
    int b = updatePoint(n * 2 + 1, m + 1, e, idx, diff);
    return tree[n] = merge(a, b);
}

template<int N>
int SegTree<N>::updateRange(int n, int s, int e, int left, int right, int diff) {
    if (right < s || e < left) { return tree[n]; }
    if (s == e) { return tree[n] += diff; }

    int m = s + (e - s) / 2;
    int a = updateRange(n * 2, s, m, left, right, diff);
    int b = updateRange(n * 2 + 1, m + 1, e, left, right, diff);
    return tree[n] = merge(a, b);
}

template<int N>
int SegTree<N>::queryPoint(int n, int s, int e, int idx) {
}

template<int N>
int SegTree<N>::queryRange(int n, int s, int e, int left, int right) {
    if (right < s || e < left) { return DEFAULT_VALUE; }
    if (left <= s && e <= right) { return tree[n]; }

    int m = s + (e - s) / 2;
    int a = queryRange(n * 2, s, m, left, right);
    int b = queryRange(n * 2 + 1, m + 1, e, left, right);
    return merge(a, b);
}


// Lazy Propagation
template<int N>
struct SegTreeLazy {
    int tree[N * 4];
    int lazyValues[N * 4];
    bool lazyExist[N * 4];

    int mergeBlock(int diff, int size) {
        return diff * size;    // sum
        //return diff;           // min
        //return diff;           // max
    }
    int pushDown(int n, int s, int e, int diff) {
        if (s == e) { return tree[n] += diff; }
        lazyExist[n] = true;
        lazyValues[n] += diff;
        return tree[n] += mergeBlock(diff, e - s + 1);
    }

    void init() { 
        for (int i = 0; i < N * 4; i++) {
            tree[i] = DEFAULT_VALUE;
            lazyValues[i] = 0;
            lazyExist[i] = false;
        }
    }

    // inclusive
    void build(const int arr[]) {
        build(1, 0, N - 1, arr);
    }
    void updatePoint(int idx, int diff) {
        updatePoint(1, 0, N - 1, idx, diff);
    }
    void updateRange(int left, int right, int diff) {
        updateRange(1, 0, N - 1, left, right, diff);
    }
    int queryPoint(int idx) {
        return queryPoint(1, 0, N - 1, idx);
    }
    int queryRange(int left, int right) {
        return queryRange(1, 0, N - 1, left, right);
    }

    // recursive
    int build(int n, int s, int e, const int arr[]);
    int updatePoint(int n, int s, int e, int idx, int diff);
    int updateRange(int n, int s, int e, int left, int right, int diff);
    int queryPoint(int n, int s, int e, int idx);
    int queryRange(int n, int s, int e, int left, int right);
};

template<int N>
int SegTreeLazy<N>::build(int n, int s, int e, const int arr[]) {
    if (s == e) { return tree[n] = arr[s]; }

    int m = s + (e - s) / 2;
    int a = build(n * 2, s, m, arr);
    int b = build(n * 2 + 1, m + 1, e, arr);
    return tree[n] = merge(a, b);
}

template<int N>
int SegTreeLazy<N>::updatePoint(int n, int s, int e, int idx, int diff) {
    if (idx < s || e < idx) { return tree[n]; }
    if (s == e) { return tree[n] += diff; }

    int m = s + (e - s) / 2;
    int a = updatePoint(n * 2, s, m, idx, diff);
    int b = updatePoint(n * 2 + 1, m + 1, e, idx, diff);
    return tree[n] = merge(a, b);
}

template<int N>
int SegTreeLazy<N>::updateRange(int n, int s, int e, int left, int right, int diff) {
    if (right < s || e < left) { return tree[n]; }
    if (s == e) { return tree[n] += diff; }

    if (left <= s && e <= right) { // 노드 영역이 query 영역에 완전히 포함
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

template<int N>
int SegTreeLazy<N>::queryPoint(int n, int s, int e, int idx) {
}

template<int N>
int SegTreeLazy<N>::queryRange(int n, int s, int e, int left, int right) {
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

#include <vector>
using namespace std;

// ================================================================
struct SegmentTreeLazy {
    static const int DEFAULT_VALUE = 0;
    //static const int DEFAULT_VALUE = numeric_limits<int>::max(); // for min
    //static const int DEFAULT_VALUE = numeric_limits<int>::min(); // for max

    int merge(int left, int right) {
        return left + right; // sum
        //return min(left, right); // min
        //return max(left, right); // max
    }

    int mergeBlock(int diff, int size) {
        return diff * size;    // sum
        //return diff;         // min
        //return diff;         // max
    }


    int N;                  // size
    vector<int> tree;       // segment tree
    vector<int> lazyValue;  // lazy diff
    vector<bool> lazyExist; // 

    void build(const int arr[], int size) {
        N = size;
        tree.resize(N * 4);
        lazyValue.assign(N * 4, DEFAULT_VALUE);
        lazyExist.assign(N * 4, false);

        buildRec(arr, 1, 0, N - 1);
    }

    // inclusive
    int update(int left, int right, int newValue) {
        return updateRec(left, right, newValue, 1, 0, N - 1);
    }

    // inclusive
    int query(int left, int right) {
        return queryRec(left, right, 1, 0, N - 1);
    }

private:
    int pushDown(int newValue, int n, int nodeLeft, int nodeRight) {
        if (nodeLeft == nodeRight)
            return tree[n] = newValue;

        lazyExist[n] = true;
        lazyValue[n] = newValue;
        return tree[n] = mergeBlock(newValue, nodeRight - nodeLeft + 1);
    }

    int buildRec(const int arr[], int n, int nodeLeft, int nodeRight) {
        if (nodeLeft == nodeRight)
            return tree[n] = arr[nodeLeft];

        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        int leftVal = buildRec(arr, n * 2, nodeLeft, mid);
        int rightVal = buildRec(arr, n * 2 + 1, mid + 1, nodeRight);
        return tree[n] = merge(leftVal, rightVal);
    }

    int updateRec(int left, int right, int newValue, int n, int nodeLeft, int nodeRight) {
        if (right < nodeLeft || nodeRight < left)
            return tree[n];

        if (nodeLeft == nodeRight)
            return tree[n] = newValue;

        if (left <= nodeLeft && nodeRight <= right) {
            lazyExist[n] = true;
            lazyValue[n] = newValue;
            return tree[n] = mergeBlock(newValue, nodeRight - nodeLeft + 1);
        }

        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        if (lazyExist[n]) {
            lazyExist[n] = false;
            pushDown(lazyValue[n], n * 2, nodeLeft, mid);
            pushDown(lazyValue[n], n * 2 + 1, mid + 1, nodeRight);
            lazyValue[n] = DEFAULT_VALUE;
        }

        int leftVal = updateRec(left, right, newValue, n * 2, nodeLeft, mid);
        int rightVal = updateRec(left, right, newValue, n * 2 + 1, mid + 1, nodeRight);
        return tree[n] = merge(leftVal, rightVal);
    }

    int queryRec(int left, int right, int n, int nodeLeft, int nodeRight) {
        if (right < nodeLeft || nodeRight < left)
            return DEFAULT_VALUE;           // default diff

        if (left <= nodeLeft && nodeRight <= right)
            return tree[n];

        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        if (lazyExist[n]) {
            lazyExist[n] = false;
            pushDown(lazyValue[n], n * 2, nodeLeft, mid);
            pushDown(lazyValue[n], n * 2 + 1, mid + 1, nodeRight);
            lazyValue[n] = DEFAULT_VALUE;
        }

        return merge(queryRec(left, right, n * 2, nodeLeft, mid),
            queryRec(left, right, n * 2 + 1, mid + 1, nodeRight));
    }
};

// =========================================================

template<int N>
struct SegTreeLazyBOJ {
    int tree[N * 4];
    int lazy[N * 4];

    const int DEFAULT_VALUE = 0;
    int merge(int a, int b) { return a + b; }

    // inclusive
    void build(const int arr[]) { build(1, 0, N - 1, arr); }
    void updatePoint(int idx, int diff) { updatePoint(1, 0, N - 1, idx, diff); }
    void updateRange(int left, int right, int diff) { updateRange(1, 0, N - 1, left, right, diff); }
    int queryRange(int left, int right) { return queryRange(1, 0, N - 1, left, right); }

    // recursive
    int build(int n, int s, int e, const int arr[]) {
        if (s == e) { return tree[n] = arr[s]; }
        int m = s + (e - s) / 2;
        int a = build(n * 2, s, m, arr);
        int b = build(n * 2 + 1, m + 1, e, arr);
        return tree[n] = merge(a, b);
    }
    int updatePoint(int n, int s, int e, int idx, int diff) {
        if (idx < s || e < idx) { return tree[n]; }
        if (s == e) { return tree[n] += diff; }

        int m = s + (e - s) / 2;
        int a = updatePoint(n * 2, s, m, idx, diff);
        int b = updatePoint(n * 2 + 1, m + 1, e, idx, diff);
        return tree[n] = merge(a, b);
    }
    void updateLazy(int n, int s, int e) {
        if (lazy[n] == 0) { return; }

        tree[n] += (e - s + 1) * lazy[n];
        if (s != e) {
            lazy[n * 2] += lazy[n];
            lazy[n * 2 + 1] += lazy[n];
        }
        lazy[n] = 0;
    }
    int updateRange(int n, int s, int e, int left, int right, int diff) {
        updateLazy(n, s, e);

        if (right < s || e < left) { return tree[n]; }
        if (left <= s && e <= right) {
            if (s != e) {
                lazy[n * 2] += diff;
                lazy[n * 2 + 1] += diff;
            }
            return tree[n] += (e - s + 1) * diff;
        }

        int m = s + (e - s) / 2;
        int a = updateRange(n * 2, s, m, left, right, diff);
        int b = updateRange(n * 2 + 1, m + 1, e, left, right, diff);
        return tree[n] = merge(a, b);
    }
    int queryRange(int n, int s, int e, int left, int right) {
        updateLazy(n, s, e);

        if (right < s || e < left) { return DEFAULT_VALUE; }
        if (left <= s && e <= right) { return tree[n]; }

        int m = s + (e - s) / 2;
        int a = queryRange(n * 2, s, m, left, right);
        int b = queryRange(n * 2 + 1, m + 1, e, left, right);
        return merge(a, b);
    }
};