#include "blazingio.hpp"
//#include <iostream>
#include <vector>
#include <algorithm>


bool Augment (int v, std::vector<bool>& used, std::vector<std::vector<int>>& graph, std::vector<int>& match) {
    if (used[v]) return false;
    used[v] = true;
    for (int i = 0; i < graph[v].size(); ++i) {
        if (match[graph[v][i]] == -1 || Augment(match[graph[v][i]], used, graph, match)) {
            match[graph[v][i]] = v;
            return true;
        }
    }
    return false;
}

bool Sort (std::pair<int, int>& a, std::pair<int, int>& b) {
    return a.second > b.second;
}

bool Sort2 (std::pair<int, int>& a, std::pair<int, int>& b) {
    return a.first < b.first;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> vertex(n);
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        vertex[i].first = i;
        vertex[i].second = a;
    }
    std::sort(vertex.begin(), vertex.end(), Sort);
    std::vector<std::vector<int>> graph (n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[v - 1].push_back(u - 1);
    }
    std::vector<int> match (n, -1);
    std::vector<bool> used (n, false);
    for (int v = 0; v < n; ++v) {
        if (Augment(v, used, graph, match)) {
            for (int i = 0; i < n; ++i) {
                used[i] = false;
            }
        }
    }
    int res = 0;
    std::vector<std::pair<int, int>> ans;
    for (int i = 0; i < n; ++i) {
        if (match[i] != -1) {
            ++res;
            ans.push_back({i + 1, match[i] + 1});
        }
    }
    std::sort(ans.begin(), ans.end(), Sort2);
    std::cout << res << '\n';
    for (int i = 0; i < ans.size() - 1; ++i) {
        std::cout << ans[i].first << ' ' << ans[i].second << '\n';
    }
    std::cout << ans[ans.size() - 1].first << ' ' << ans[ans.size() - 1].second;
    return 0;
}
