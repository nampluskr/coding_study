#pragma once

inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }
inline int min(int a, int b) { return (a < b) ? a : b; }


/////////////////////////////////////////////////////////////////////
// Basic sorting methods O(N^2)

void bubbleSort(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
       bool swapped = false;
       for (int j = 0; j < i; j++)
           if (arr[j] > arr[j + 1]) {
               swap(arr[j], arr[j + 1]);
               swapped = true;
           }
       if (!swapped)
           break;
    }
}

void bubbleSort_recur(int arr[], int n) {
     if (n == 1) return;     // base case
     int cnt = 0;
     for (int i = 0; i < n - 1; i++)
         if (arr[i] > arr[i + 1]) {
             swap(arr[i], arr[i + 1]);
             cnt++;
         }
     if (cnt == 0) return;
     bubbleSort_recur(arr, n - 1);
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        if (minIdx != i)
            swap(arr[i], arr[minIdx]);
    }
}

int get_minIndex(int arr[], int i, int j){
    if (i == j) return i;
    int minIdx = get_minIndex(arr, i + 1, j);
    return (arr[i] < arr[minIdx])? i: minIdx;
}

void selectionSort_recur(int arr[], int n, int idx = 0) {
    if (idx == n) return;
    int minIdx = get_minIndex(arr, idx, n - 1);
    if (minIdx != idx) swap(arr[minIdx], arr[idx]);
    selectionSort_recur(arr, n, idx + 1);
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j;
        for (j = i - 1; j >= 0 && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = key;
    }
}

void insertionSort_recur(int arr[], int n) {
    if (n <= 1) return;
    insertionSort_recur(arr, n - 1);

    int j, last = arr[n - 1];
    for (j = n - 2; j >= 0 && arr[j] > last; j--)
        arr[j + 1] = arr[j];
    arr[j + 1] = last;
}


/////////////////////////////////////////////////////////////////////
// Fast sorting methods O(N log N)

void shellSort(int arr[], int n) {
    int h = 1;
    while (h < n / 3)       // by Knuth (1973)
        h = h * 3 + 1;      // 1, 4, 13, 40, 121, 364, 1093, ...

    while (h >= 1) {
        for (int i = h; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i - h; j >= 0 && arr[j] > temp; j -= h)
                arr[j + h] = arr[j];
            arr[j + h] = temp;
        }
        h = h / 3;
    }
}

void merge(int arr[], int s, int m, int e, int aux[]){
    if (arr[m] <= arr[m + 1]) return;

    for (int i = s, j = 0; i <= m; i++, j++)
        aux[j] = arr[i];
    int i = m + 1, j = 0, k = s;
    while (i <= e && j <= m - s){
        if (aux[j] <= arr[i])
            arr[k++] = aux[j++];
        else
            arr[k++] = arr[i++];
    }
    while (j <= m - s)
        arr[k++] = aux[j++];
}

// Merge Sort (Top-down)
void mergeSort_recur(int arr[], int s, int e, int aux[]) {
    if (s < e) {
        int m = s + (e - s) / 2;
        mergeSort_recur(arr, s, m, aux);
        mergeSort_recur(arr, m + 1, e, aux);
        merge(arr, s, m, e, aux);
    }
}

void mergeSort(int arr[], int n) {
    int* aux = new int[n];
    mergeSort_recur(arr, 0, n - 1, aux);
    delete[] aux;
}

// Merge sort (Bottom-up)
void mergeSort2(int arr[], int n) {
    int* aux = new int[n];
    for (int size = 1; size < n; size *= 2)
        for (int s = 0; s < n - size; s += size * 2)
            merge(arr, s, s + size - 1, min(s + size * 2 - 1, n - 1), aux);
    delete[] aux;
}

struct Pair {
    int leftLast, rightFirst;
};

// Lomuto partition scheme
Pair partitionLomuto(int arr[], int s, int e) {
    int pivot = arr[e];
    int i = s;
    for (int j = s; j < e; j++)
        if (arr[j] <= pivot)
            swap(arr[i++], arr[j]);
    swap(arr[i], arr[e]);
    return { i - 1, i + 1 };
}

