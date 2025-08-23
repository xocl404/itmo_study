#include <iostream>
#include <vector>

void Euler (int v, std::vector<std::vector<int>>& graph, std::vector<int>& result) {
    for (int i = 0; i < graph[v].size(); ++i) {
        if (graph[v][i] == -1) continue;
        int u = graph[v][i];
        graph[v][i] = -1;
        for (int j = 0; j < graph[u].size(); ++j) {
            if (graph[u][j] == v) {
                graph[u][j] = -1;
                break;
            }
        }
        Euler (u, graph, result);
    }
    result.push_back(v + 1);
}

int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> graph (N);
    for (int i = 0; i < M; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);

    }
    for (int i = 0; i < N; ++i) {
        if (graph[i].size() % 2) {
            std::cout << ":(";
            return 0;
        }
    }
    std::vector<int> result;
    Euler (0, graph, result);
    if (result.size() != M + 1) {
        std::cout << ":(";
        return 0;
    }
    for (int i = M; i >= 0; --i) {
        std::cout << result[i] << ' ';
    }

    return 0;
}
