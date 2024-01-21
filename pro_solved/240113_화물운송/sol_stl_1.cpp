#include <vector>
#include <queue>
#include <list>
using namespace std;

#define MAX_N	1000	// 0부터 N-1까지 ID값을 가진다.
#define MAX_ROADS	4000	// 
#define INF			30001	// 최대 중량 ( 1 ≤ mLimit[i] ≤ 30,000 )

int N;	// 노드의 개수
int K;	// 간선의 개수

vector<int> roads[MAX_N];
int limit[MAX_N][MAX_N];
int flow[MAX_N][MAX_N];

int parent[MAX_N];
bool visited[MAX_N];

/////////////////////////////////////////////////////////////////////
void bfs(int start, int end) {
    queue<int> Q;
    visited[start] = true; parent[start] = -1;
    Q.push(start);

    while (!Q.empty()) {
        int cur = Q.front(); Q.pop();
        if (cur == end) break;

        for (int next : roads[cur])
            if (!visited[next] && limit[cur][next] - flow[cur][next] > 0) {
                visited[next] = true; parent[next] = cur;
                Q.push(next);
            }
    }
}

void show_path(int start, int end) {
    if (parent[end] == -1) { printf(">> No path\n"); return; }
    list<int> path;
    for (int i = end; i != start; i = parent[i]) { path.push_front(i); }
    path.push_front(start);
    printf(">> ");
    //for (int i = 0; i) { printf("[%d]->", i); }
    printf("\n");
}

/////////////////////////////////////////////////////////////////////
void init(int _N, int _K, int sCity[], int eCity[], int mLimit[])
{
    N = _N;
    K = _K;
    for (int i = 0; i < N; i++) { 
        roads[i].clear();
        for (int j = 0; j < N; j++)
            limit[i][j] = 0;
    }
    for (int i = 0; i < K; i++) {
        roads[sCity[i]].push_back(eCity[i]);
        limit[sCity[i]][eCity[i]] = mLimit[i];
    }
}

void add(int sCity, int eCity, int mLimit)
{
    roads[sCity].push_back(eCity);
    limit[sCity][eCity] = mLimit;
}

int calculate(int sCity, int eCity)
{
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++)
            flow[i][j] = 0;

    int res = 0;
    while (true) {
        for (int i = 0; i < N; i++) {
            visited[i] = false;
            parent[i] = -1;
        }
        bfs(sCity, eCity);                 // get path to end
        show_path(sCity, eCity);
        if (parent[eCity] == -1) break;    // no path to end

        int minFlow = INF;
        for (int i = eCity; i != sCity; i = parent[i]) {
            minFlow = min(minFlow, limit[parent[i]][i] - flow[parent[i]][i]);
            flow[parent[i]][i] += minFlow;
            flow[i][parent[i]] -= minFlow;
        }
        res += minFlow;
    }
    if (res == 0) { res = -1; }
    return res;
}