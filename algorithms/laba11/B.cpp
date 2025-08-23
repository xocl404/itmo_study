#include "blazingio.hpp"
#include <vector>
#include <queue>

int bfs (int s, std::vector<std::vector<int>>& graph, std::vector<int>& dist, int n) {
    std::queue<int> q;
    std::vector<int> parent(dist.size(), -1);
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < n; ++i) {
            if (graph[v][i] && dist[i] == -1) {
                parent[i] = v;
                dist[i] = dist[v] + 1;
                q.push(i);
            }
        }
    }
    if (dist[n - 1] == -1) {
        return 0;
    }
    int res = 101;
    int p = n - 1;
    while (p != 0) {
        res = std::min (res, graph[parent[p]][p]);
        p = parent[p];
    }
    p = n - 1;
    while (p != 0) {
        graph[parent[p]][p] -= res;
        graph[p][parent[p]] += res;
        p = parent[p];
    }

    return res;
};

int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> graph (N);
    for (int i = 0; i < N; ++i) {
        graph[i].resize(N, 0);
    }
    for (int i = 0; i < M; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        graph[u - 1][v - 1] = c;
    }
    int f = 0;
    int d;
    do {
        std::vector<int> dist(N, -1);
        f += bfs(0, graph, dist, N);
        d = dist[N - 1];
    }
    while (d != -1);
    std::cout << f;

    return 0;
}
