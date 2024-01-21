#if 0
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <queue>
using namespace std;

#define MAX_NODES   1000    // 0부터 N-1까지 ID값을 가진다.
#define MAX_EDGES   4000 
#define INF         30001   // 최대 중량 ( 1 ≤ mLimit[i] ≤ 30,000 )

struct Edge {
    int to, cost;
    const bool operator<(const Edge& edge) const { return cost < edge.cost; }
};

vector<Edge> adj[MAX_NODES];
bool visited[MAX_NODES];
int parent[MAX_NODES];
vector<int> history;

int N;      // number of nodes
int K;      // number of edges

/////////////////////////////////////////////////////////////////////
void show_history() {
    printf(">> ");
    if (!history.empty()) {
        for (int i = 0; i < history.size() - 1; i++)
            printf("[%d]->", history[i]);
        printf("[%d]\n", history.back());
    }
}

void init() {
    for (int i = 0; i < N; i++) {
        visited[i] = false;
        parent[i] = -1;
    }
    history.clear();
}

/////////////////////////////////////////////////////////////////////

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

int calculate(int sCity, int eCity)
{
    priority_queue<Edge> Q;
    init();
    
    printf("\n*** start [%d] -> end [%d]\n", sCity, eCity);
    Q.push({ sCity, 0 });
    int res = INF;
    Edge cur = { sCity, 0 };

    while (!Q.empty()) {
        cur = Q.top(); Q.pop();

        visited[cur.to] = true; history.push_back(cur.to);

        if (res > cur.cost && cur.to != sCity)
            res = cur.cost;

        if (cur.to == eCity) break;

        for (auto& next : adj[cur.to]) 
            if (!visited[next.to]) {
                Q.push(next);
            }
    }
    if (cur.to != eCity) res = -1;;

    show_history();

    return res;
}
#endif