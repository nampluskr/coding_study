#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <string>
#include <cstring>
#include <unordered_map>
using namespace std;

#define MAX_NAME    11
#define N           100

struct Node {
    char name[MAX_NAME];
    vector<int> nodeList;
};

Node nodes[N];       //  노드 연결 정보
int nodeCnt;
unordered_map<string, int> nodeMap;

int visited[N];
int parent[N];

vector<int> history;
vector<int> path;

/////////////////////////////////////////////////////////////////////
int get_nodeIndex(const char name[]) {
    int nIdx;
    auto ptr = nodeMap.find(name);
    if (ptr == nodeMap.end()) {
        nIdx = nodeCnt++;
        strcpy_s(nodes[nIdx].name, name);
        nodeMap.emplace(name, nIdx);
    }
    else { nIdx = ptr->second; }
    return nIdx;
}

void add_node(const char name1[], const char name2[]) {
    int nIdx1 = get_nodeIndex(name1);
    int nIdx2 = get_nodeIndex(name2);

    nodes[nIdx1].nodeList.push_back(nIdx2);
    nodes[nIdx2].nodeList.push_back(nIdx1);
}

void print_list(const vector<int>& list) {
    int i;
    for (i = 0; i < list.size() - 1; i++)
        printf("[%s]->", nodes[list[i]].name);
    printf("[%s]\n", nodes[list[i]].name);
}