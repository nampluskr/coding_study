#if 0
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <queue>
using namespace std;

const int MAX = 4010;
const int _N = 1010;
const int INF = 987654321;

struct Edge
{
    int cost, to;
    const bool operator<(const Edge& edge)const {
        return cost < edge.cost;
    }
};

vector<Edge> adj[MAX];
int minVal;

void init(int N, int K, int sCity[], int eCity[], int mLimit[])
{
    for (int i = 0; i < MAX; i++) adj[i].clear();

    for (int i = 0; i < K; i++)
        adj[sCity[i]].push_back({ mLimit[i],eCity[i] });
}

void add(int sCity, int eCity, int mLimit)
{
    adj[sCity].push_back({ mLimit, eCity });
}

int calculate(int sCity, int eCity)
{
    int visited[_N] = {};
    minVal = INF;
    priority_queue<Edge> pq; pq.push({ 0,sCity });

    while (pq.size()) {
        auto cur = pq.top(); pq.pop();
        visited[cur.to] = 1;
        if (minVal > cur.cost && cur.to != sCity) minVal = cur.cost;
        if (visited[eCity]) return minVal;
        for (auto m : adj[cur.to]) if (!visited[m.to]) pq.push(m);
    }
    return -1;
}
#endif