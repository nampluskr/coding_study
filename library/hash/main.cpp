#include <cstdio>

extern void test_int_dataMap();
extern void test_int_listMap();
extern void test_str_dataMap();
extern void test_str_listMap();

int main()
{
    printf("\n*** [Hash Map int => data] \n");
    test_int_dataMap();
    
    printf("\n*** [Hash Map int => list] \n");
    test_int_listMap();

    printf("\n*** [Hash Map str => data] \n");
    test_str_dataMap();

    printf("\n*** [Hash Map str => list] \n");
    test_str_listMap();

    return 0;
}