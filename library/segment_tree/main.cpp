extern void test_seg(int);
extern void test_seglazy(int);
extern void test_segref(int);
extern void test_segboj(int);

int main()
{
    test_seg(1);
    test_seglazy(1);
    test_segref(0);
    test_segboj(0);

    return 0;
}