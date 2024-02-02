#pragma once

inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

/////////////////////////////////////////////////////////////////////
// Linear Search

int linearSearch(int arr[], int n, int x) {
    //// for loop
    for (int i = 0; i < n; i++)
       if (arr[i] == x) return i;

    // while loop
    int i = 0;
    while (i < n) {
        if (arr[i] == x) return i;
        i++;
    }

    return -1;
}

// Forward search
int linearSearch_recur(int arr[], int n, int x, int i) {
    if (i == n - 1) return -1;
    if (arr[i] == x) return i;
    return linearSearch_recur(arr, n, x, i + 1);
}

// Backward search
int linearSearch_recur2(int arr[], int n, int x) {
    if (n == 0) return -1;
    if (arr[n - 1] == x) return n - 1;
    return linearSearch_recur2(arr, n - 1, x);
}

int sentinelSearch(int arr[], int n, int x) {
    int last = arr[n - 1];
    arr[n - 1] = x;     // Element to be searched is placed at the last index
    int i = 0;
    while (arr[i] != x) i++;
    arr[n - 1] = last;

    if ((i < n - 1) || (arr[n - 1] == x)) return i;
    else return -1;
}

int LinearSearchTransposition(int arr[], int n, int x) {
    int i;
    for (i = 0; i < n; i++) {
        // If x is found, then swap the element with it's previous index
        if (arr[i] == x) {
            if (i == 0) return i; // If x is first element
            swap(arr[i], arr[i - 1]);
            return i;
        }
    }
    return -1;
}

int LinearSearchMoveToFront(int arr[], int n, int x) {
    int i;
    for (i = 0; i < n; i++) {
        // If x is found, then swap the element with 0-th index
        if (arr[i] == x) {
            swap(arr[i], arr[0]);
            return i;
        }
    }
    return -1;
}

/////////////////////////////////////////////////////////////////////
// Binary Search

int binarySearch(int arr[], int n, int x) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return -1;
}

int binarySearch_recur(int arr[], int lo, int hi, int x) {
    if (hi < lo) return -1;

    int mid = lo + (hi - lo) / 2;
    if (arr[mid] == x)
        return mid;
    else if (arr[mid] < x)
        return binarySearch_recur(arr, mid + 1, hi, x);
    else
        return binarySearch_recur(arr, lo, mid - 1, x);
}

int lowerBound(int arr[], int n, int x) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < x)
            lo = mid + 1;
        else                // x <= arr[mid]
            hi = mid - 1;
    }
    return lo;
}

int upperBound(int arr[], int n, int x) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= x)
            lo = mid + 1;
        else                // x < arr[mid]
            hi = mid - 1;
    }
    return lo;
}

bool decide(int arr[], int mid, int x) {
    return x <= arr[mid];
}

int parametricSearch(int arr[], int lo, int hi, int x) {
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (decide(arr, mid, x))
            hi = mid - 1;
        else
            lo = mid + 1;
    }
    return lo;
}

/////////////////////////////////////////////////////////////////////
// Quick Select

// Lomuto partition scheme
int partitionLomuto(int arr[], int lo, int hi) {
    // swap(arr[hi], arr[lo + (hi - lo) / 2]);
    int pivot = arr[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; j++)
        if (arr[j] <= pivot)
            swap(arr[++i], arr[j]);
    swap(arr[++i], arr[hi]);
    return i;
}

// Hoare partition scheme
int partitionHoare(int arr[], int lo, int hi) {
    // swap(arr[hi], arr[lo + (hi - lo) / 2]);
    int pivot = arr[lo];
    int i = lo, j = hi + 1;
    while (true) {
        do i++; while (i <= hi && arr[i] < pivot);
        do j--; while (j > lo && pivot < arr[j]);
        if (i < j) swap(arr[i], arr[j]);
        else break;
    }
    swap(arr[lo], arr[j]);
    return j;
}

void quickSelect_recur(int arr[], int lo, int hi, int k) {
    if (lo == hi) return;

    int pIdx = partitionLomuto(arr, lo, hi);
    if (k == pIdx) return;
    else if (k < pIdx)
        quickSelect_recur(arr, lo, pIdx - 1, k);
    else
        quickSelect_recur(arr, pIdx + 1, hi, k);
}

void quickSelect(int arr[], int n, int k) { 
    quickSelect_recur(arr, 0, n - 1, k);
}

int selectTopK(int arr[], int n, int k) {
    quickSelect_recur(arr, 0, n - 1, n - k);
    return arr[n - k];
}

int selectBottomK(int arr[], int n, int k) {
    quickSelect_recur(arr, 0, n - 1, k);
    return arr[k - 1];
}