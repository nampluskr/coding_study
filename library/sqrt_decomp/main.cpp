extern void test_rngsum1(int);
extern void test_rngsum2(int);
extern void test_rngmax1(int);
extern void test_rngmax2(int);
extern void test_rngmax3(int);

int main()
{
    test_rngsum1(1);
    test_rngsum2(1);
    test_rngmax1(0);
    test_rngmax2(0);
    test_rngmax3(0);

    return 0;
}