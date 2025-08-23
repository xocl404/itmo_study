#include <iostream>
#include <vector>

void dfs (int v, int parent, int weight, std::vector<std::pair<int, int>>& parents, std::vector<char>& used,
          const std::vector<std::vector<std::pair<int, int>>>& graph, bool& result, int k) {
    used[v] = 'g';
    parents[v].first = parent;
    parents[v].second = weight;
    for (int i = 0; i < graph[v].size(); ++i) {
        if (!result) {
            used[v] = 'b';
            return;
        }
        if (used[graph[v][i].first] == 'g') {
            int counter = 2;
            int h = weight + graph[v][i].second;
            int p = parent;
            while (p != graph[v][i].first) {
                ++counter;
                h += parents[p].second;
                p = parents[p].first;
            }
            if (h < 0 && counter >= k) {
                result = false;
            }
            used[v] = 'b';
            return;
        }
        if (used[graph[v][i].first] == 'w') {
            dfs(graph[v][i].first, v, graph[v][i].second, parents, used, graph, result, k);
        }
    }
    used[v] = 'b';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, k;
    std::cin >> N >> k;
    for (int i = 0; i < N; ++i) {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::vector<std::pair<int, int>>> graph(n);
        for (int j = 0; j < m; ++j) {
            int u, v, h;
            std::cin >> u >> v >> h;
            graph[u - 1].emplace_back(v - 1, h);
        }
        bool result = true;
        std::vector<char> used(n, 'w');
        std::vector<std::pair<int, int>> parents (n);
        for (int x = 0; x < n; ++x) {
            if (used[x] == 'w') {
                dfs (x, -1, 0, parents, used, graph, result, k);
            }
            if (!result) break;
        }
        if (result) std::cout << "YES\n";
        else std::cout << "NO\n";
    }

    return 0;
}
