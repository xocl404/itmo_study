#include <iostream>
#include <vector>
#include <set>

void dfs (int v, int parent, const std::vector<std::vector<int>>& graph, std::vector<int>& tin, std::vector<int>& ret,
          std::set<std::pair<int, int>>& result, int& timer, std::vector<bool>& used) {
    tin[v] = timer;
    ++timer;
    ret[v] = tin[v];
    used[v] = true;
    for (int i = 0; i < graph[v].size(); ++i) {
        if (graph[v][i] == parent) {
            continue;
        }
        if (used[graph[v][i]]) {
            ret[v] = std::min (ret[v], tin[graph[v][i]]);
            continue;
        } else {
            dfs (graph[v][i], v, graph, tin, ret, result, timer, used);
            ret[v] = std::min (ret[v], ret[graph[v][i]]);
        }
        if (ret[graph[v][i]] == tin[graph[v][i]]) {
            result.insert({std::min(v, graph[v][i])  + 1, std::max(v, graph[v][i]) + 1});
        }
    }

}

int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> graph (N);
    for (int i = 0; i < M; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x;
        --y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    std::vector<int> tin (N);
    std::vector<int> ret (N);
    std::set<std::pair<int, int>> result;
    std::vector<bool> used (N, false);
    int timer = 0;
    for (int i = 0; i < N; ++i) {
        if (!used[i]) {
            dfs(i, -1, graph, tin, ret, result, timer, used);
        }
    }
    for (auto& i : result) {
        std::cout << i.first << ' ' << i.second << '\n';
    }

    return 0;
}
