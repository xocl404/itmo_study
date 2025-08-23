#include <iostream>
#include <vector>
#define int long long 

struct Edge {
    int u;
    int v;
    int c;
};

int Get (int v, std::vector<int>& parent) {
    if (parent[v] == -1) {
        return v;
    }
    parent[v] = Get(parent[v], parent);
    return parent[v];
}

bool Unite (int u, int v, std::vector<int>& parent) {
    u = Get(u, parent);
    v = Get(v, parent);
    if (u == v) {
        return false;
    }
    parent[u] = v;
    return true;
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int N, M;
    std::cin >> N >> M;
    std::vector<Edge> graph;
    for (int i = 0; i < M; ++i) {
        int a, b, l;
        std::cin >> a >> b >> l;
        graph.push_back({a, b, l});
        int j = i;
        while (j > 0 && graph[j].c < graph[j - 1].c) {
            std::swap (graph[j], graph[j - 1]);
            --j;
        }
    }
    std::vector<int> parent(N + 1, -1);
    int result = 0;
    for (int i = 0; i < M; ++i) {
        if (Unite(graph[i].u, graph[i].v, parent)) {
            result += graph[i].c;
        }
    }

    std::cout << result;

    return 0;
}
