#include <cstdio>

extern void test_heapSort();
extern void test_heapify();
extern void test_topK1();
extern void test_topK2();

int main()
{
    printf("\n*** [Heap Sort]\n");
    test_heapSort();

    printf("\n*** [Heapifty]\n");
    test_heapify();

    printf("\n*** [Top-K-1]\n");
    test_topK1();

    printf("\n*** [Top-K-2]\n");
    test_topK2();

    return 0;
}