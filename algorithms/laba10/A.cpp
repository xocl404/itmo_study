#include <iostream>
#include <vector>

void dfs (int v, int p, std::vector<int>& parent, const std::vector<std::vector<int>>& graph) {
    parent[v] = p;
    for (int i = 0; i < graph[v].size(); ++i) {
        if (graph[v][i] != p) {
            dfs (graph[v][i], v, parent, graph);
        }
    }
}

int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n);
    std::vector<int> degree (n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
        ++degree[u - 1];
        ++degree[v - 1];
    }
    std::vector<int> ans (n - 2);
    std::vector<int> parent (n);
    dfs(n - 1, -1, parent, graph);

    int min;
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 1) {
            min = i;
            break;
        }
    }
    int leaf = min;
    for (int i = 0; i < n - 2; ++i) {
        int next = parent[leaf];
        ans[i] = next + 1;
        --degree[next];
        if (degree[next] == 1 && next < min) {
            leaf = next;
        } else {
            do {
                ++min;
            }
            while (degree[min] != 1);
            leaf = min;
        }
    }
    
    for (int i = 0; i < n - 2; ++i) {
        std::cout << ans[i] << ' ';
    }

    return 0;
}
