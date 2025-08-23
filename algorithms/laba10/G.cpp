#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

struct Edge {
    int u;
    int v;
    int c;
    bool b;
};

bool Sort (Edge& a, Edge& b) {
    return a.c < b.c;
}

int Get(int v, std::vector<int>& parent) {
    if (parent[v] == -1) {
        return v;
    }
    return parent[v] = Get(parent[v], parent);
}

bool Unite (int u, int v, std::vector<int>& parent, std::vector<int>& size) {
    u = Get(u, parent);
    v = Get(v, parent);
    if (u == v) return false;
    if (size[u] < size[v]) {
        std::swap(u, v);
    }
    parent[v] = u;
    size[u] += v;
    return true;
}

signed main() {
    int N, M, K;
    std::cin >> N >> M >> K;
    std::vector<Edge> graph;
    for (int i = 0; i < M; ++i) {
        int X, Y, S;
        std::cin >> X >> Y >> S;
        graph.push_back({X, Y, S, false});

    }
    for (int i = 0; i < K; ++i) {
        int X, Y, B;
        std::cin >> X >> Y >> B;
        graph.push_back({X, Y, B, true});
    }
    std::sort (graph.begin(), graph.end(), Sort);
    std::vector<int> parent(N + 1, -1);
    std::vector<int> size(N + 1, 1);
    int expense = 0;
    for (int i = 0; i < M + K; ++i) {
        if (Unite(graph[i].u, graph[i].v, parent, size)) {
            if (graph[i].b) {
                expense += graph[i].c;
            }
        } else if (!graph[i].b) {
            expense -= graph[i].c;
        }
    }
    std::cout << std::max (0ll, expense);

    return 0;
}
