#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include "hash.h"
#include <cstring>

struct Data {
    int value, idx;
};

HashMap<int, Data> int_dataMap;
HashMap<int, LinkedList<Data>> int_listMap;

HashMap<const char*, Data> str_dataMap;
HashMap<const char*, LinkedList<Data>> str_listMap;

void test_int_dataMap() {
    int_dataMap.clear();
    int_dataMap.emplace(1001, { 10, 1 });
    int_dataMap.emplace(2002, { 20, 2 });
    int_dataMap.emplace(3003, { 30, 3 });
    int_dataMap.emplace(4004, { 40, 4 });

    auto data = int_dataMap[5005];
    int_dataMap[4004] = { 400, 40 };
    int_dataMap.clear();
}

void test_int_listMap() {
    int_listMap.clear();
    int_listMap[1001].push_back({ 10, 1 });
    int_listMap[1001].push_back({ 20, 2 });
    int_listMap[1001].push_back({ 30, 3 });

    for (auto ptr = int_listMap[1001].head; ptr; ptr = ptr->next) {
        auto data = ptr->data;
        printf("{%d, %d} ", data.value, data.idx);
    }
    printf("\n");

    int_listMap[1001].clear();
    for (auto ptr = int_listMap[1001].head; ptr; ptr = ptr->next) {
        auto data = ptr->data;
        printf("{%d, %d} ", data.value, data.idx);
    }
    printf("\n");
}

void test_str_dataMap() {
    char names[10][20] = {};
    strcpy(names[0], "aaa");
    strcpy(names[1], "bbb");
    strcpy(names[2], "ccc");
    strcpy(names[3], "ddd");

    str_dataMap.clear();
    str_dataMap.emplace(names[0], { 10, 1 });
    str_dataMap.emplace(names[1], { 20, 2 });
    str_dataMap.emplace(names[2], { 30, 3 });
    str_dataMap.emplace(names[3], { 40, 4 });
}

void test_str_listMap() {
    char names[10][20] = {};
    strcpy(names[0], "aaa");
    strcpy(names[1], "bbb");
    strcpy(names[2], "ccc");
    strcpy(names[3], "ddd");

    str_listMap.clear();
    str_listMap[names[0]].push_back({ 10, 1 });
    str_listMap[names[0]].push_back({ 20, 2 });
    str_listMap[names[0]].push_back({ 30, 3 });
    str_listMap[names[0]].push_back({ 30, 3 });

    printf(">> ");
    for (auto ptr = str_listMap[names[0]].head; ptr; ptr = ptr->next) {
        auto data = ptr->data;
        printf("{%d, %d} ", data.value, data.idx);
    }
    printf("\n");

    str_listMap[names[0]].clear();
    printf(">> ");
    for (auto ptr = str_listMap[names[0]].head; ptr; ptr = ptr->next) {
        auto data = ptr->data;
        printf("{%d, %d} ", data.value, data.idx);
    }
    printf("\n");
}