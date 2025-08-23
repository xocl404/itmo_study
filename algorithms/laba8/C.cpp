#include <iostream>
#include <vector>

void dfs (int v, std::vector<int>* g, bool* b) {
    b[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
        if (!b[g[v][i]]) {
            dfs(g[v][i], g, b);
        }
    }
}

int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<int>* g = new std::vector<int>[N];
    for (int x = 0; x < M; ++x) {
        int i, j;
        std::cin >> i >> j;
        g[i - 1].push_back(j - 1);
        g[j - 1].push_back(i - 1);
    }

    bool* b = new bool[N]{};
    int counter = 0;
    for (int i = 0; i < N; ++i) {
        if(!b[i]) {
            ++counter;
            dfs(i, g, b);
        }
    }

    std::cout << counter;
    delete[] b;
    delete[] g;

    return 0;
}
