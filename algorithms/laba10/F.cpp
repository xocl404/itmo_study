#include <iostream>
#include <vector>

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

int Kruskal1 (const std::vector<Edge>& graph, std::vector<int> parent, std::vector <int>& mst) {
    int result = 0;
    for (int i = 0; i < graph.size(); ++i) {
        if (Unite(graph[i].u, graph[i].v, parent)) {
            result += graph[i].c;
            mst.push_back(i);
        }
    }
    return result;
}

int Kruskal2 (const std::vector<Edge>& graph, std::vector<int> parent, int e) {
    int result = 0;
    for (int i = 0; i < graph.size(); ++i) {
        if (i == e) continue;
        if (Unite(graph[i].u, graph[i].v, parent)) {
            result += graph[i].c;
        }
    }
    return result;
}

int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<Edge> graph;
    for (int i = 0; i < M; ++i) {
        int A, B, C;
        std::cin >> A >> B >> C;
        graph.push_back({A, B, C});
        int j = i;
        while (j > 0 && graph[j].c < graph[j - 1].c) {
            std::swap (graph[j], graph[j - 1]);
            --j;
        }
    }
    std::vector<int> parent(N + 1, -1);
    std::vector <int> mst;
    int S1 = Kruskal1(graph, parent, mst);
    int S2 = 2147483647;
    for (int j = 0; j < mst.size(); ++j) {
        std::vector<int> p (N + 1, -1);
        S2 = std::min (S2, Kruskal2(graph, p, mst[j]));
    }
    std::cout << S1 << ' ' << S2;

    return 0;
}
