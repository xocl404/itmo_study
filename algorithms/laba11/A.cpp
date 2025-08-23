#include "blazingio.hpp"
#include <vector>

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

int main() {
    int N, M, Q;
    std::cin >> N >> M >> Q;
    std::vector<std::vector<bool>> matrix(N);
    for (int i = 0; i < N; ++i) {
        matrix[i].resize(M, true);
    }
    for (int i = 0; i < Q; ++i) {
        int x, y;
        std::cin >> x >> y;
        matrix[x - 1][y - 1] = false;
    }
    std::vector<std::vector<int>> graph (N * M);
    for (int y = 0; y < M; ++y) {
        int l = y % 2;
        for (int x = l; x < N; x += 2) {
            if (!matrix[x][y]) continue;
            if (x != 0 && matrix[x - 1][y]) {
                graph[x + N * y].push_back(x - 1 + N * y);
            }
            if (x != N - 1 && matrix[x + 1][y]) {
                graph[x + N * y].push_back(x + 1 + N * y);
            }
            if (y != 0 && matrix[x][y - 1]) {
                graph[x + N * y].push_back(x + N * (y - 1));
            }
            if (y != M - 1 && matrix[x][y + 1]) {
                graph[x + N * y].push_back(x + N * (y + 1));
            }
        }
    }
    std::vector<int> match (N * M, -1);
    std::vector<bool> used (N * M, false);
    for (int y = 0; y < M; ++y) {
        int l = y % 2;
        for (int x = l; x < N; x += 2) {
            if (Augment(y * N + x, used, graph, match)) {
                for (int i = 0; i < N * M; ++i) {
                    used[i] = false;
                }
            }
        }
    }
    int res = 0;
    for (int i = 0; i < N * M; ++i) {
        if (match[i] != -1) {
            ++res;
        }
    }
    std::cout << res * 2;

    return 0;
}
