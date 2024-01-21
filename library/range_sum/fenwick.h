#pragma once

template<int max_size>
struct FenwickTree {
    int tree[max_size + 1];
    int N;

    void init(int size) { N = size; clear(); }
    void clear() { for (int i = 1; i <= max_size; i++) tree[i] = 0; }
    void build(const int arr[], int size) {
        clear();
        for (int i = 0; i < size; i++)
            updatePoint(i, arr[i]);
    }
    void updatePoint(int idx, int delta) {
        idx++;
        while (idx <= N) {
            tree[idx] += delta;
            idx += idx & -idx;
        }
    }
    int prefixSum(int idx) {
        idx++;
        int res = 0;
        while (idx > 0) {
            res += tree[idx];
            idx -= idx & -idx;
        }
        return res;
    }
    int queryRange(int left, int right) {
        return prefixSum(right) - prefixSum(left - 1);
    }
};

template<int max_size>
struct FenwickTreeRange {
    FenwickTree<max_size> tree1;    // slope
    FenwickTree<max_size> tree2;    // y-intersection

    void init(int size) { tree1.init(size); tree2.init(size); }
    void clear() { tree1.clear(); tree2.clear(); }
    void build(const int arr[], int size) {
        clear();
        for (int i = 0; i < size; i++)
            updatePoint(i, arr[i]);
    }
    void updatePoint(int idx, int delta) { updateRange(idx, idx, delta); }
    void updateRange(int left, int right, int delta) {
        tree1.updatePoint(left, delta);
        tree1.updatePoint(right + 1, -delta);
        tree2.updatePoint(left, delta * (left - 1));
        tree2.updatePoint(right + 1, -delta * right);
    }
    int prefixSum(int idx) {
        return tree1.prefixSum(idx) * idx - tree2.prefixSum(idx);
    }
    int queryRange(int left, int right) {
        return prefixSum(right) - prefixSum(left - 1);
    }
};