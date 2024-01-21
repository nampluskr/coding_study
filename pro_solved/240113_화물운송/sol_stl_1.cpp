#if 1
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <deque>
#include <queue>
#include <stack>
using namespace std;

#define MAX_NODES   1000    // 0부터 N-1까지 ID값을 가진다.
#define MAX_EDGES   4000 
#define INF         30001   // 최대 중량 ( 1 ≤ mLimit[i] ≤ 30,000 )

struct Edge {
    int to, cost;
    const bool operator<(const Edge& edge) const { return cost < edge.cost; }
};

deque<Edge> adj[MAX_NODES];
bool visited[MAX_NODES];
int parent[MAX_NODES];
deque<int> history;

int N;      // number of nodes
int K;      // number of edges

void init(int _N, int _K, int sCity[], int eCity[], int mLimit[])
{
    N = _N;
    for (int i = 0; i < N; i++) adj[i].clear();

    K = _K;
    for (int i = 0; i < K; i++)
        adj[sCity[i]].push_back({ eCity[i], mLimit[i] });
}

void add(int sCity, int eCity, int mLimit)
{
    adj[sCity].push_back({ eCity, mLimit });
}


/////////////////////////////////////////////////////////////////////
void init() {
    for (int i = 0; i < N; i++) {
        visited[i] = false;
        parent[i] = -1;
    }
    history.clear();
}

void bfs(int start, int end) {
    init();
    queue<Edge> Q;
    Q.push({ start, 0 });   // { to, cost }
    visited[start] = true; history.push_back(start);

    int res = -INF;
    while (!Q.empty()) {
        auto cur = Q.front(); Q.pop();

        if (cur.to == end) break;

        for (auto& next : adj[cur.to])
            if (!visited[next.to]) {
                visited[next.to] = true; history.push_back(next.to);
                parent[next.to] = cur.to;
                Q.push(next);
            }
    }
}

void bfs_pq(int start, int end) {
    init();
    priority_queue<Edge> Q;
    Q.push({ start, 0 });   // { to, cost }
    visited[start] = true; history.push_back(start);

    int res = INF;
    while (!Q.empty()) {
        auto cur = Q.top(); Q.pop();

        if (cur.to == end) break;

        for (auto& next : adj[cur.to])
            if (!visited[next.to]) {
                visited[next.to] = true; history.push_back(next.to);
                parent[next.to] = cur.to;
                Q.push(next);
            }
    }
}

bool dfs(int cur, int end) {
    if (!visited[cur]) {
        visited[cur] = true; history.push_back(cur);
        
        if (cur == end) return true;
    }
    for (auto& next: adj[cur])
        if (!visited[next.to]) {
            parent[next.to] = cur;
            if (dfs(next.to, end) == true) return true;
        }
    return false;
}

void dfs_stack(int start, int end) {
    init();
    stack<Edge> S;
    S.push({ start, 0 });

    while (!S.empty()) {
        auto cur = S.top(); S.pop();

        if (!visited[cur.to]) {
            visited[cur.to] = true; history.push_back(cur.to);

            if (cur.to == end) break;

            for (auto& next: adj[cur.to])
                if (!visited[next.to]) {
                    parent[next.to] = cur.to;
                    S.push(next);
                }
        }
    }
}

void dfs_queue(int start, int end) {
    init();
    queue<Edge> Q;
    Q.push({ start, 0 });

    while (!Q.empty()) {
        auto cur = Q.front(); Q.pop();

        if (!visited[cur.to]) {
            visited[cur.to] = true; history.push_back(cur.to);

            if (cur.to == end) break;

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    parent[next.to] = cur.to;
                    Q.push(next);
                }
        }
    }
}

void dfs_pq(int start, int end) {
    init();
    priority_queue<Edge> Q;
    Q.push({ start, 0 });

    while (!Q.empty()) {
        auto cur = Q.top(); Q.pop();

        if (!visited[cur.to]) {
            visited[cur.to] = true; history.push_back(cur.to);

            if (cur.to == end) break;

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    parent[next.to] = cur.to;
                    Q.push(next);
                }
        }
    }
}


void show_history() {
    printf(">> ");
    if (!history.empty()) {
        for (int i = 0; i < history.size() - 1; i++)
            printf("[%d]->", history[i]);
        printf("[%d]\n", history.back());
    }
}

void show_path(int start, int end) {
    deque<int> path;
    if (parent[end] == -1) {
        printf(">> No path!\n");
        return;
    }
    for (int node = end; node != start; node = parent[node])
        path.push_front(node);

    printf(">> ");
    path.push_front(start);
    for (int node : path)
        if (node != end)
            printf("[%d]->", node);
    printf("[%d]\n", end);
}


/////////////////////////////////////////////////////////////////////

int calculate(int sCity, int eCity)
{
    printf("\n Start[%d] -> End[%d]\n", sCity, eCity);
    if (sCity == 0 && eCity == 4)
        int k = 0;

    //bfs_pq(sCity, eCity);
    //bfs(sCity, eCity);
    //init(); dfs(sCity, eCity);
    //dfs_stack(sCity, eCity);
    //dfs_queue(sCity, eCity);

    dfs_pq(sCity, eCity);

    show_history();
    return 0;
}
#endif