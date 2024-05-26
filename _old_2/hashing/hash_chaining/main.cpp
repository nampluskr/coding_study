#include <cstdio>
#include "hash_chaining_sll.h"
#include "hash_chaining_dll.h"  // swea linked list
#include "hash_chaining_bst.h"  // swea set
#include "..\..\data.h"

HashChainingSLL<Data, int> map1;
HashChainingDLL<Data, int> map2;
HashChainingBST<Data, int> map3;

template<typename T>
void test_hash_chaining(T& map) {
    Data d1{ 10, 1 }, d2{ 20, 2 }, d3{ 30, 3 };
    auto& m = map;

    printf("\n*** [Insert] ***\n");
    m.clear();
    m.insert(d1, 1111);
    m.insert(d2, 1111);

    printf("\n*** [Find] ***\n");
    printf(">> find d1 = %d\n", (int)m.find(d1));
    printf(">> find d2 = %d\n", (int)m.find(d2));
    printf(">> find d3 = %d\n", (int)m.find(d3));

    printf("\n*** [Erase] ***\n");
    m.erase(d1);
    m.erase(d2);
    m.erase(d3);

    printf("\n*** [Find] ***\n");
    printf(">> find d1 = %d\n", (int)m.find(d1));
    printf(">> find d2 = %d\n", (int)m.find(d2));
    printf(">> find d3 = %d\n", (int)m.find(d3));

    printf("\n*** [Assign] ***\n");
    m[d1] = 111;
    m[d2] = 222;

    printf(">> map[d1] = %d\n", m[d1]);
    printf(">> map[d2] = %d\n", m[d2]);
    printf(">> map[d3] = %d\n", m[d3]);

    printf("\n*** [Find] ***\n");
    printf(">> find d1 = %d\n", (int)m.find(d1));
    printf(">> find d2 = %d\n", (int)m.find(d2));
    printf(">> find d3 = %d\n", (int)m.find(d3));

    printf("\n*** [Erase] ***\n");
    m.clear();

    printf("\n*** [Find] ***\n");
    printf(">> find d1 = %d\n", (int)m.find(d1));
    printf(">> find d2 = %d\n", (int)m.find(d2));
    printf(">> find d3 = %d\n", (int)m.find(d3));

    m.clear();
}

int main()
{
    test_hash_chaining(map1);
    test_hash_chaining(map2);
    test_hash_chaining(map3);

    return 0;
}
