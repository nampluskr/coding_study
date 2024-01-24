## [Backtracking] Recursion / Queue / Priority Queue / Stack

```cpp
#if 1
#include <vector>
#include <set>
#include <stack>
#include <queue>
using namespace std;

#define MAX_NODES   10
#define INF         99

struct Edge {
    int to, cost;
    bool operator<(const Edge& edge) const {
        return (cost < edge.cost) || (cost == edge.cost && to < edge.to);
    }
};
set<Edge> adj[MAX_NODES];       // adjacency list
//vector<Edge> adj[MAX_NODES];       // adjacency list
bool visited[MAX_NODES];        // visiting flag
vector<int> path;               // visiting history
//int query[MAX_NODES];
int N;                          // number of nodes
int res = 0;


struct Edge2 {
    int to, cost;
    bool visited[MAX_NODES];        // visiting flag
    vector<int> path;               // visiting history
    //int query[MAX_NODES];
    int query;

    Edge2(int to, int cost) {
        this->to = to; this->cost = cost;
        for (int i = 0; i < N; i++) { this->visited[i] = false; }
        this->path.clear();
        this->query = 0;
    }
    Edge2(int to, int cost, bool visited[], vector<int> path, int query) {
        this->to = to; this->cost = cost;
        for (int i = 0; i < N; i++) { this->visited[i] = visited[i];  }
        for (int i = 0; i < path.size(); i++) { this->path.push_back(path[i]); }
        this->query = query;
    }
    bool operator<(const Edge2& edge) const {
        return (cost < edge.cost) || (cost == edge.cost && to < edge.to);
    }
};

void add(int from, int to, int cost = 0) {
    adj[from].insert({ to, cost });
    //adj[from].push_back({ to, cost });
}

void show_path(const vector<int>& path, int value = 0) {
    if (!path.empty()) {
        printf(">> [%2d]: ", value);
        for (int i = 0; i < path.size() - 1; i++)
            printf("[%d]->", path[i]);
        printf("[%d]\n", path.back());
    }
    else {
        printf(">> No Path!\n");
    }
}

void init_graph() {
    N = 6;
    add(0, 1, 16); add(0, 2, 13);
    add(1, 2, 10); add(1, 3, 12);
    add(2, 1, 4);  add(2, 4, 14);
    add(3, 5, 20);
    add(4, 3, 7);  add(4, 5, 4);
}

void init() {
    for (int i = 0; i < N; i++) {
        visited[i] = false;
        //query[i] = INF;
    }
    path.clear();
}

void dfs(const Edge& cur, int target, int query) {
    //printf(" > res=%2d, cur.cost=%2d, query=%2d\n", res, cur.cost, query);

    if (cur.to == target) {
        res = max(res, query);
        show_path(path, query);
        return;
    }
    for (auto& next : adj[cur.to]) {
        if (!visited[next.to] && res < min(query, next.cost)) {
            visited[next.to] = true; path.push_back(next.to);
            dfs(next, target, min(query, next.cost));
            visited[next.to] = false; path.pop_back();
        }
    }
}

void bfs(int start, int target) {
    for (int i = 0; i < N; i++) { visited[i] = false; }
    path.clear();
    queue<Edge2> Q;

    visited[start] = true; path.push_back(start);
    Q.push({ start, 0, visited, path, INF });

    while (!Q.empty()) {
        auto cur = Q.front(); Q.pop();
        auto& visited = cur.visited;
        auto& path = cur.path;
        auto& query = cur.query;

        if (cur.to == target) {
            res = max(res, query);
            show_path(path, query);
            continue;
        }

        for (auto& next : adj[cur.to]) {
            if (!visited[next.to] && res < min(query, next.cost)) {
                visited[next.to] = true; path.push_back(next.to);
                Q.push({ next.to, next.cost, visited, path, min(query, next.cost) });
                visited[next.to] = false; path.pop_back();
            }
        }
    }
}

void bfs_pq(int start, int target) {
    for (int i = 0; i < N; i++) { visited[i] = false; }
    path.clear();
    priority_queue<Edge2> Q;

    visited[start] = true; path.push_back(start);
    Q.push({ start, 0, visited, path, INF });

    while (!Q.empty()) {
        auto cur = Q.top(); Q.pop();
        auto& visited = cur.visited;
        auto& path = cur.path;
        auto& query = cur.query;

        if (cur.to == target) {
            res = max(res, query);
            show_path(path, query);
            continue;
        }

        for (auto& next : adj[cur.to]) {
            if (!visited[next.to] && res < min(query, next.cost)) {
                visited[next.to] = true; path.push_back(next.to);
                Q.push({ next.to, next.cost, visited, path, min(query, next.cost) });
                visited[next.to] = false; path.pop_back();
            }
        }
    }
}

void bfs_stack(int start, int target) {
    for (int i = 0; i < N; i++) { visited[i] = false; }
    path.clear();
    stack<Edge2> Q;

    visited[start] = true; path.push_back(start);
    Q.push({ start, 0, visited, path, INF });

    while (!Q.empty()) {
        auto cur = Q.top(); Q.pop();
        auto& visited = cur.visited;
        auto& path = cur.path;
        auto& query = cur.query;

        if (cur.to == target) {
            res = max(res, query);
            show_path(path, query);
            continue;
        }

        for (auto& next : adj[cur.to]) {
            if (!visited[next.to] && res < min(query, next.cost)) {
                visited[next.to] = true; path.push_back(next.to);
                Q.push({ next.to, next.cost, visited, path, min(query, next.cost) });
                visited[next.to] = false; path.pop_back();
            }
        }
    }
}

int main()
{
    int start = 0, end = 5;

    init_graph();

    printf("\n*** Backtracking - Recursion\n");
    res = 0;
    init();
    visited[start] = true; path.push_back(start);
    dfs({ start, 0 }, end, INF);
    printf(">> res = %d\n\n", res);

    printf("\n*** Backtracking - Queue\n");
    res = 0;
    bfs(start, end);
    printf(">> res = %d\n\n", res);

    printf("\n*** Backtracking - Prriority Queue\n");
    res = 0;
    bfs_pq(start, end);
    printf(">> res = %d\n\n", res);

    printf("\n*** Backtracking - Stack\n");
    res = 0;
    bfs_stack(start, end);
    printf(">> res = %d\n\n", res);

    return 0;
}
#endif
```
