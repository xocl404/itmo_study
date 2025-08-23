#include <iostream>
#include <vector>

void dfs (int v, std::vector<int>* g, std::vector<int>& s, bool* b) {
    b[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
        if (!b[g[v][i]]) {
            dfs(g[v][i], g, s, b);
        }
    }
    s.push_back(v);
}

int main () {
    int N, M;
    std::cin >> N >> M;
    std::vector<int>* g = new std::vector<int>[N];
    for (int x = 0; x < M; ++x) {
        int i, j;
        std::cin >> i >> j;
        g[i - 1].push_back(j - 1);
    }
    std::vector<int> s;
    bool* b = new bool[N]{};
    for (int i = 0; i < N; ++i) {
        if (!b[i]) {
            dfs(i, g, s, b);
        }
    }
    delete[] g;
    delete[] b;
    int* result = new int[N];
    for (int i = 0; i < N; ++i) {
        result[s[N - 1 - i]] = i + 1;
    }
    for (int i = 0; i < N; ++i) {
        std::cout << result[i] << ' ';
    }

    delete[] result;

    return 0;
}
