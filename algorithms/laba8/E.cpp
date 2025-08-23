#include <iostream>
#include <vector>

void dfs (int v, int parent, char* c, std::vector<int>* g, bool& result) {
    c[v] = 'g';
    for (int i = 0; i < g[v].size(); ++i) {
        if (result) {
            return;
        }
        if (c[g[v][i]] == 'g' && g[v][i] != parent) {
            result = true;
            return;
        }
        if (c[g[v][i]] == 'w') {
            dfs(g[v][i], v, c, g, result);
        }
    }
    c[v] = 'b';
}

int main () {
    int n, m;
    std::cin >> n >> m;
    std::vector<int>* g = new std::vector<int>[n];
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    char* c = new char[n];
    for (int i = 0; i < n; ++i) {
        c[i] = 'w';
    }
    bool result = false;
    for (int i = 0; i < n; ++i) {
        if (c[i] == 'w') {
            dfs(i, -1, c, g, result);
        }
        if (result) {
            break;
        }
    }
    if (result) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    delete[] c;
    delete[] g;
    return 0;
}
