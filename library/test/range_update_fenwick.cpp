#if 1
#include <vector>
#include <cstdio>
using namespace std;

#define MAX_SIZE 5

template<int max_size>
struct FenwickTree {
    int tree[max_size + 1];
    int cnt = max_size;

    void clear() { for (int i = 1; i <= max_size; i++) tree[i] = 0; }
    void build(const int arr[], int size) {
        int cnt = size;
        clear();
        for (int i = 0; i < size; i++)
            updatePoint(i, arr[i]);
    }
    void updatePoint(int idx, int delta) {
        idx++;
        while (idx <= cnt) {
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
    FenwickTree<max_size> tree1;
    FenwickTree<max_size> tree2;

    void clear() { tree1.clear(); tree2.clear(); }
    void build(const int arr[], int size) {
        tree1.cnt = tree2.cnt = size;
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


FenwickTree<MAX_SIZE> bit;
FenwickTreeRange<MAX_SIZE> bitRange;

int main()
{
    int left, right, delta;

    // point update
    bit.clear();

    left = 0, right = 4, delta = 5;
    for (int i = left; i <= right; i++) { bit.updatePoint(i, delta); }

    left = 2, right = 4, delta = 10;
    for (int i = left; i <= right; i++) { bit.updatePoint(i, delta); }

    left = 1, right = 4;
    printf(">> Sum[%2d, %2d] = %d\n", left, right, bit.queryRange(left, right));

    // range update
    bitRange.clear();

    left = 0, right = 4, delta = 5;
    //bitRange.updateRange(left, right, delta);
    for (int i = left; i <= right; i++) { bitRange.updatePoint(i, delta); }

    left = 2, right = 4, delta = 10;
    //bitRange.updateRange(left, right, delta);
    for (int i = left; i <= right; i++) { bitRange.updatePoint(i, delta); }

    left = 1, right = 4;
    printf(">> Sum[%2d, %2d] = %d\n", left, right, bitRange.queryRange(left, right));

    return 0;
}
#endif