#include <stack>
#include "graph.h"
using namespace std;

void set_graph() {
    for (int i = 0; i < N; i++) { nodes[i] = {}; }
    nodeCnt = 0;
    nodeMap.clear();

    add_node("A", "B"); add_node("A", "C");
    add_node("B", "D");
    add_node("C", "G"); add_node("C", "H"); add_node("C", "I");
    add_node("D", "E"); add_node("D", "F");
    add_node("I", "J");
}

void trace(int start, int end) {
    if (end == start) { path.push_back(end); }
    if (parent[end] == -1) { return; }
    trace(start, parent[end]);
    path.push_back(end);
}

void init() {
    for (int i = 0; i < N; i++) {
        visited[i] = false;
        parent[i] = -1;
    }
    history.clear();
    path.clear();
}


void dfs1(int cur) {
    if (!visited[cur]) {
        visited[cur] = true; history.push_back(cur);

        for (int next : nodes[cur].nodeList)
            if (!visited[next]) {
                parent[next] = cur;
                dfs1(next);
            }
    }
}

void dfs2(int cur) {
    for (int next : nodes[cur].nodeList)
        if (!visited[next]) {
            visited[next] = true; history.push_back(next);
            parent[next] = cur;
            dfs2(next);
        }
}

void dfs_stack(int start) {
    stack<int> S;
    S.push(start);

    while (!S.empty()) {
        int cur = S.top(); S.pop();

        if (!visited[cur]) {
            visited[cur] = true; history.push_back(cur);

            for (int next : nodes[cur].nodeList)
                if (!visited[next]) {
                    parent[next] = cur;
                    S.push(next);
                }
        }
    }
}

int main()
{
    init();
    set_graph();
    int start = get_nodeIndex("A");
    int end = get_nodeIndex("J");

    //printf("\n*** DFS-1 ***\n");
    //init();
    //dfs1(start);        print_list(history);
    //trace(start, end);  print_list(path);

    //printf("\n*** DFS-2 ***\n");
    //init();
    //visited[start] = true;  history.push_back(start);
    //dfs2(start);        print_list(history);
    //trace(start, end);  print_list(path);

    printf("\n*** DFS-Stack ***\n");
    init();
    dfs_stack(start);  print_list(history);
    trace(start, end);  print_list(path);

    return 0;
}