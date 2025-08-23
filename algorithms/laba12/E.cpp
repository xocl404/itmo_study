#include <iostream>
#include <vector>

int main() {
    int N;
    std::cin >> N;
    int m = 100000;
    std::vector<std::vector<std::pair<int, int>>> ht(2 * m);
    int counter = 0;
    for (int i = 0; i < N; ++i) {
        int s;
        std::cin >> s;
        int index = abs(s - i) % m;
        if ((s - i) < 0) {
            index += m;
        }
        bool b = false;
        for (int j = 0; j < ht[index].size(); ++j) {
            if (ht[index][j].first == s - i) {
                counter += ht[index][j].second;
                ++ht[index][j].second;
                b = true;
                break;
            }
        }
        if (!b) {
            ht[index].emplace_back(s - i, 1);
        }
    }
    std::cout << counter;

    return 0;
}
