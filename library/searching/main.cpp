#include <cstdio>

extern void test_linearSearch(int);
extern void test_binarySearch(int);
extern void test_quickSelect(int);

int main()
{
    int opt;

    opt = 0;
    test_linearSearch(opt);
    test_binarySearch(opt);

    opt = 1;
    test_quickSelect(opt);

    return 0;
}