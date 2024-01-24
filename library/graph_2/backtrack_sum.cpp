#if 0
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;

#define MAX_NODES   100
#define INF         0x7ffffff

// Min Cost Path
struct Edge {
    int to, cost;
    bool operator<(const Edge& edge) const {
        return (cost > edge.cost) || (cost == edge.cost && to > edge.to);
    }
};

set<Edge> adj[MAX_NODES];       // adjacency list (ascending order)
bool visited[MAX_NODES];        // visiting flag
vector<int> path;               // visiting history
int N;                          // number of nodes
int res = INF;                    // optimal solution value (min / max)

struct Edge2 {
    int to, cost;                   // next node, edge cost
    bool visited[MAX_NODES];        // visiting flag
    vector<int> path;               // visiting history
    int query;                      // query for costs of a path (sum/min)

    Edge2(int to, int cost) {
        this->to = to; this->cost = cost; this->query = 0;
        for (int i = 0; i < N; i++) { this->visited[i] = false; }
        this->path.clear();
    }
    Edge2(int to, int cost, int query, bool visited[], vector<int> path) {
        this->to = to; this->cost = cost; this->query = query;
        for (int i = 0; i < N; i++) { this->visited[i] = visited[i]; }
        for (int i = 0; i < path.size(); i++) { this->path.push_back(path[i]); }
    }
    bool operator<(const Edge2& edge) const {
        return (cost < edge.cost) || (cost == edge.cost && to < edge.to);
    }
};

/////////////////////////////////////////////////////////////////////
void add(int from, int to, int cost = 0) {
    adj[from].insert({ to, cost });
}

void show_path(const vector<int>& path, int value = 0) {
    if (!path.empty()) {
        printf(">> [%2d]: ", value);
        for (int i = 0; i < path.size() - 1; i++)
            printf("[%d]->", path[i]);
        printf("[%d]\n", path.back());
    }
    else
        printf(">> No Path!\n");
}

void create_graph() {
    N = 6;
    add(0, 1, 16); add(0, 2, 13);
    add(1, 2, 10); add(1, 3, 12);
    add(2, 1, 4);  add(2, 4, 14);
    add(3, 5, 20);
    add(4, 3, 7);  add(4, 5, 4);
}

void init_graph() {
    for (int i = 0; i < N; i++) { visited[i] = false; }
    path.clear();
}

/*
*** Backtracking - Recursion
>> [48]: [0]->[1]->[3]->[5]
>> [67]: [0]->[1]->[2]->[4]->[3]->[5]
>> [44]: [0]->[1]->[2]->[4]->[5]
>> [54]: [0]->[2]->[4]->[3]->[5]
>> [31]: [0]->[2]->[4]->[5]
>> [49]: [0]->[2]->[1]->[3]->[5]
>> res = 31
*/
void dfs_recur(const Edge& cur, int target, int query) {
    if (cur.to == target) {
        res = min(res, query);
        show_path(path, query);
        return;
    }
    for (auto& next : adj[cur.to])
        if (!visited[next.to]) {
            visited[next.to] = true; path.push_back(next.to);
            dfs_recur(next, target, query + next.cost);
            visited[next.to] = false; path.pop_back();
        }
}

/*
*** Backtracking - Stack
>> [49]: [0]->[2]->[1]->[3]->[5]
>> [31]: [0]->[2]->[4]->[5]
>> [54]: [0]->[2]->[4]->[3]->[5]
>> [44]: [0]->[1]->[2]->[4]->[5]
>> [67]: [0]->[1]->[2]->[4]->[3]->[5]
>> [48]: [0]->[1]->[3]->[5]
>> res = 31
*/
void dfs_stack(int start, int target) {
    init_graph();       // initialize visited & path
    stack<Edge2> S;
    visited[start] = true; path.push_back(start);
    S.push({ start, 0, 0, visited, path });

    while (!S.empty()) {
        auto cur = S.top(); S.pop();
        auto& visited = cur.visited; auto& path = cur.path; 
        int query = cur.query;

        if (cur.to == target) {
            res = min(res, query);
            show_path(path, query);
            continue;
        }
        for (auto& next : adj[cur.to])
            if (!visited[next.to]) {
                visited[next.to] = true; path.push_back(next.to);
                S.push({ next.to, next.cost, query + next.cost, visited, path });
                visited[next.to] = false; path.pop_back();
            }
    }
}

/*
*** Backtracking - Queue
>> [48]: [0]->[1]->[3]->[5]
>> [31]: [0]->[2]->[4]->[5]
>> [44]: [0]->[1]->[2]->[4]->[5]
>> [54]: [0]->[2]->[4]->[3]->[5]
>> [49]: [0]->[2]->[1]->[3]->[5]
>> [67]: [0]->[1]->[2]->[4]->[3]->[5]
>> res = 31
*/
void bfs_queue(int start, int target) {
    init_graph();       // initialize visited & path
    queue<Edge2> Q;
    visited[start] = true; path.push_back(start);
    Q.push({ start, 0, 0, visited, path });

    while (!Q.empty()) {
        auto cur = Q.front(); Q.pop();
        auto& visited = cur.visited; auto& path = cur.path;
        int query = cur.query;

        if (cur.to == target) {
            res = min(res, query);
            show_path(path, query);
            continue;
        }
        for (auto& next : adj[cur.to])
            if (!visited[next.to]) {
                visited[next.to] = true; path.push_back(next.to);
                Q.push({ next.to, next.cost, query + next.cost, visited, path });
                visited[next.to] = false; path.pop_back();
            }
    }
}

/*
*** Backtracking - Prriority Queue
>> [48]: [0]->[1]->[3]->[5]
>> [54]: [0]->[2]->[4]->[3]->[5]
>> [67]: [0]->[1]->[2]->[4]->[3]->[5]
>> [44]: [0]->[1]->[2]->[4]->[5]
>> [31]: [0]->[2]->[4]->[5]
>> [49]: [0]->[2]->[1]->[3]->[5]
>> res = 31
*/
void bfs_pq(int start, int target) {
    init_graph();       // initialize visited & path
    priority_queue<Edge2> Q;
    visited[start] = true; path.push_back(start);
    Q.push({ start, 0, 0, visited, path });

    while (!Q.empty()) {
        auto cur = Q.top(); Q.pop();
        auto& visited = cur.visited; auto& path = cur.path;
        int query = cur.query;

        if (cur.to == target) {
            res = min(res, query);
            show_path(path, query);
            continue;
        }
        for (auto& next : adj[cur.to])
            if (!visited[next.to]) {
                visited[next.to] = true; path.push_back(next.to);
                Q.push({ next.to, next.cost, query + next.cost, visited, path });
                visited[next.to] = false; path.pop_back();
            }
    }
}

int main()
{
    int start = 0, end = 5;

    create_graph();

    printf("\n*** Backtracking - Recursion\n");
    res = INF;
    init_graph();
    visited[start] = true; path.push_back(start);
    dfs_recur({ start, 0 }, end, 0);
    printf(">> res = %d\n", res);

    printf("\n*** Backtracking - Stack\n");
    res = INF;
    dfs_stack(start, end);
    printf(">> res = %d\n", res);

    printf("\n*** Backtracking - Queue\n");
    res = INF;
    bfs_queue(start, end);
    printf(">> res = %d\n", res);

    printf("\n*** Backtracking - Prriority Queue\n");
    res = INF;
    bfs_pq(start, end);
    printf(">> res = %d\n", res);

    return 0;
}
#endif