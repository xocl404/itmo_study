#include <iostream>
#include <vector>

int main () {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }
    std::vector<int> res;
    for (int i = 0; i <= n / 2; ++i) {
        bool b = true;
        for (int j = 0; j < i; ++j) {
            if (v[j] != v[2 * i - 1 - j]) {
                b = false;
                break;
            }
        }
        if (b) res.push_back(n - i);
    }
    for (int i = res.size() - 1; i >= 0; --i) {
        std::cout << res[i] << ' ';
    }
    return 0;
}
