#include "blazingio.hpp"
#include <vector>

int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<bool>> graph(N, std::vector<bool> (N, false));
    std::vector<int> queue;
    std::vector<bool> have (N, false);
    for (int i = 0; i < M; ++i) {
        int A, B;
        std::cin >> A >> B;
        graph[A][B] = true;
        graph[B][A] = true;
        if (!have[A]) {
            queue.push_back(A);
            have[A] = true;
        }
        if (!have[B]) {
            queue.push_back(B);
            have[B] = true;
        }
    }
    for (int k = 0; k < N * (N - 1); ++k) {
        if (!graph[queue[0]][queue[1]]) {
            for (int i = 2; i < N - 1; ++i) {
                if (graph[queue[0]][queue[i]] && graph[queue[1]][queue[i + 1]]) {
                    for (int j = 0; 1 + j < i - j; ++j) {
                        std::swap(queue[1 + j], queue[i - j]);
                    }
                    break;
                }
            }
        }
        queue.push_back(queue[0]);
        queue.erase(queue.begin());
    }
    for (int i = 0; i < N; ++i) {
        std::cout << queue[i] << ' ';
    }

    return 0;
}
