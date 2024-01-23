#pragma once

#include <vector>
#include <stack>
#include <queue>
#include <set>
#include "func.h"
using namespace std;

#ifndef MAX_NODES
#define MAX_NODES   100
#endif

#define INF 0x7fffffff


struct Edge {
    int to, cost;
    bool operator<(const Edge& edge) const { 
        return (cost < edge.cost) || (cost == edge.cost && to < edge.to); }
};

struct Edge2 {
    int to, cost;
    bool visited[MAX_NODES];
    vector<int> path;

    Edge2(int to, int cost) { 
        this->to = to; this->cost = cost;
        for (int i = 0; i < MAX_NODES; i++) { this->visited[i] = false; }
        path.clear();
    }
    Edge2(int to, int cost, const bool visited[], const vector<int> path) { 
        this->to = to; this->cost = cost;
        for (int i = 0; i < MAX_NODES; i++) { this->visited[i] = visited[i]; }
        for (int i = 0; i < path.size(); i++) { this->path.push_back(path[i]); }
    }
    bool operator<(const Edge2& edge) const {
        return (cost < edge.cost) || (cost == edge.cost && to < edge.to);
    }
};

struct GraphTreversal {
    set<Edge> adj[MAX_NODES];   // adjacency list (우선순위 오른차순)
    bool visited[MAX_NODES];
    int parent[MAX_NODES];
    vector<int> path;
    int N;                      // number of nodes;

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
        path.clear();
    }
    void add(int from, int to, int cost = 0) {
        adj[from].insert({ to, cost });
    }
    void trace(int start, int end) {
        if (parent[end] == -1) { return; }
        if (end == start) { path.push_back(end); }
        trace(start, parent[end]);
        path.push_back(end);
    }
    void show_path(int start, int end) {
        path.clear();
        path.push_back(start);
        trace(start, end);
        print_list(path);
    }

    void dfs1_recur(int cur) {
        if (!visited[cur]) {
            visited[cur] = true; path.push_back(cur);

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
                visited[cur.to] = true; path.push_back(cur.to);

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
                visited[cur.to] = true; path.push_back(cur.to);

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
                visited[cur.to] = true; path.push_back(cur.to);

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
                visited[next.to] = true; path.push_back(next.to);
                parent[next.to] = cur;
                dfs2_recur(next.to);
            }
    }
    void dfs2_stack(int start) {
        clear();
        stack<Edge> S;
        visited[start] = true; path.push_back(start);
        S.push({ start, 0 });

        while (!S.empty()) {
            auto cur = S.top(); S.pop();

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; path.push_back(next.to);
                    parent[next.to] = cur.to;
                    S.push(next);
                }
        }
    }
    void bfs2_queue(int start) {
        clear();
        queue<Edge> Q;
        visited[start] = true; path.push_back(start);
        Q.push({ start, 0 });

        while (!Q.empty()) {
            auto cur = Q.front(); Q.pop();

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; path.push_back(next.to);
                    parent[next.to] = cur.to;
                    Q.push(next);
                }
        }
    }
    void bfs2_pq(int start) {
        clear();
        priority_queue<Edge> Q;
        visited[start] = true; path.push_back(start);
        Q.push({ start, 0 });

        while (!Q.empty()) {
            auto cur = Q.top(); Q.pop();

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; path.push_back(next.to);
                    parent[next.to] = cur.to;
                    Q.push(next);
                }
        }
    }
};