// Hoare partition scheme
Pair partitionHoare(int arr[], int s, int e) {
    int pivot = arr[s + (e - s) / 2];
    int i = s, j = e;
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (pivot < arr[j]) j--;
        if (i < j) swap(arr[i++], arr[j--]);
        else i++;
    }
    return { j, j + 1 };
}

void quickSort_recur(int arr[], int s, int e) {
    if (s >= e) return;

    //auto pIdx = partitionLomuto(arr, s, e);
    auto pIdx = partitionHoare(arr, s, e);

    quickSort_recur(arr, s, pIdx.leftLast);
    quickSort_recur(arr, pIdx.rightFirst, e);
}

void quickSort(int arr[], int n) {
    quickSort_recur(arr, 0, n - 1);
}

void quickSort_iter(int arr[], int l, int h) {
    int* stack = new int[h - l + 1];

    int top = -1;
    stack[++top] = l;
    stack[++top] = h;

    while (top >= 0) {
        h = stack[top--];
        l = stack[top--];

        //auto p = partitionLomuto(arr, l, h);
        auto p = partitionHoare(arr, l, h);

        if (p.leftLast > l) {
            stack[++top] = l;
            stack[++top] = p.leftLast;
        }
        if (p.rightFirst < h) {
            stack[++top] = p.rightFirst;
            stack[++top] = h;
        }
    }
    delete[] stack;
}


/////////////////////////////////////////////////////////////////////
// Special sorting methods O(N)

void countingSort(int arr[], int n, int max_num) {
    int base = max_num;		    // 0 <= arr[j] < base (MAX_NUM)
    int* count = new int[base];
    int* sorted = new int[n];

    for (int j = 0; j < base; j++) { count[j] = 0; }				// initialize
    for (int j = 0; j < n; j++) { count[arr[j]]++; }				// count
    for (int j = 1; j < base; j++) { count[j] += count[j - 1]; }	// accumulate
    for (int j = n - 1; j >= 0; j--)
        sorted[--count[arr[j]]] = arr[j];							// sort
    for (int j = 0; j < n; j++) { arr[j] = sorted[j]; }			// copy

    delete[] count, sorted;
}

void radixSort10(int arr[], int n) {
    int base = 10;			    // 0 <= arr[j] < base^digits (= 10^6)
    int decimal = 1;
    int* count = new int[base];
    int* sorted = new int[n];

    // counting sort in base 10 for 10^i digit
    for (int i = 0; i < 6; i++, decimal *= 10) {

        for (int j = 0; j < base; j++) { count[j] = 0; }
        for (int j = 0; j < n; j++) { count[arr[j] / decimal % base]++; }
        for (int j = 1; j < base; j++) { count[j] += count[j - 1]; }
        for (int j = n - 1; j >= 0; j--)
            sorted[--count[arr[j] / decimal % base]] = arr[j];	// sort
        for (int j = 0; j < n; j++) { arr[j] = sorted[j]; }	// copy
    }
    delete[] count, sorted;
}

void radixSort256(int arr[], int n) {
    int base = (1 << 8);        // 0 <= arr[j] < 2^32 (= 256^4)
    int mask = base - 1;
    int* count = new int[base];
    int* sorted = new int[n];

    // counting sort in base 256 for 256^i digit
    for (int i = 0; i < 32; i += 8) {

        for (int j = 0; j < base; j++) { count[j] = 0; }
        for (int j = 0; j < n; j++) { count[(arr[j] >> i) & mask]++; }
        for (int j = 1; j < base; j++) { count[j] += count[j - 1]; }
        for (int j = n - 1; j >= 0; j--)
            sorted[--count[(arr[j] >> i) & mask]] = arr[j];		// sort
        for (int j = 0; j < n; j++) { arr[j] = sorted[j]; }	// copy
    }
    delete[] count, sorted;
}