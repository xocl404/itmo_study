#include <iostream>
#include <vector>
#include <set>

void dfs (int v, std::vector<int>* graph, bool* used, std::vector<int>& result) {
    used[v] = true;
    for (int i = 0; i < graph[v].size(); ++i) {
        if (!used[graph[v][i]]) {
            dfs(graph[v][i], graph, used, result);
        }
    }
    result.push_back(v);
}

void dfsR (int v, std::vector<int>* graph, bool* used, std::vector<int>& condensation, int* g) {
    used[v] = true;
    condensation[condensation.size() - 1] = std::min (condensation[condensation.size() - 1], v);
    g[v] = condensation.size() - 1;
    for (int i = 0; i < graph[v].size(); ++i) {
        if (!used[graph[v][i]]) {
            dfsR(graph[v][i], graph, used, condensation, g);
        }
    }

}

int main () {
    int N, M;
    std::cin >> N >> M;
    std::vector<int>* graph = new std::vector<int>[N];
    std::vector<int>* reverse_graph = new std::vector<int>[N];
    for (int i = 0; i < M; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        reverse_graph[b - 1].push_back(a - 1);
    }

    std::vector<int> result;
    bool* used = new bool[N]{};
    for (int i = 0; i < N; ++i) {
        if (!used[i]) {
            dfs(i, graph, used, result);
        }
    }

    for (int i = 0; i < N; ++i) {
        used[i] = false;
    }
    int* g = new int[N];
    std::vector<int> condensation;
    for (int i = N - 1; i >= 0; --i) {
        if (!used[result[i]]) {
            condensation.push_back(result[i]);
            dfsR(result[i], reverse_graph, used, condensation, g);
        }
    }
    std::set<std::pair<int, int>> answer;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            if (g[i] != g[graph[i][j]]) {
                answer.insert({condensation[g[i]] + 1, condensation[g[graph[i][j]]] + 1});
            }
        }
    }
    std::cout << condensation.size() << ' ' << answer.size() << '\n';
    for (auto i : answer) {
        std::cout << i.first << ' ' << i.second << '\n';
    }

    return 0;
}
