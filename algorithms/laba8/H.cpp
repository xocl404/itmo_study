#include <iostream>
#include <vector>

void dfs (int v, std::vector<int>* graph, bool* used, std::vector<int>& result) {
    used[v] = true;
    for (int i = 0; i < graph[v].size(); ++i) {
        if (!used[graph[v][i]]) {
            dfs(graph[v][i], graph, used, result);
        }
    }
    result.push_back(v);
}


void dfsR (int v, std::vector<int>* graph, bool* used, int* g, int counter) {
    used[v] = true;
    g[v] = counter;
    for (int i = 0; i < graph[v].size(); ++i) {
        if (!used[graph[v][i]]) {
            dfsR(graph[v][i], graph, used, g, counter);
        }
    }
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int>* graph = new std::vector<int>[2 * n];
    std::vector<int>* reverse_graph = new std::vector<int>[2 * n];
    for (int i = 0; i < k; ++i) {
        std::string str1;
        std::cin >> str1;
        if (str1[0] == '!') {
            int ten = 1;
            int a = -1;
            for (int j = str1.length() - 1; j > 0; --j) {
                a += ((int)str1[j] - 48) * ten;
                ten *= 10;
            }
            graph[a].push_back(a + n);
            reverse_graph[a + n].push_back(a);
        } else {
            int ten = 1;
            int a = -1;
            for (int j = str1.length() - 1; j >= 0; --j) {
                a += ((int)str1[j] - 48) * ten;
                ten *= 10;
            }
            std::string str2;
            int b;
            std::cin >> str2 >> b;
            --b;
            if (str2 == "||") {
                graph[a + n].push_back(b);
                graph[b + n].push_back(a);
                reverse_graph[b].push_back(a + n);
                reverse_graph[a].push_back(b + n);
            } else if (str2 == "->") {
                graph[a].push_back(b);
                graph[b + n].push_back(a + n);
                reverse_graph[b].push_back(a);
                reverse_graph[a + n].push_back(b + n);
            } else if (str2 == "&") {
                graph[a + n].push_back(b);
                graph[b + n].push_back(a);
                graph[a + n].push_back(b + n);
                graph[b].push_back(a);
                graph[a].push_back(b);
                graph[b + n].push_back(a + n);
                reverse_graph[b].push_back(a + n);
                reverse_graph[a].push_back(b + n);
                reverse_graph[b + n].push_back(a + n);
                reverse_graph[a].push_back(b);
                reverse_graph[b].push_back(a);
                reverse_graph[a + n].push_back(b + n);
            } else {
                graph[a].push_back(b + n);
                graph[b].push_back(a + n);
                graph[a + n].push_back(b);
                graph[b + n].push_back(a);
                reverse_graph[b + n].push_back(a);
                reverse_graph[a + n].push_back(b);
                reverse_graph[b].push_back(a + n);
                reverse_graph[a].push_back(b + n);
            }
        }
    }
    bool* used = new bool[2 * n]{};
    std::vector<int> result;
    for (int i = 0; i < 2 * n; ++i) {
        if(!used[i]) {
            dfs(i, graph, used, result);
        }
    }
    for (int i = 0; i < 2 * n; ++i) {
        used[i] = false;
    }
    int counter = 0;
    int* g = new int[2 * n];
    for (int i = 2 * n - 1; i >= 0; --i) {
        if (!used[result[i]]) {
            ++counter;
            dfsR(result[i], reverse_graph, used, g, counter);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (g[i] == g[i + n]) {
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";

    return 0;
}
