#include <iostream>
#include <vector>
#include <queue>

int GetCoordinate (int x, int y, int z) {
    return x * 102 * 201 + y * 201 + z;
}

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

int main () {
    int K, E;
    std::cin >> K >> E;
    int sx, sy, sz;
    std::cin >> sx >> sy >> sz;
    int s = GetCoordinate(sx, sy, sz);
    int fx, fy, fz;
    std::cin >> fx >> fy >> fz;
    int f = GetCoordinate(fx, fy, fz);
    bool* b = new bool[102 * 102 * 201]{};
    for (int i = 0; i < K; ++i) {
        int x, y, z, h;
        std::cin >> x >> y >> z >> h;
        for (int j = 0; j < h; ++j) {
            b[GetCoordinate (x, y, z + j)] = true;
        }
    }
    std::vector<int>* graph = new std::vector<int>[102 * 102 * 201];
    for (int x = 1; x <= 100; ++x) {
        for (int y = 1; y <= 100; ++y) {
            for (int z = 1; z <= 199; ++z) {
                if (!b[GetCoordinate (x, y, z)]) {
                    if (!b[GetCoordinate (x - 1, y, z)]) {
                        graph[GetCoordinate (x, y, z)].push_back(GetCoordinate (x - 1, y, z));
                    }
                    if (!b[GetCoordinate (x + 1, y, z)]) {
                        graph[GetCoordinate (x, y, z)].push_back(GetCoordinate (x + 1, y, z));
                    }
                    if (!b[GetCoordinate (x, y - 1, z)]) {
                        graph[GetCoordinate (x, y, z)].push_back(GetCoordinate (x, y - 1, z));
                    }
                    if (!b[GetCoordinate (x, y + 1, z)]) {
                        graph[GetCoordinate (x, y, z)].push_back(GetCoordinate (x, y + 1, z));
                    }
                    if (!b[GetCoordinate (x, y, z - 1)]) {
                        graph[GetCoordinate (x, y, z)].push_back(GetCoordinate (x, y, z - 1));
                    }
                    if (!b[GetCoordinate (x, y, z + 1)]) {
                        graph[GetCoordinate (x, y, z)].push_back(GetCoordinate (x, y, z + 1));
                    }
                }
            }
        }
    }
    if (s == f) {
        std::cout << 0;
        return 0;
    }
    int* dist = new int [102 * 102 * 201];
    for (int i = 0; i < 102 * 102 * 201; ++i) {
        dist[i] = 102 * 102 * 201;
    }
    bfs(s, graph, 102 * 102 * 201, dist);
    if (dist[f] > E) {
        std::cout << -1;
    } else {
        std::cout << dist[f];
    }

    return 0;
}
