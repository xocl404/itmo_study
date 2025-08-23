#include <iostream>
#include <vector>

void dfs (int v, int p, std::vector<std::vector<int>>& g, std::vector<int>& k, int num) {
    int i = 0;
    for (int to : g[v]) {
        if (to != p && k[to] == 0) {
            ++i;
            dfs (to, v, g, k, num);
        }
    }
    if (!i) k[v] = num;
    if (i == 1 && p == -1) k[v] = num;
}

int main() {
    int N;
    std::cin >> N;
    std::vector<std::vector<int>> g (N);
    for (int i = 0; i < N - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }
    std::vector<int> k (N, 0);
    int num = 0;
    while (true) {
        ++num;
        int v = -1;
        for (int i = 0; i < N; ++i) {
            if (k[i] == 0) {
                v = i;
                break;
            }
        }
        if (v == -1) break;
        dfs(v, -1, g, k, num);
    }
    int mx = 0;
    for (int i = 0; i < N; ++i) {
        mx = std::max (mx, k[i]);
    }
    std::vector<int> c;
    for (int i = 0; i < N; ++i) {
        if (k[i] == mx) c.push_back(i + 1);
    }
    if (c.size() == 1) {
        std::cout << 2 * mx - 2 << '\n';
        std::cout << c[0];
    } else {
        std::cout << 2 * mx - 1 << '\n';
        std::cout << c[0] << ' ' << c[1];
    }

    return 0;
}
