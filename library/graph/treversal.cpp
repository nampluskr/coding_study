#include "graph.h"
#include "func.h"

#ifndef MAX_NODES
#define MAX_NODES   100
#endif

GraphTreversal G1;

void init_graph1() {
    G1.init(10);

    G1.add(0, 1); G1.add(0, 2);
    G1.add(1, 3);
    G1.add(2, 4); G1.add(2, 5); G1.add(2, 6);
    G1.add(3, 7); G1.add(3, 8);
    G1.add(6, 9);
}

void test_dfs(int option) {
    if (option == 0) return;

    int start = 0, end = 7;
    init_graph1();

    printf("\n*** TYPE-1 DFS (Recursive)\n");
    G1.clear();
    G1.dfs1_recur(start);        // 노드 번호 작은 순으로 dfs 탐색
    print_list(G1.path);         // [0]->[1]->[3]->[7]->[8]->[2]->[4]->[5]->[6]->[9]
    G1.show_path(start, end);    

    printf("\n*** TYPE-1 DFS (Stack)\n");
    G1.dfs1_stack(start);        // 노드 번호 큰 순으로 dfs 탐색
    print_list(G1.path);         // [0]->[2]->[6]->[9]->[5]->[4]->[1]->[3]->[8]->[7]
    G1.show_path(start, end);

    printf("\n*** TYPE-2 DFS (Recursive)\n");
    G1.clear();
    G1.visited[start] = true; G1.path.push_back(start);
    G1.dfs2_recur(start);        // 노드 번호 작은 순으로 dfs 탐색
    print_list(G1.path);         // [0]->[1]->[3]->[7]->[8]->[2]->[4]->[5]->[6]->[9]
    G1.show_path(start, end);

    printf("\n*** TYPE-2 DFS (Stack)\n");
    G1.dfs2_stack(start);        // 노드 번호 작은 순으로 저장후 맨 마지막 노드부터 탐색
    print_list(G1.path);         // [0]->[1]->[2]->[4]->[5]->[6]->[9]->[3]->[7]->[8]
    G1.show_path(start, end);
}

void test_bfs(int option) {
    if (option == 0) return;

    int start = 0, end = 7;
    init_graph1();

    printf("\n*** TYPE-1 BFS (Queue)\n");
    G1.bfs1_queue(start);        // 노드 번호 작은 순으로 bfs 탐색
    print_list(G1.path);         // [0]->[1]->[2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]
    G1.show_path(start, end);

    printf("\n*** TYPE-1 BFS (Priority Queue)\n");
    G1.bfs1_pq(start);           // 노드 번호 큰 순으로 탐색
    print_list(G1.path);         // [0]->[2]->[6]->[9]->[5]->[4]->[1]->[3]->[8]->[7]
    G1.show_path(start, end);

    printf("\n*** TYPE-2 BFS (Queue)\n");
    G1.bfs2_queue(start);        // 노드 번호 작은 순으로 bfs 탐색
    print_list(G1.path);         // [0]->[1]->[2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]
    G1.show_path(start, end);

    printf("\n*** TYPE-2 BFS (Priority Queue)\n");
    G1.bfs2_pq(start);           // 노드 번호 저장후 우선순위 큰 순으로 탐색
    print_list(G1.path);         // [0]->[1]->[2]->[4]->[5]->[6]->[9]->[3]->[7]->[8]
    G1.show_path(start, end);
}