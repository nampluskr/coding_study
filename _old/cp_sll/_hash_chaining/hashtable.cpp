#include <iostream>
#include "hashtable.h"
#include "../data.h"

HashTable<int, int> intMap;
HashTable<Data, int> dataMap;

void test_intHashTable(int option) {
    // if (option == 0) return ;

    // auto& map = intMap;
    // map.clear();
    // map.insert(10, 1);
    // map.insert(20, 2);
    // map.insert(30, 3);

    // printf("map[%d] = %d\n", 10, map[10]);
    // printf("map[%d] = %d\n", 20, map[20]);
    // printf("map[%d] = %d\n", 30, map[30]);
    // printf("map[%d] = %d\n", 40, map[40]);

    // // map.erase(10);
    // // map.erase(20);
    // // map.erase(30);

    // printf("map[%d] = %d\n", 10, map[10]);
    // printf("map[%d] = %d\n", 20, map[20]);
    // printf("map[%d] = %d\n", 30, map[30]);
    // printf("map[%d] = %d\n", 40, map[40]);

    // map[10] = 100;
    // map[20] = 200;
    // map[30] = 300;
    // map[40] = 400;

    // printf("map[%d] = %d\n", 10, map[10]);
    // printf("map[%d] = %d\n", 20, map[20]);
    // printf("map[%d] = %d\n", 30, map[30]);
    // printf("map[%d] = %d\n", 40, map[40]);
}

void test_dataHashTable(int option) {
    if (option == 0) return;

    auto& map = dataMap;
    map.clear();

    map.insert({ 10, 111 }, 1);
    map.insert({ 20, 222 }, 2);
    map.insert({ 30, 333 }, 3);

    // auto key = Data{ 20, 222 };
    // int hash_value = hash_func<Data>(key);
    // auto res = map.table[hash_value].find({ key, {} });

    auto res1 = map.find({ 20, 222 });
    auto res2 = map.find({ 20, 333 });

    // printf("map[%s] = %d\n", Data{ 10, 111 }.str().c_str(), map[{ 10, 111 }]);
    // printf("map[%s] = %d\n", Data{ 20, 222 }.str().c_str(), map[{ 20, 222 }]);
    // printf("map[%s] = %d\n", Data{ 30, 333 }.str().c_str(), map[{ 30, 333 }]);
    // printf("map[%s] = %d\n", Data{ 40, 444 }.str().c_str(), map[{ 40, 444 }]);

}


int main()
{
    test_intHashTable(0);
    test_dataHashTable(1);

    return 0;
}