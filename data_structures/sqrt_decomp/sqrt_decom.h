#pragma once

#include <cmath>

#define INF 0x7fffffff

inline int ceil(int a, int b) { return (a + b - 1) / b; }
inline int get_min(int a, int b) { return (a < b) ? a : b; }
inline int get_max(int a, int b) { return (a < b) ? b : a; }

struct Data {
    int base, sum, min, max;
    int left, right;

    // void update(int idx, int value) {
    //      sum += value;
    //      min = max = arr[left];
    //      for (int i = left + 1; i <= right; i++) {
    //          min = get_min(min, arr[i]);
    //          max = get_max(max, arr[i]);
    // }
    void update_min_max(const int arr[]) {
        min = max = arr[left];
        for (int i = left + 1; i <= right; i++) {
            min = get_min(min, arr[i]);
            max = get_max(max, arr[i]);
        }
    }
};

template<int N>
struct SqrtDecomp {
    Data buckets[N];     // sum of bucket range
    int* arr;
    int bucketSize, bucketCnt;

    void init(int arr[]);
    void update(int idx, int value);
    void update(int left, int right, int value);
    int query(int idx);
    Data query(int left, int right);

    Data merge(const Data& a, const Data& b) {
        Data res = a;
        res.sum += b.sum;
        if (b.min < res.min) { res.min = b.min; }
        if (res.max < b.max) { res.max = b.max; }
        //res.left = get_min(res.left, b.left);
        //res.right = get_max(res.right, b.right);
        return res;
    }
};

template<int N>
void SqrtDecomp<N>::init(int arr[]) {
    this->arr = arr;
    bucketSize = sqrt(N);
    bucketCnt = ceil(N, bucketSize);

    for (int i = 0; i < bucketCnt; i++) {
        buckets[i] = { 0, 0, INF, -INF };
        buckets[i].left = i * bucketSize;
        buckets[i].right = get_min((i + 1) * bucketSize - 1, N - 1);
    }
    for (int i = 0; i < N; i++) {
        buckets[i / bucketSize].sum += this->arr[i];
        buckets[i / bucketSize].update_min_max(arr);
    }
}

template<int N>
void SqrtDecomp<N>::update(int idx, int value) {
    arr[idx] += value;
    buckets[idx / bucketSize].sum += value;         // update sum
    buckets[idx / bucketSize].update_min_max(arr);  // update min, max
}

template<int N>
void SqrtDecomp<N>::update(int left, int right, int value) {
    int s = left / bucketSize;      // start bucket index
    int e = right / bucketSize;     // end bucket index

    if (s == e) {
        for (int i = left; i <= right; i++) { update(i, value); }
        return;
    }
    while (left / bucketSize == s) { update(left++, value); }
    for (int i = s + 1; i <= e - 1; i++) { 
        buckets[i].base += value;
        buckets[i].sum += value * bucketSize;
        buckets[i].min += value;
        buckets[i].max += value;
    }
    while (right / bucketSize== e) { update(right--, value); }
}

template<int N>
int SqrtDecomp<N>::query(int idx) { 
    return arr[idx] + buckets[idx / bucketCnt].base;
}

template<int N>
Data SqrtDecomp<N>::query(int left, int right) {
    Data res = { 0, 0, INF, -INF };    // default value
    int s = left / bucketSize;
    int e = right / bucketSize;

    if (s == e) {
        for (int i = left; i <= right; i++) { 
            res.sum += arr[i];
            res.update_min_max(arr);    // error: res.left == 0, res.right == 0
        }
        return res;
    }
    while (left / bucketSize == s) { 
        res.sum += arr[left++];
        res.update_min_max(arr);        // error: res.left == 0, res.right == 0
    }
    for (int i = s + 1; i <= e - 1; i++) { 
        res = merge(res, buckets[i]);
    }
    while (right / bucketSize == e) { 
        res.sum += arr[right--];
        res.update_min_max(arr);        // error: res.left == 0, res.right == 0
    }
    return res;
}