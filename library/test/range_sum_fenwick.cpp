#if 0
#include <cstdio>

#define MAX_SIZE    100

int arr[MAX_SIZE] = { 1, 2, 1, 4, 1, 2, 1, 8, 1, 2, 1, 4, 1, 2, 1, 16 };
int size = 16;
int tree[MAX_SIZE];

void update(int idx, int delta) {
    while (idx <= size) {
        tree[idx] += delta;
        idx += idx & -idx; //���������� ������ ��ġ�� 1��
    }
}

int sum(int idx) {
    int ans = 0;
    while (idx > 0) {
        ans += tree[idx];
        idx -= idx & -idx;  //���������� ������ ��ġ�� 1�� ����.
    }
    return ans;
}
#endif