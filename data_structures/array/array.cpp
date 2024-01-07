#include <cstdio>

#define MAX_SIZE    10

int arr[MAX_SIZE] = { 2, 4, 10, 5, 15, 3 };
int N = 6;      // array size

int findType1(const int arr[], int size, int key) {
    for (int i = 0; i < N; i++) {
        if (arr[i] == key) { return i; }
    }
    return -1;
}

int findType2(const int arr[], int size, int key) {
    int i = 0;
    while (i < N) {
        if (arr[i] == key) { return i; }
        i++;
    }
    return -1;
}

int findType3(int i, const int arr[], int size, int key) {
    if (i == size - 1) { return -1; }
    if (arr[i] == key) { return i; }
    return findType3(i + 1, arr, size, key);
}

int findType4(const int arr[], int size, int key) {
    if (size == 0) { return -1; }
    if (arr[size - 1] == key) { return size - 1; }
    return findType4(arr, size - 1, key);
}

void test_find(int option)
{
    if (option == 0) { return; }

    printf("\n*** Initialize ***\n");

    printf(">> ");
    for (int i = 0; i < MAX_SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");

    int res, key = 5;
    printf("\n*** Find (for loop) ***\n");
    res = findType3(0, arr, N, key);
    if (res != -1)
        printf(">> Found: %d\n", res);
    else
        printf(">> Not Found: %d\n", res);


    printf("\n*** Find (while loop) ***\n");
    res = findType3(0, arr, N, key);
    if (res != -1)
        printf(">> Found: %d\n", res);
    else
        printf(">> Not Found: %d\n", res);


    printf("\n*** Find (Recursive-1) ***\n");
    res = findType3(0, arr, N, key);
    if (res != -1)
        printf(">> Found: %d\n", res);
    else
        printf(">> Not Found: %d\n", res);


    printf("\n*** Find (Recursive-2) ***\n");
    res = findType4(arr, N, key);
    if (res != -1)
        printf(">> Found: %d\n", res);
    else
        printf(">> Not Found: %d\n", res);
}