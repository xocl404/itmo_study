#include <iostream>
#include <vector>
#include <queue>

void bfs (int s, std::vector<int>* g, int N, int* dist) {
    dist[s] = 0;
    std::queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < g[v].size(); ++i) {
            if (dist[g[v][i]] == N) {
                dist[g[v][i]] = dist[v] + 1;
                q.push(g[v][i]);
            }
        }

    }
}

int main() {
    int N, M, K;
    std::cin >> N >> M >> K;
    std::vector<int>* graph = new std::vector<int>[N];
    for (int x = 0; x < M; ++x) {
        int i, j;
        std::cin >> i >> j;
        graph[i - 1].push_back(j - 1);
        graph[j - 1].push_back(i - 1);
    }
    int* dist = new int[N];
    for (int i = 0; i < N; ++i) {
        dist[i] = N;
    }
    bfs(0, graph, N, dist);
    std::vector<int> answer;

    for (int i = 0; i < N; ++i) {
        if (dist[i] == K) {
            answer.push_back(i + 1);
        }
    }
    if (answer.empty()) {
        std::cout << "NO";
        return 0;
    }
    for (int i = 0; i < answer.size(); ++i) {
        std::cout << answer[i] << '\n';
    }

    return 0;
}
