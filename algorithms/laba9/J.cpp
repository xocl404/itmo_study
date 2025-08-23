#include <iostream>
#include <vector>

void dfs (int v, std::vector<bool>& used, const std::vector<std::vector<int>>& graph, std::vector<int>& k, int counter, const std::vector<int>& size) {
    used[v] = true;
    k[v] = counter;
    for (int i = 0; i < size[v]; ++i) {
        if (!used[graph[v][i]]) {
            dfs (graph[v][i], used, graph, k, counter, size);
        }
    }
}

int main() {
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<std::vector<int>> graph (n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a;
        --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    std::vector<int> a(q);
    std::vector<int> b(q);
    std::vector<char> c(q);
    for (int i = 0; i < q; ++i) {
        std::cin >> c[i] >> a[i] >> b[i];
        --a[i];
        --b[i];
    }
    std::vector<int> size (n);
    for (int i = 0; i < n; ++i) {
        size[i] = graph[i].size();
    }
    for (int i = 0; i < q; ++i) {
        if (c[i] == '-') {
            for (int j = 0; j < size[a[i]]; ++j) {
                if (graph[a[i]][j] == b[i]) {
                    --size[a[i]];
                    std::swap(graph[a[i]][j], graph[a[i]][size[a[i]]]);
                    break;
                }
            }
            for (int j = 0; j < size[b[i]]; ++j) {
                if (graph[b[i]][j] == a[i]) {
                    --size[b[i]];
                    std::swap(graph[b[i]][j], graph[b[i]][size[b[i]]]);
                    break;
                }
            }
        }
    }
    int counter = -1;
    std::vector<int> k(n, -1);
    std::vector<bool> used(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            ++counter;
            dfs (i, used, graph, k, counter, size);
        }
    }
    std::vector<std::vector<int>> K(counter + 1);
    for (int i = 0; i < n; ++i) {
        K[k[i]].push_back(i);
    }
    std::vector<std::string> ans;
    for (int i = q - 1; i >= 0; --i) {
        if (c[i] == '?') {
            if (k[a[i]] == k[b[i]]) {
                ans.emplace_back("YES");
            } else {
                ans.emplace_back("NO");
            }
        } else {
            if (k[a[i]] == k[b[i]]) continue;
            if (k[a[i]] == -1 && k[b[i]] == -1) {
                ++counter;
                k[a[i]] = counter;
                k[b[i]] = counter;
                K.emplace_back();
                K[counter].push_back(a[i]);
                K[counter].push_back(b[i]);
                continue;
            }
            if (k[a[i]] == -1) {
                K[k[b[i]]].push_back(a[i]);
                k[a[i]] = k[b[i]];
                continue;
            }
            if (k[b[i]] == -1) {
                K[k[a[i]]].push_back(b[i]);
                k[b[i]] = k[a[i]];
                continue;
            }
            int x = k[a[i]];
            int y = k[b[i]];
            if (K[k[a[i]]].size() > K[k[b[i]]].size()) {
                x = k[b[i]];
                y = k[a[i]];
            }
            for (int j = 0; j < K[x].size(); ++j) {
                K[y].push_back(K[x][j]);
                k[K[x][j]] = y;
            }
        }
    }
    for (int i = ans.size() - 1; i >= 0; --i) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}
