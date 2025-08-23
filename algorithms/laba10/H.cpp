#include <iostream>
#include <vector>

struct Edge {
    int v;
    int t;
};

struct Heap {
    std::vector<std::pair<int, long long*>> heap;
    int size;

    void Sift (int v) {
        for (int i = 0; i < size; ++i) {
            if (heap[i].first == v) {
                SiftDown(i);
                SiftUp(i);
                return;
            }
        }
    }

    void SiftDown (int i) {
        int j = i * 2;
        if (j + 1 >= size) return;
        if (j + 1 == size - 1) {
            if (*heap[i].second >= *heap[j + 1].second) {
                std::swap(heap[i], heap[j + 1]);
            }
            return;
        }
        if (*heap[i].second >= *heap[j + 1].second || *heap[i].second >= *heap[j + 2].second) {
            if (*heap[j + 1].second < *heap[j + 2].second)  {
                std::swap(heap[i], heap[j + 1]);
                SiftDown(j + 1);
            } else {
                std::swap(heap[i], heap[j + 2]);
                SiftDown(j + 2);
            }
        }
    }

    void SiftUp (int i) {
        int j = (i - 1) / 2;
        if (i == 0) return;
        if (*heap[j].second < *heap[i].second) return;
        if (*heap[j].second >= *heap[i].second) {
            std::swap(heap[i], heap[j]);
            SiftUp(j);
        }
    }

    int GetMin () {
        if (*heap[0].second == LONG_LONG_MAX) return -1;
        std::swap(heap[0], heap[size - 1]);
        --size;
        SiftDown(0);
        return heap[size].first;
    }
};

void Dijkstra (int s, const std::vector<std::vector<Edge>>& graph, std::vector<long long>& dist) {
    Heap h;
    h.size = dist.size();
    for (int i = 0; i < h.size; ++i) {
        h.heap.emplace_back(i, &dist[i]);
    }
    dist[s]= 0;
    h.SiftUp(s);
    for (int j = 0; j < dist.size(); ++j) {
        int v = h.GetMin();
        if (v == -1) break;
        for (int i = 0; i < graph[v].size(); ++i) {
            if (dist[graph[v][i].v] > dist[v] + 1ll * graph[v][i].t) {
                dist[graph[v][i].v] = dist[v] + 1ll * graph[v][i].t;
                h.Sift(graph[v][i].v);
            }
        }
    }
}


int main () {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<Edge>> graph (n);
    for (int i = 0; i < m; ++i) {
        int s, t;
        std::cin >> s >> t;
        std::vector<int> vertex (s);
        for (int j = 0; j < s; ++j) {
            std::cin >> vertex[j];
        }
        for (int u = 0; u < s - 1; ++u) {
            for (int v = u + 1; v < s; ++v) {
                graph[vertex[u] - 1].push_back({vertex[v] - 1, t});
                graph[vertex[v] - 1].push_back({vertex[u] - 1, t});
            }
        }
    }
    std::vector<long long> dist (n, LONG_LONG_MAX);
    Dijkstra(0, graph, dist);
    if (dist[k - 1] == LONG_LONG_MAX) {
        std::cout << -1;
        return 0;
    }
    std::cout << dist[k - 1];

    return 0;
}
