#include <cstdio>
#include "seg_tree.h"

#define N 10

SegTree<N> seg;
SegTreeLazy<N> seglazy;
SegmentTreeLazy segref;
SegTreeLazyBOJ<N> segboj;

//int arr[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int arr[N] = { 3, 6, 2, 5, 3, 1, 8, 9, 7, 3 };

void test_seg(int option) {
    if (option == 0) return;

    printf("\n[ Segment Tree - Range Sum]\n");
   
    seg.init();
    seg.build(arr);

    int left = 0, right = N - 1;
    int res = seg.queryRange(0, N - 1);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);

    seg.updateRange(3, 7, 2);
    //for (int i = 3; i <= 7; i++) { seg.updatePoint(i, 2); }
    res = seg.queryRange(0, N - 1);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);

    seg.updateRange(4, 9, 1);
    //for (int i = 4; i <= 9; i++) { seg.updatePoint(i, 1); }
    res = seg.queryRange(0, N - 1);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);
}

void test_seglazy(int option) {
    if (option == 0) return;

    printf("\n[ Segment Tree - Range Sum (Lazy Propagation)]\n");
    
    //seglazy.init();
    seglazy.build(arr);

    int left = 0, right = N - 1;
    int res = seglazy.queryRange(0, N - 1);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);

    seglazy.updateRange(3, 7, 2);
    //for (int i = 3; i <= 7; i++) { seglazy.updatePoint(i, 2); }
    res = seglazy.queryRange(0, N - 1);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);

    seglazy.updateRange(4, 9, 1);
    //for (int i = 4; i <= 9; i++) { seglazy.updatePoint(i, 1); }
    res = seglazy.queryRange(0, N - 1);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);
}

void test_segref(int option) {
    if (option == 0) return;

    printf("\n[ Segment Tree - Range Sum (Lazy Propagation)]\n");

    segref.build(arr, N);

    int left = 0, right = N - 1;
    int res = segref.query(0, N - 1);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);

    segref.update(3, 7, 2);
    //for (int i = 3; i <= 7; i++) { seglazy.updatePoint(i, 2); }
    res = segref.query(0, N - 1);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);
}

void test_segboj(int option) {
    if (option == 0) return;

    printf("\n[ Segment Tree - Range Sum (Lazy Propagation)]\n");

    segboj.build(arr);

    int left = 0, right = N - 1;
    int res = segboj.queryRange(0, N - 1);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);

    segboj.updateRange(3, 7, 2);
    //for (int i = 3; i <= 7; i++) { segboj.updatePoint(i, 2); }
    res = segboj.queryRange(0, N - 1);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);

    segboj.updateRange(4, 9, 1);
    //for (int i = 4; i <= 9; i++) { segboj.updatePoint(i, 1); }
    res = segboj.queryRange(0, N - 1);
    printf(">> Range [%d, %d]: sum = %d\n", left, right, res);
}
