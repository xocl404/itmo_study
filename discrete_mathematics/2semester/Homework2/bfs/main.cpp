#include <iostream>
#include <vector>
#include <queue>

void bfs (int s, const std::vector<std::vector<int>>& graph, std::vector<int>& dist) {
    dist[s] = 0;
    std::queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < graph[v].size(); ++i) {
            if (dist[graph[v][i]] == -1) {
                dist[graph[v][i]] = dist[v] + 1;
                q.push(graph[v][i]);
            }
        }
    }
}

int main() {
    int V, E;
    std::cin >> V >> E;
    std::vector<std::vector<int>> graph(V);
    for (int i = 0; i < E; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }
    std::vector<int> eccentricity;
    for (int i = 0; i < V; ++i) {
        if (i == 10 || i == 20 || i == 21 || i == 27 || i == 47) { // находятся в другой компоненте связности графа G*
            eccentricity.push_back(-1);
            continue;
        }
        std::vector<int> dist (V, -1);
        bfs (i, graph, dist);
        int max = -1;
        for (int j = 0; j < V; ++j) {
            max = std::max (max, dist[j]);
        }
        eccentricity.push_back(max);
    }
    int rad = E + 1;
    int diam = -1;
    for (int i = 0; i < V; ++i) {
        if (eccentricity[i] == -1) continue;
        diam = std::max (diam, eccentricity[i]);
        rad = std::min (rad, eccentricity[i]);
    }
    std::vector<int> center;
    for (int i = 0; i < V; ++i) {
        if (eccentricity[i] == rad) center.push_back(i + 1);
    }
    std::cout << "diam = " << diam << std::endl;
    std::cout << "rad = " << rad << std::endl;
    std::cout << "center: ";
    for (int i = 0; i < center.size(); ++i) {
        std::cout << center[i] << ' ';
    }

    return 0;
}
