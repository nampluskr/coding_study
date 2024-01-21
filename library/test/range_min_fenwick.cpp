#if 0
// https://thinkmath2020.tistory.com/709
#include <cstdio>

#define MAX_SIZE    100
#define INF         0x7fffffff

int min(int a, int b) { return (a < b) ? a: b; }

int arr[MAX_SIZE] = { 3, 2, 5, 7, 10, 3, 2, 7, 8, 2, 1, 9, 5, 10, 7, 4 };
int size = 16;

int tree1[MAX_SIZE + 1];    // prefix BIT
int tree2[MAX_SIZE + 1];    // suffix BIT

void prefix(int idx, int num) {
    idx++;
    while (idx <= size) {
        tree1[idx] = min(tree1[idx], num);
        idx += idx & -idx;
    }
}
void suffix(int idx, int num) {
    idx++;
    while (idx > 0) {
        tree2[idx] = min(tree2[idx], num);
        idx -= idx & -idx;
    }
}
int query(int left, int right) {
    left++; right++;
    int res = INF;
    int prev = left;
    int curr = prev + (prev & -prev);

    while (curr <= right) {
        res = min(res, tree2[prev]);
        prev = curr;
        curr = prev + (prev & -prev);
    }
    res = min(res, arr[prev]);
    prev = right;
    curr = prev - (prev & -prev);

    while (curr >= left) {
        res = min(res, tree1[prev]);
        prev = curr;
        curr = prev - (prev & -prev);
    }
    return res;
}

/////////////////////////////////////////////////////////////////////
int main()
{
    for (int i = 1; i <= size; i++) {
        tree1[i] = tree2[i] = INF;
    }

    int left, right, res;
    for (int i = 0; i < size; i++) { 
        prefix(i, arr[i]);
        suffix(i, arr[i]);
    }

    left = 2, right = 8;
    printf("Min[%2d, %2d] = %d\n", left, right, query(left, right));
    
    return 0;
}
#endif