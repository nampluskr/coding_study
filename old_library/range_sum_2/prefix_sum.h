#pragma once

#ifndef MAX_SIZE
#define MAX_SIZE    1000000
#endif

#include "func.h"


struct PrefixSum {
    int table[MAX_SIZE + 1];

    void init(int size) {
        for (int i = 0; i < size; i++) { table[i] = 0; }
    }
    void build(const int arr[], int size) {
        table[0] = 0;
        for (int i = 0; i < size; i++) { table[i + 1] = table[i] + arr[i]; }
    }
    int queryRange(int left, int right) {
        return table[right + 1] - table[left];
    }
};