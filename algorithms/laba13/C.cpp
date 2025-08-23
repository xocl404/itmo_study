#include <iostream>

int main() {
    int N, M;
    std::cin >> N >> M;
    std::string s;
    std::cin >> s;
    int res = M;
    for (int l = 0; l < M; ++l) {
        int i, j, k;
        std::cin >> i >> j >> k;
        for (int x = -1; x < k - 1; ++x) {
            if (s[i + x] != s[j + x]) {
                --res;
                break;
            }
        }
    }
    std::cout << res;

    return 0;
}
