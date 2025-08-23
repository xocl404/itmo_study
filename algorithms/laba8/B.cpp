#include <iostream>
#include <vector>

bool dfs (int v, int key, std::vector<int>* g, bool* b) {
    b[v] = true;
    bool result = false;
    for (int i = 0; i < g[v].size(); ++i) {
        if (g[v][i] == key) {
            result = true;
        } else if (!b[g[v][i]]) {
            result = dfs(g[v][i], key, g, b);
        }
        if (result) {
            break;
        }
    }
    return result;
}

int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<int>* g = new std::vector<int>[n];
    for (int i = 0; i < m; ++i) {
        int start, end;
        std::cin >> start >> end;
        g[start - 1].push_back(end - 1);
    }
    for (int x = 0; x < q; ++x) {
        bool* b1 = new bool[n]{};
        bool* b2 = new bool[n]{};
        int i, j;
        std::cin >> i >> j;
        if (dfs (j - 1, i - 1, g, b1) && dfs (i - 1, j - 1, g, b2)) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
        delete[] b1;
        delete[] b2;
    }


    delete[] g;
    return 0;
}