struct GraphFindAPath{
    set<Edge> adj[MAX_NODES];   // adjacency list
    bool visited[MAX_NODES];
    int parent[MAX_NODES];
    vector<int> path;
    int N;                      // number of nodes;

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
        path.clear();
    }
    void add(int from, int to, int cost = 0) {
        adj[from].insert({ to, cost });
    }
    void trace(int start, int end) {
        if (parent[end] == -1) { return; }
        if (end == start) { path.push_back(end); }
        trace(start, parent[end]);
        path.push_back(end);
    }
    void show_path(int start, int end) {
        path.clear();
        trace(start, end);
        print_list(path);
    }

    bool dfs1_recur(int cur, int target) {
        if (!visited[cur]) {
            visited[cur] = true; path.push_back(cur);

            if (cur == target) return true;

            for (auto& next : adj[cur])
                if (!visited[next.to]) {
                    parent[next.to] = cur;
                    if (dfs1_recur(next.to, target) == true)
                        return true;
                }
            return false;
        }
    }
    bool dfs1_stack(int start, int target) {
        clear();
        stack<Edge> S;
        S.push({ start, 0 });

        while (!S.empty()) {
            auto cur = S.top(); S.pop();

            if (!visited[cur.to]) {
                visited[cur.to] = true; path.push_back(cur.to);

                if (cur.to == target) return true;

                for (auto& next : adj[cur.to])
                    if (!visited[next.to]) {
                        parent[next.to] = cur.to;
                        S.push(next);
                    }
            }
        }
        return false;
    }
    bool bfs1_queue(int start, int target) {
        clear();
        queue<Edge> Q;
        Q.push({ start, 0 });

        while (!Q.empty()) {
            auto cur = Q.front(); Q.pop();

            if (!visited[cur.to]) {
                visited[cur.to] = true; path.push_back(cur.to);

                if (cur.to == target) return true;

                for (auto& next : adj[cur.to])
                    if (!visited[next.to]) {
                        parent[next.to] = cur.to;
                        Q.push(next);
                    }
            }
        }
        return false;
    }
    bool bfs1_pq(int start, int target) {
        clear();
        priority_queue<Edge> Q;
        Q.push({ start, 0 });

        while (!Q.empty()) {
            auto cur = Q.top(); Q.pop();

            if (!visited[cur.to]) {
                visited[cur.to] = true; path.push_back(cur.to);

                if (cur.to == target) return true;

                for (auto& next : adj[cur.to])
                    if (!visited[next.to]) {
                        parent[next.to] = cur.to;
                        Q.push(next);
                    }
            }
        }
        return false;
    }

    bool dfs2_recur(int cur, int target) {
        if (cur == target) return true;

        for (auto& next : adj[cur])
            if (!visited[next.to]) {
                visited[next.to] = true; path.push_back(next.to);
                parent[next.to] = cur;
                if (dfs2_recur(next.to, target) == true)
                    return true;
            }
        return false;
    }
    bool dfs2_stack(int start, int target) {
        clear();
        stack<Edge> S;
        visited[start] = true; path.push_back(start);
        S.push({ start, 0 });

        while (!S.empty()) {
            auto cur = S.top(); S.pop();

            if (cur.to == target) return true;

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; path.push_back(next.to);
                    parent[next.to] = cur.to;
                    S.push(next);
                }
        }
        return false;
    }
    bool bfs2_queue(int start, int target) {
        clear();
        queue<Edge> Q;
        visited[start] = true; path.push_back(start);
        Q.push({ start, 0 });

        while (!Q.empty()) {
            auto cur = Q.front(); Q.pop();

            if (cur.to == target) return true;

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; path.push_back(next.to);
                    parent[next.to] = cur.to;
                    Q.push(next);
                }
        }
        return false;
    }
    bool bfs2_pq(int start, int target) {
        clear();
        priority_queue<Edge> Q;
        visited[start] = true; path.push_back(start);
        Q.push({ start, 0 });

        while (!Q.empty()) {
            auto cur = Q.top(); Q.pop();

            if (cur.to == target) return true;

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; path.push_back(next.to);
                    parent[next.to] = cur.to;
                    Q.push(next);
                }
        }
        return false;
    }
};

// Backtracking
struct GraphFindAllPaths {
    set<Edge> adj[MAX_NODES];   // adjacency list
    bool visited[MAX_NODES];
    vector<int> path;
    int N;                      // number of nodes;

