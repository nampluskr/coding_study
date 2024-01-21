#include "graph.h"

#ifndef MAX_NODES
#define MAX_NODES   100
#endif

GraphWeighted<MAX_NODES> G;

int start = 0;

void init_graph(int num_nodes) {
    G.init(num_nodes);

    // 노드 번호 오름 차순으로 추가 (탐색 순서 결정)
    G.addEdge(0, 1); G.addEdge(0, 2);
    G.addEdge(1, 3);
    G.addEdge(2, 4); G.addEdge(2, 5); G.addEdge(2, 6);
    G.addEdge(3, 7); G.addEdge(3, 8);
    G.addEdge(6, 9);
}

void test_dfs() {
    init_graph(10);

    printf("\n*** TYPE-1 DFS (Recursive)\n");
    G.clear();
    G.dfs1_recur(start);    // 노드 번호 작은 순으로 dfs 탐색
    G.show_history();       // [0]->[1]->[3]->[7]->[8]->[2]->[4]->[5]->[6]->[9]

    printf("\n*** TYPE-1 DFS (Stack)\n");
    G.dfs1_stack(start);    // 노드 번호 큰 순으로 dfs 탐색
    G.show_history();       // [0]->[2]->[6]->[9]->[5]->[4]->[1]->[3]->[8]->[7]

    printf("\n*** TYPE-2 DFS (Recursive)\n");
    G.clear();
    G.visited[start] = true; G.history.push_back(start);
    G.dfs2_recur(start);    // 노드 번호 작은 순으로 dfs 탐색
    G.show_history();       // [0]->[1]->[3]->[7]->[8]->[2]->[4]->[5]->[6]->[9]

    printf("\n*** TYPE-2 DFS (Stack)\n");
    G.dfs2_stack(start);    // 노드 번호 작은 순으로 저장후 맨 마직막 노드부터 탐색
    G.show_history();       // [0]->[1]->[2]->[4]->[5]->[6]->[9]->[3]->[7]->[8]
}

void test_bfs() {
    init_graph(10);

    printf("\n*** TYPE-1 BFS (Queue)\n");
    G.bfs1_queue(start);    // 노드 번호 작은 순으로 bfs 탐색
    G.show_history();       // [0]->[1]->[2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]

    printf("\n*** TYPE-2 DFS (Queue)\n");
    G.bfs2_queue(start);    // 노드 번호 작은 순으로 bfs 탐색
    G.show_history();       // [0]->[1]->[2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]
}