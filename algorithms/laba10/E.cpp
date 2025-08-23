#include <iostream>
#include <vector>

void dfs_search_bridge (int v, int parent, std::vector<std::vector<int>>& graph, std::vector<int>& tin,
                        std::vector<int>& ret, int& timer, std::vector<bool>& used) {
    tin[v] = timer;
    ++timer;
    ret[v] = tin[v];
    used[v] = true;
    for (int i = 0; i < graph[v].size(); ++i) {
        if (graph[v][i] == parent || graph[v][i] == -1) {
            continue;
        }
        if (used[graph[v][i]]) {
            ret[v] = std::min (ret[v], tin[graph[v][i]]);
            continue;
        } else {
            dfs_search_bridge (graph[v][i], v, graph, tin, ret, timer, used);
            ret[v] = std::min (ret[v], ret[graph[v][i]]);
        }
        if (ret[graph[v][i]] == tin[graph[v][i]]) {
            for (int j = 0; j < graph[graph[v][i]].size(); ++j) {
                if (graph[graph[v][i]][j] == v) {
                    graph[graph[v][i]][j] = -1;
                    break;
                }
            }
            graph[v][i] = -1;
        }
    }
}

void dfs (int v, const std::vector<std::vector<int>>& graph, std::vector<bool>& used, std::vector<int>& number, int n) {
    number[v] = n;
    used[v] = true;
    for (int i = 0; i < graph[v].size(); ++i) {
        if (graph[v][i] != -1 && !used[graph[v][i]]) {
            dfs (graph[v][i], graph, used, number, n);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M, Q;
    std::cin >> N >> M >> Q;
    std::vector<std::vector<int>> graph(N + 1);
    for (int i = 0; i < M; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    std::vector<int> tin (N + 1);
    std::vector<int> ret (N + 1);
    int timer = 0;
    std::vector<bool> used (N + 1, false);
    dfs_search_bridge (0, -1, graph, tin, ret, timer, used);
    for (int i = 0; i <= N; ++i) {
        used[i] = false;
    }
    std::vector<int> number (N + 1);
    for (int i = 0; i <= N; ++i) {
        if (!used[i]) {
            dfs (i, graph, used, number, i);
        }
    }
    for (int i = 0; i < Q; ++i) {
        int a, b;
        std::cin >> a >> b;
        if (number[a] == number[b]) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
