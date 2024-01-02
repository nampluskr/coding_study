#pragma once

#define INF 0x7fffffff

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a < b) ? b : a; }

template<int N>
struct SegmentTree {
    int tree[N * 4];

    int merge(int a, int b) { return a + b; }       // range sum (default: 0)
    //int merge(int a, int b) { return min(a, b); }   // range min (default: INF)
    //int merge(int a, int b) { return max(a, b); }   // range max (default: -INF)

    // inclusive
    void build(const int arr[]) { build_recur(1, 0, N - 1, arr); }
    int query(int left, int right) { return query_recur(1, 0, N - 1, left, right); }
    int update(int idx, int value) { return update_recur(1, 0, N - 1, idx, value); }
    int update(int left, int right, int value) {
        return update_recur(1, 0, N - 1, left, right, value);
    }

    // recursive
    int build_recur(int n, int s, int e, const int arr[]);
    int query_recur(int n, int s, int e, int left, int right);
    int update_recur(int n, int s, int e, int idx, int value);
    int update_recur(int n, int s, int e, int left, int right, int value);
};

// recursive
template<int N>
int SegmentTree<N>::build_recur(int n, int s, int e, const int arr[]) {
    if (s == e) { return tree[n] = arr[s]; }    // leaf node

    int m = s + (e - s) / 2;
    int a = build_recur(n * 2, s, m, arr);
    int b = build_recur(n * 2 + 1, m + 1, e, arr);
    return tree[n] = merge(a, b);
}

template<int N>
int SegmentTree<N>::query_recur(int n, int s, int e, int left, int right) {
    if (right < s || e < left) { return 0; }            // default value
    if (left <= s && e <= right) { return tree[n]; }    // leaf node

    int m = s + (e - s) / 2;
    int a = query_recur(n * 2, s, m, left, right);
    int b = query_recur(n * 2 + 1, m + 1, e, left, right);
    return merge(a, b);
}

template<int N>
int SegmentTree<N>::update_recur(int n, int s, int e, int idx, int value) {
    if (idx < s || e < idx) { return tree[n]; }     // default value
    if (s == e) { return tree[n] += value; }        // leaf node

    int m = s + (e - s) / 2;
    int a = update_recur(n * 2, s, m, idx, value);
    int b = update_recur(n * 2 + 1, m + 1, e, idx, value);
    return tree[n] = merge(a, b);
}

template<int N>
int SegmentTree<N>::update_recur(int n, int s, int e, int left, int right, int value) {
    if (right < s || e < left) { return tree[n]; }              // default value
    if (s == e) { return tree[n] += value; }   // leaf node

    int m = s + (e - s) / 2;
    int a = update_recur(n * 2, s, m, left, right, value);
    int b = update_recur(n * 2 + 1, m + 1, e, left, right, value);
    return tree[n] = merge(a, b);
}