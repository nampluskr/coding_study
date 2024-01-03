### Segment Tree Range Update 테스트 - Type 2 이상 (JJH 코드 참고)

```cpp
#pragma once

template<int N>
struct SegTreeType1 {
    int tree[N * 4];

    void clear() {}
    int merge(int a, int b) { return a + b; }
    void updatePoint(int idx, int value) { updatePoint(1, 0, N - 1, idx, value); }
    void updateRange(int left, int right, int value) { updateRange(1, 0, N - 1, left, right, value); }
    int queryRange(int left, int right) { return queryRange(1, 0, N - 1, left, right); }

    // recursive
    int updatePoint(int n, int s, int e, int idx, int value) {
        if (idx < s || e < idx) { return tree[n]; }   // do nothing
        if (s == e) { return tree[n] += value; }
        int m = s + (e - s) / 2;
        int a = updatePoint(n * 2, s, m, idx, value);
        int b = updatePoint(n * 2 + 1, m + 1, e, idx, value);
        return tree[n] = merge(a, b);
    }
    int updateRange(int n, int s, int e, int left, int right, int value) {
        if (right < s || e < left) { return tree[n]; }   // do nothing
        if (s == e) { return tree[n] += value; }
        int m = s + (e - s) / 2;
        int a = updateRange(n * 2, s, m, left, right, value);
        int b = updateRange(n * 2 + 1, m + 1, e, left, right, value);
        return tree[n] = merge(a, b);
    }
    int queryRange(int n, int s, int e, int left, int right) {
        if (right < s || e < left) { return 0; }   // default value
        if (left <= s && e <= right) { return tree[n]; }
        int m = s + (e - s) / 2;
        int a = queryRange(n * 2, s, m, left, right);
        int b = queryRange(n * 2 + 1, m + 1, e, left, right);
        return tree[n] = merge(a, b);
    }
};

template<int N>
struct SegTreeType2 {
    int tree[N * 4];

    void clear() {}
    int merge(int a, int b) { return a + b; }
    void updateRange(int left, int right, int value) { updateRange(1, 0, N - 1, left, right, value); }
    int queryPoint(int idx) { return queryPoint(1, 0, N - 1, idx); }

    // recursive
    int updateRange(int n, int s, int e, int left, int right, int value) {
        if (right < s || e < left) { return tree[n]; }   // default value
        if (left <= s && e <= right) { return tree[n] += value; }
        int m = s + (e - s) / 2;
        int a = updateRange(n * 2, s, m, left, right, value);
        int b = updateRange(n * 2 + 1, m + 1, e, left, right, value);
        return tree[n] = merge(a, b);
    }
    int queryPoint(int n, int s, int e, int idx) {
        if (idx < s || e < idx) { return 0; }   // do nothing
        if (s == e) { return tree[n]; }
        int m = s + (e - s) / 2;
        int a = queryPoint(n * 2, s, m, idx);
        int b = queryPoint(n * 2 + 1, m + 1, e, idx);
        return tree[n] = merge(a, b);
    }
};
```
### 테스트 코드

```cpp
#include "seg_tree.h"

#define N   8

SegTreeType1<N> seg1;
SegTreeType2<N> seg2;

void test_seg1() {
    //seg1.updatePoint(1, 1);
    //seg1.updatePoint(2, 1);
    //seg1.updatePoint(3, 1);
    //seg1.updatePoint(4, 1);

    seg1.updateRange(1, 4, 1);
}
void test_seg2() {
    seg2.updateRange(1, 4, 1);
}

int main()
{
    test_seg1();

    //test_seg2();

    return 0;
}
```
