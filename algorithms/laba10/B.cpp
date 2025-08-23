#include <iostream>
#include <vector>

struct Edge {
    int v;
    int c;
};

void mst (int v, const std::vector<std::vector<Edge>>& graph, std::vector<bool>& used, std::vector<int>& dist, int& result) {
    used[v] = true;
    result += dist[v];
    for (int i = 0; i < graph[v].size(); ++i) {
        if (used[graph[v][i].v]) continue;
        if (dist[graph[v][i].v] == -1 || dist[graph[v][i].v] > graph[v][i].c) {
            dist[graph[v][i].v] = graph[v][i].c;
        }
    }
    int min = -1;
    int index = -1;
    for (int i = 0; i < dist.size(); ++i) {
        if (dist[i] == -1 || used[i]) continue;
        if (min == -1) {
            min = dist[i];
            index = i;
            continue;
        }
        if (min > dist[i]) {
            min = dist[i];
            index = i;
        }
    }
    if (index == -1) return;
    mst (index, graph, used, dist, result);
}

int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<Edge>> graph(N);
    for (int i = 0; i < M; ++i) {
        int A, B, C;
        std::cin >> A >> B >> C;
        graph[A - 1].push_back({B - 1, C});
        graph[B - 1].push_back({A - 1, C});
    }
    std::vector<bool> used(N, false);
    std::vector<int> dist(N, -1);
    int result = 0;
    dist[0] = 0;
    mst (0, graph, used, dist, result);
    std::cout << result;

    return 0;
}
