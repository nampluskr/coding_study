#include "graph.h"
#include "func.h"

GraphFindAPath G2;

// http://www.cs.emory.edu/~cheung/Courses/253/Syllabus/NetFlow/FIGS/netflow40.gif
void init_graph2() {
    G2.init(8);
    G2.add(0, 1, 8); G2.add(0, 2, 7); G2.add(0, 3, 4);
    G2.add(1, 2, 2); G2.add(1, 4, 3); G2.add(1, 5, 9);
    G2.add(2, 3, 5); G2.add(2, 5, 6);
    G2.add(3, 5, 7); G2.add(3, 6, 2);
    G2.add(4, 7, 9);
    G2.add(5, 4, 3); G2.add(5, 6, 4); G2.add(5, 7, 5);
    G2.add(6, 7, 8);
}

void test_dfs_findAPath(int option) {
    if (option == 0) return;

    int start = 0, end = 7;
    init_graph2();

    printf("\n*** TYPE-1 DFS (Recursive)\n");
    G2.clear();
    G2.dfs1_recur(start, end);   // 노드 우선순위 작은 순으로 dfs 탐색
    print_list(G2.path);         // [0]->[1]->[2]->[3]->[5]->[4]->[7]

    printf("\n*** TYPE-1 DFS (Stack)\n");
    G2.dfs1_stack(start, end);   // 노드 우선 순위 큰 순으로 dfs 탐색
    print_list(G2.path);         // [0]->[3]->[6]->[7]

    printf("\n*** TYPE-2 DFS (Recursive)\n");
    G2.clear();
    G2.visited[start] = true; G2.path.push_back(start);
    G2.dfs2_recur(start, end);   // 노드 우선순위 작은 순으로 dfs 탐색
    print_list(G2.path);         // [0]->[1]->[2]->[3]->[5]->[4]->[7]->[6]

    printf("\n*** TYPE-2 DFS (Stack)\n");
    G2.dfs2_stack(start, end);   // 노드 우선순위 작은 순으로 저장후 맨 마지막 노드부터 탐색
    print_list(G2.path);         // [0]->[1]->[2]->[3]->[5]->[6]->[7]
}

void test_bfs_findAPath(int option) {
    if (option == 0) return;

    int start = 0, end = 7;
    init_graph2();

    printf("\n*** TYPE-1 BFS (Queue)\n");
    G2.bfs1_queue(start, end);   // 노드 우선순위 작은 순으로 bfs 탐색
    print_list(G2.path);         // 

    printf("\n*** TYPE-1 BFS (Priority Queue)\n");
    G2.bfs1_pq(start, end);      // 노드 우선순위 높은 순으로 bfs 탐색
    print_list(G2.path);         // 
    G2.trace(start, end);


    printf("\n*** TYPE-2 BFS (Queue)\n");
    G2.bfs2_queue(start, end);   // 노드 우선순위 작은 순으로 bfs 탐색
    print_list(G2.path);         // 

    printf("\n*** TYPE-2 BFS (Priority Queue)\n");
    G2.bfs2_pq(start, end);      // 노드 우선순위 저장후 우선순위 큰 순으로 탐색
    print_list(G2.path);         // 
}