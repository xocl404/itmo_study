#include <iostream>
#include <vector>

void dfs (int v, std::vector<int>* graph, bool* used) {
    used[v] = true;
    for (int i = 0; i < graph[v].size(); ++i) {
        if (!used[graph[v][i]]) {
            dfs(graph[v][i], graph, used);
        }
    }
}

int main () {
    int n, m;
    std::cin >> n >> m;
    std::vector<int>* graph = new std::vector<int>[n];
    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        graph[x - 1].push_back(y - 1);
        graph[y - 1].push_back(x - 1);
    }
    if (n != m) {
        std::cout << "EUCLID";
        return 0;
    }
    bool* used = new bool[n]{};
    dfs(0, graph, used);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            std::cout << "EUCLID";
            return 0;
        }
    }
    std::cout << "ARCHIMEDES";

    return 0;
}
