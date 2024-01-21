#pragma once

#include <deque>
#include <stack>
#include <queue>
using namespace std;

struct Edge {
    int to, cost;
    bool operator<(const Edge& edge) const { return cost < edge.cost; }
};

template<int max_nodes>
struct GraphWeighted {
    deque<Edge> adj[max_nodes]; // adjacency list
    int N;                      // number of nodes;

    bool visited[max_nodes];
    int parent[max_nodes];
    deque<int> history;

    void init(int num_nodes) { 
        N = num_nodes;
        for (int i = 0; i < N; i++) { adj[i].clear(); }
        clear();
    }
    void clear() { 
        for (int i = 0; i < N; i++) {
            visited[i] = false;
            parent[i] = -1;
        }
        history.clear();
    }
    void addEdge(int from, int to) {
        adj[from].push_back({ to, 0 });
        //adj[to].push_back({ from, 0 });
    }
    void addDirectedEdge(int from, int to, int cost) {
        adj[from].push_back({ to, cost });
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

    void dfs1_recur(int cur) {
        if (!visited[cur]) {
            visited[cur] = true; history.push_back(cur);

            for (auto& next : adj[cur])
                if (!visited[next.to]) {
                    parent[next.to] = cur;
                    dfs1_recur(next.to);
                }
        }
    }
    void dfs1_stack(int start) {
        clear();
        stack<Edge> S;
        S.push({ start, 0 });

        while (!S.empty()) {
            auto cur = S.top(); S.pop();

            if (!visited[cur.to]) {
                visited[cur.to] = true; history.push_back(cur.to);

                for (auto& next : adj[cur.to])
                    if (!visited[next.to]) {
                        parent[next.to] = cur.to;
                        S.push(next);
                    }
            }
        }
    }
    void bfs1_queue(int start) {
        clear();
        queue<Edge> Q;
        Q.push({ start, 0 });

        while (!Q.empty()) {
            auto cur = Q.front(); Q.pop();

            if (!visited[cur.to]) {
                visited[cur.to] = true; history.push_back(cur.to);

                for (auto& next : adj[cur.to])
                    if (!visited[next.to]) {
                        parent[next.to] = cur.to;
                        Q.push(next);
                    }
            }
        }
    }
    void bfs1_pq(int start) {
        clear();
        priority_queue<Edge> Q;
        Q.push({ start, 0 });

        while (!Q.empty()) {
            auto cur = Q.top(); Q.pop();

            if (!visited[cur.to]) {
                visited[cur.to] = true; history.push_back(cur.to);

                for (auto& next : adj[cur.to])
                    if (!visited[next.to]) {
                        parent[next.to] = cur.to;
                        Q.push(next);
                    }
            }
        }
    }

    void dfs2_recur(int cur) {

        for (auto& next : adj[cur])
            if (!visited[next.to]) {
                visited[next.to] = true; history.push_back(next.to);
                parent[next.to] = cur;
                dfs2_recur(next.to);
            }
    }
    void dfs2_stack(int start) {
        clear();
        stack<Edge> S;
        visited[start] = true; history.push_back(start);
        S.push({ start, 0 });

        while (!S.empty()) {
            auto cur = S.top(); S.pop();

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; history.push_back(next.to);
                    parent[next.to] = cur.to;
                    S.push(next);
                }
        }
    }
    void bfs2_queue(int start) {
        clear();
        queue<Edge> Q;
        visited[start] = true; history.push_back(start);
        Q.push({ start, 0 });

        while (!Q.empty()) {
            auto cur = Q.front(); Q.pop();

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; history.push_back(next.to);
                    parent[next.to] = cur.to;
                    Q.push(next);
                }
        }
    }
    void bfs2_pq(int start) {
        clear();
        priority_queue<Edge> Q;
        visited[start] = true; history.push_back(start);
        Q.push({ start, 0 });

        while (!Q.empty()) {
            auto cur = Q.top(); Q.pop();

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; history.push_back(next.to);
                    parent[next.to] = cur.to;
                    Q.push(next);
                }
        }
    }
};
