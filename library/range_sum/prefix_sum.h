#pragma once

template<int max_size>
struct PrefixSum {
    int table[max_size + 1];

    void clear() { for (int i = 1; i <= max_size; i++) table[i] = 0; }
    void build(const int arr[], int size) {
        for (int i = 0; i < size; i++)
            table[i + 1] = table[i] + arr[i];
    }
    int queryRange(int left, int right) {
        return table[right + 1] - table[left];
    }
};