// Counting Sort / Radix Sort in base 10 and 256 (test array size = 10^6)
#include <cstdio>
#include <ctime>

#define MAX_SIZE	1000000		// max. array size
#define MAX_NUM		100000		// base for counting sort


/////////////////////////////////////////////////////////////////////
void countingSort(int arr[], int size, int max_num = MAX_NUM) {
    int base = max_num;		// 0 <= arr[j] < base (MAX_NUM)
    int* count = new int[base], * sorted = new int[size];

    for (int j = 0; j < base; j++) { count[j] = 0; }				// initialize
    for (int j = 0; j < size; j++) { count[arr[j]]++; }				// count
    for (int j = 1; j < base; j++) { count[j] += count[j - 1]; }	// accumulate
    for (int j = size - 1; j >= 0; j--)
        sorted[--count[arr[j]]] = arr[j];							// sort
    for (int j = 0; j < size; j++) { arr[j] = sorted[j]; }			// copy

    delete[] count, sorted;
}

void radixSort10(int arr[], int size) {
    int base = 10;			// 0 <= arr[j] < base^digits (= 10^6)
    int decimal = 1;
    int* count = new int[base], * sorted = new int[size];

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
    int* count = new int[base], * sorted = new int[size];

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

/////////////////////////////////////////////////////////////////////
static unsigned long long seed;;
int arr[MAX_SIZE];
int size = 1000000;

static int rand() {
    seed = seed * 25214903917ULL + 11ULL;
    return (seed >> 16) & 0x3fffffff;
}

void init(int arr[], int size) {
    seed = 23;
    for (int i = 0; i < size; i++)
        arr[i] = rand() % MAX_NUM;
}

/////////////////////////////////////////////////////////////////////
void test_countSort() {
    init(arr, size);
    printf("\n[Counting Sort] size = %d\n", size);

    clock_t start = clock();
    countingSort(arr, size, MAX_NUM);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
}

void test_radixSort10() {
    init(arr, size);
    printf("\n[Radix Sort in base 10] size = %d\n", size);

    clock_t start = clock();
    radixSort10(arr, size);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
}

void test_radixSort256() {
    init(arr, size);
    printf("\n[Radix Sort in base 256] size = %d\n", size);

    clock_t start = clock();
    radixSort256(arr, size);
    printf(">> Time = %d ms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
}
