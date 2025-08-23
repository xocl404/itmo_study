#include "blazingio.hpp"
#include <vector>

int main() {
    int N;
    std::cin >> N;
    int res = true;
    int m = 50000;
    std::vector<std::vector<int>> ht(2 * m);
    for (int i = 0; i < N; ++i) {
        int a;
        std::cin >> a;
        if (a >= 0) {
            ht[a % m].push_back(a);
        } else {
            ht[m + (-a) % m].push_back(a);
        }
    }
    for (int i = 0; i < N; ++i) {
        int a;
        std::cin >> a;
        int index = abs(a) % m;
        if (a < 0) {
            index += m;
        }
        bool b = false;
        for (int j = 0; j < ht[index].size(); ++j) {
            if (ht[index][j] == a) {
                b = true;
                break;
            }
        }
        if (!b) res = false;
    }
    if (res) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}
