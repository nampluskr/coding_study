#pragma once

int min(int a, int b);
int max(int a, int b);
int ceil(int a, int b);
int sqrt(int n);
int rand(unsigned long long seed);

template<typename T>
void print_rangeSum(T& rngSum, int left, int right);