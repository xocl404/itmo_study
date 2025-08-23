#include <iostream>
#include <vector>
#define int unsigned long long

struct Edge {
    int v;
    int t;
};

struct Heap {
    std::vector<std::pair<int, int*>> heap;
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
        std::swap(heap[0], heap[size - 1]);
        --size;
        SiftDown(0);
        return heap[size].first;
    }
};

void Dijkstra (int s, const std::vector<std::vector<Edge>>& graph, std::vector<int>& dist) {
    Heap h;
    h.size = dist.size();
    for (int i = 0; i < h.size; ++i) {
        h.heap.emplace_back(i, &dist[i]);
    }
    dist[s]= 0;
    h.SiftUp(s);
    for (int j = 0; j < dist.size(); ++j) {
        int v = h.GetMin();
        for (int i = 0; i < graph[v].size(); ++i) {
            if (dist[graph[v][i].v] == 1000000000000000000 || dist[graph[v][i].v] > dist[v] + graph[v][i].t) {
                dist[graph[v][i].v] = dist[v] + graph[v][i].t;
                h.Sift(graph[v][i].v);
            }
        }
    }
}

signed main () {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<Edge>> graph(n);
    for (int i = 0; i < m; ++i) {
        int x, y, l;
        std::cin >> x >> y >> l;
        --x;
        --y;
        graph[x].push_back({y, l});
        graph[y].push_back({x, l});
    }
    std::vector<int> sum(n, 0);
    for (int i = 0; i < n; ++i) {
        std::vector<int> dist(n, 1000000000000000000);
        Dijkstra(i, graph, dist);
        for (int j = 0; j < n; ++j) {
            sum[i] += dist[j];
        }
    }
    int min = sum[0];
    int res = 0;
    for (int i = 1; i < n; ++i) {
        if (sum[i] < min) {
            min = sum[i];
            res = i;
        }
    }
    std::cout << res + 1;

    return 0;
}
