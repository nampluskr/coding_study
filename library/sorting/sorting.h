#pragma once

inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }


/////////////////////////////////////////////////////////////////////
// Basic sorting methods O(N^2)

void bubbleSort(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
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

void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        if (minIdx != i)
            swap(arr[i], arr[minIdx]);
    }
}

void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int temp = arr[i];
        int j;
        for (j = i - 1; j >= 0 && arr[j] > temp; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = temp;
    }
}


/////////////////////////////////////////////////////////////////////
// Fast sorting methods O(N log N)

void shellSort(int arr[], int size) {
    int h = 1;
    while (h < size / 3)    // by Knuth (1973)
        h = h * 3 + 1;      // 1, 4, 13, 40, 121, 364, 1093, ...

    while (h >= 1) {
        for (int i = h; i < size; i++) {
            int temp = arr[i];
            int j;
            for (j = i - h; j >= 0 && arr[j] > temp; j -= h)
                arr[j + h] = arr[j];
            arr[j + h] = temp;
        }
        h = h / 3;
    }
}

void mergeSort(int arr[], int size) {
}

void quickSort(int arr[], int size) {
}





/////////////////////////////////////////////////////////////////////
// Special sorting methods O(N)

void countingSort(int arr[], int size, int max_num) {
    int base = max_num;		    // 0 <= arr[j] < base (MAX_NUM)
    int* count = new int[base];
    int* sorted = new int[size];

    for (int j = 0; j < base; j++) { count[j] = 0; }				// initialize
    for (int j = 0; j < size; j++) { count[arr[j]]++; }				// count
    for (int j = 1; j < base; j++) { count[j] += count[j - 1]; }	// accumulate
    for (int j = size - 1; j >= 0; j--)
        sorted[--count[arr[j]]] = arr[j];							// sort
    for (int j = 0; j < size; j++) { arr[j] = sorted[j]; }			// copy

    delete[] count, sorted;
}

void radixSort10(int arr[], int size) {
    int base = 10;			    // 0 <= arr[j] < base^digits (= 10^6)
    int decimal = 1;
    int* count = new int[base];
    int* sorted = new int[size];

    // counting sort in base 10 for 10^i digit
    for (int i = 0; i < 6; i++, decimal *= 10) {

        for (int j = 0; j < base; j++) { count[j] = 0; }
        for (int j = 0; j < size; j++) { count[arr[j] / decimal % base]++; }
        for (int j = 1; j < base; j++) { count[j] += count[j - 1]; }
        for (int j = size - 1; j >= 0; j--)
            sorted[--count[arr[j] / decimal % base]] = arr[j];	// sort
        for (int j = 0; j < size; j++) { arr[j] = sorted[j]; }	// copy
    }
    delete[] count, sorted;
}

void radixSort256(int arr[], int size) {
    int base = (1 << 8);        // 0 <= arr[j] < 2^32 (= 256^4)
    int mask = base - 1;
    int* count = new int[base];
    int* sorted = new int[size];

    // counting sort in base 256 for 256^i digit
    for (int i = 0; i < 32; i += 8) {

        for (int j = 0; j < base; j++) { count[j] = 0; }
        for (int j = 0; j < size; j++) { count[(arr[j] >> i) & mask]++; }
        for (int j = 1; j < base; j++) { count[j] += count[j - 1]; }
        for (int j = size - 1; j >= 0; j--)
            sorted[--count[(arr[j] >> i) & mask]] = arr[j];		// sort
        for (int j = 0; j < size; j++) { arr[j] = sorted[j]; }	// copy
    }
    delete[] count, sorted;
}