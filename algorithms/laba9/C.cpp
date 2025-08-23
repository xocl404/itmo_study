#include <iostream>
#include <vector>

struct Edge {
    int v;
    int t;
};

int SearchVertex (const std::vector<int>& dist, const std::vector<bool>& used) {
    int min = -1;
    int res = -1;
    for (int i = 0; i < dist.size(); ++i) {
        if (dist[i] == -1 || used[i]) continue;
        if (min == -1 || min > dist[i]) {
            min = dist[i];
            res = i;
        }
    }
    return res;
}

void Dijkstra (int s, const std::vector<std::vector<Edge>>& graph, std::vector<bool>& used, std::vector<int>& dist) {
    dist[s]= 0;
    int v = SearchVertex(dist, used);
    while (v != -1) {
        used[v] = true;
        for (int i = 0; i < graph[v].size(); ++i) {
            if (dist[graph[v][i].v] == -1 || dist[graph[v][i].v] > dist[v] + graph[v][i].t) {
                dist[graph[v][i].v] = dist[v] + graph[v][i].t;
            }
        }
        v = SearchVertex(dist, used);
    }
}

int main () {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<Edge>> graph(n);
    for (int i = 0; i < m; ++i) {
        int a, b, t;
        std::cin >> a >> b >> t;
        graph[a - 1].push_back({b - 1, t});
    }
    std::vector<bool> used (n, false);
    std::vector<int> dist (n, -1);
    Dijkstra (0, graph, used, dist);
    std::cout << dist[n - 1];

    return 0;
}