    void init(int num_nodes) {
        N = num_nodes;
        for (int i = 0; i < N; i++) { adj[i].clear(); }
        clear();
    }
    void clear() {
        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }
        path.clear();
    }
    void add(int from, int to, int cost = 0) {
        adj[from].insert({ to, cost });
    }

    void dfs_recur(int cur, int target) {
        if (cur == target) {
            print_list(path);
            return;
        }
        for (auto& next : adj[cur])
            if (!visited[next.to]) {
                visited[next.to] = true; path.push_back(next.to);
                dfs_recur(next.to, target);
                visited[next.to] = false; path.pop_back();
            }
    }
    void dfs_stack(int start, int target) {
        clear();
        stack<Edge2> S;
        visited[start] = true; path.push_back(start);
        S.push({ start, 0, visited, path });

        while (!S.empty()) {
            auto cur = S.top(); S.pop();
            auto& visited = cur.visited;
            auto& path = cur.path;

            if (cur.to == target) {
                print_list(path);
                continue;
            }

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; path.push_back(next.to);
                    S.push({ next.to, next.cost, visited, path });
                    visited[next.to] = false; path.pop_back();
                }
        }
    }
    void bfs_queue(int start, int target) {
        clear();
        queue<Edge2> Q;
        visited[start] = true; path.push_back(start);
        Q.push({ start, 0, visited, path });

        while (!Q.empty()) {
            auto cur = Q.front(); Q.pop();
            auto& visited = cur.visited;
            auto& path = cur.path;

            if (cur.to == target) {
                print_list(path);
                continue;
            }

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; path.push_back(next.to);
                    Q.push({ next.to, next.cost, visited, path });
                    visited[next.to] = false; path.pop_back();
                }
        }
    }
    void bfs_pq(int start, int target) {
        clear();
        priority_queue<Edge2> Q;
        visited[start] = true; path.push_back(start);
        Q.push({ start, 0, visited, path });

        while (!Q.empty()) {
            auto cur = Q.top(); Q.pop();
            auto& visited = cur.visited;
            auto& path = cur.path;

            if (cur.to == target) {
                print_list(path);
                continue;
            }

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; path.push_back(next.to);
                    Q.push({ next.to, next.cost, visited, path });
                    visited[next.to] = false; path.pop_back();
                }
        }
    }
};

// Backtracking
struct GraphMaxCostPath {
    set<Edge> adj[MAX_NODES];   // adjacency list
    bool visited[MAX_NODES];
    vector<int> path;
    int N;                      // number of nodes;
    int res;                    // min cost value of a path

    void init(int num_nodes) {
        N = num_nodes;
        for (int i = 0; i < N; i++) { adj[i].clear(); }
        clear();
    }
    void clear() {
        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }
        path.clear();
        res = INF;
    }
    void add(int from, int to, int cost = 0) {
        adj[from].insert({ to, cost });
    }

    void dfs_recur(int cur, int cost, int target) {
        res = min(res, cost);
        if (cur == target) {
            print_list(path);
            printf("* Min Cost = %d\n", res);
            res = INF;
            return;
        }
        for (auto& next : adj[cur])
            if (!visited[next.to] && res < next.cost) {
                visited[next.to] = true; path.push_back(next.to);
                dfs_recur(next.to, next.cost, target);
                visited[next.to] = false; path.pop_back();
            }
    }
    void dfs_stack(int start, int target) {
        clear();
        stack<Edge2> S;
        visited[start] = true; path.push_back(start);
        S.push({ start, 0, visited, path });

        while (!S.empty()) {
            auto cur = S.top(); S.pop();
            auto& visited = cur.visited;
            auto& path = cur.path;

            if (res > cur.cost && cur.to != start)
                res = cur.cost;
            if (cur.to == target) {
                print_list(path);
                printf("* Min Cost = %d\n", res);
                res = INF;
                continue;
            }

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; path.push_back(next.to);
                    S.push({ next.to, next.cost, visited, path });
                    visited[next.to] = false; path.pop_back();
                }
        }
    }
    void bfs_queue(int start, int target) {
        clear();
        queue<Edge2> Q;
        visited[start] = true; path.push_back(start);
        Q.push({ start, 0, visited, path });

        while (!Q.empty()) {
            auto cur = Q.front(); Q.pop();
            auto& visited = cur.visited;
            auto& path = cur.path;

            if (cur.to == target) {
                print_list(path);
                continue;
            }

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; path.push_back(next.to);
                    Q.push({ next.to, next.cost, visited, path });
                    visited[next.to] = false; path.pop_back();
                }
        }
    }
    void bfs_pq(int start, int target) {
        clear();
        priority_queue<Edge2> Q;
        visited[start] = true; path.push_back(start);
        Q.push({ start, 0, visited, path });

        while (!Q.empty()) {
            auto cur = Q.top(); Q.pop();
            auto& visited = cur.visited;
            auto& path = cur.path;

            if (cur.to == target) {
                print_list(path);
                continue;
            }

            for (auto& next : adj[cur.to])
                if (!visited[next.to]) {
                    visited[next.to] = true; path.push_back(next.to);
                    Q.push({ next.to, next.cost, visited, path });
                    visited[next.to] = false; path.pop_back();
                }
        }
    }
};