#include <iostream>
#include <vector>

void dfs (int v, std::vector<int>* graph, std::vector<bool>* have, bool* used) {
    used[v] = true;
    for (int i = 0; i < graph[v].size(); ++i) {
        if (!used[graph[v][i]] && have[v][i]) {
            dfs(graph[v][i], graph, have, used);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<int>* graph = new std::vector<int>[n];
    std::vector<bool>* have = new std::vector<bool>[n];
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
        have[a - 1].push_back(true);
        have[b - 1].push_back(true);
    }
    for (int i = 0; i < q; ++i) {
        char c;
        int a, b;
        std::cin >> c >> a >> b;
        if (c == '-') {
            for (int j = 0; j < graph[a - 1].size(); ++j) {
                if (graph[a - 1][j] == b - 1) {
                    have[a - 1][j] = false;
                    break;
                }
            }
            for (int j = 0; j < graph[b - 1].size(); ++j) {
                if (graph[b - 1][j] == a - 1) {
                    have[b - 1][j] = false;
                    break;
                }
            }
        } else {
            bool* used = new bool[n]{};
            dfs(a - 1, graph, have, used);
            if (used[b - 1]) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
            delete[] used;
        }
    }

    return 0;
}
