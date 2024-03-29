#include <cstdio>

extern void test_bubbleSort(int);
extern void test_selectionSort(int);
extern void test_insertionSort(int);

extern void test_shellSort(int);
extern void test_mergeSort(int);
extern void test_quickSort(int);

extern void test_countingSort(int);
extern void test_radixSort10(int);
extern void test_radixSort256(int);

int main()
{
    int opt;

    printf("\n*** Basic Sorting Methods\n");
    opt = 0;
    test_bubbleSort(opt);
    test_selectionSort(opt);
    test_insertionSort(opt);

    printf("\n*** Fast Sorting Methods\n");
    opt = 1;
    test_shellSort(opt);
    test_mergeSort(opt);
    test_quickSort(opt);

    printf("\n*** Advanced Sorting Methods\n");
    opt = 1;
    test_countingSort(opt);
    test_radixSort10(opt);
    test_radixSort256(opt);

    return 0;
}