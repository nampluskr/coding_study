#include "graph.h"
#include "func.h"

#ifndef INF
#define INF 0x7fffffff
#endif

GraphMaxCostPath G4;

// http://www.cs.emory.edu/~cheung/Courses/253/Syllabus/NetFlow/FIGS/netflow40.gif
void init_graph4() {
    G4.init(8);
    G4.add(0, 1, 8); G4.add(0, 2, 7); G4.add(0, 3, 4);
    G4.add(1, 2, 2); G4.add(1, 4, 3); G4.add(1, 5, 9);
    G4.add(2, 3, 5); G4.add(2, 5, 6);
    G4.add(3, 5, 7); G4.add(3, 6, 2);
    G4.add(4, 7, 9);
    G4.add(5, 4, 3); G4.add(5, 6, 4); G4.add(5, 7, 5);
    G4.add(6, 7, 8); 
}

void test_maxCostPath(int option) {
    if (option == 0) return;

    int start = 0, end = 7;
    init_graph4();

    //printf("\n*** Backtracking DFS (Recursive)\n");
    //G4.clear();
    //G4.visited[start] = true; G4.path.push_back(start);
    //G4.dfs_recur(start, 0, end);    // 우선 순위 낮은 순으로 dfs 탐색 (깊이 우선)

    printf("\n*** Backtracking DFS (Stack)\n");
    G4.dfs_stack(start, end);    // 우선 순위 큰 순으로 dfs 탐색

    //printf("\n*** Backtracking BFS (Queue)\n");
    //G4.bfs_queue(start, end);    // 우선 순위 작은 순으로 bfs 탐색 (너비 우선)

    //printf("\n*** Backtracking BFS (Priority Queue)\n");
    //G4.bfs_pq(start, end);       // 노드 우선순위 큰 순으로 탐색
}