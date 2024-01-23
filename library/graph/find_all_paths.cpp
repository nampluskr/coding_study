#include "graph.h"
#include "func.h"

GraphFindAllPaths G3;

// http://www.cs.emory.edu/~cheung/Courses/253/Syllabus/NetFlow/FIGS/netflow40.gif
void init_graph3() {
    G3.init(8);
    G3.add(0, 1, 8); G3.add(0, 2, 7); G3.add(0, 3, 4);
    G3.add(1, 2, 2); G3.add(1, 4, 3); G3.add(1, 5, 9);
    G3.add(2, 3, 5); G3.add(2, 5, 6);
    G3.add(3, 5, 7); G3.add(3, 6, 2);
    G3.add(4, 7, 9);
    G3.add(5, 4, 3); G3.add(5, 6, 4); G3.add(5, 7, 5);
    G3.add(6, 7, 8);
}

void test_findAllPaths(int option) {
    if (option == 0) return;

    int start = 0, end = 7;
    init_graph3();

    printf("\n*** Backtracking DFS (Recursive)\n");
    G3.clear();
    G3.visited[start] = true; G3.path.push_back(start);
    G3.dfs_recur(start, end);    // 우선 순위 낮은 순으로 dfs 탐색 (깊이 우선)

    //printf("\n*** Backtracking DFS (Stack)\n");
    //G3.dfs_stack(start, end);    // 우선 순위 큰 순으로 dfs 탐색

    //printf("\n*** Backtracking BFS (Queue)\n");
    //G3.bfs_queue(start, end);    // 우선 순위 작은 순으로 bfs 탐색 (너비 우선)

    //printf("\n*** Backtracking BFS (Priority Queue)\n");
    //G3.bfs_pq(start, end);       // 노드 우선순위 큰 순으로 탐색
}