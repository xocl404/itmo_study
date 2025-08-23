#include <iostream>
#include <vector>

int main() {
    std::string t;
    std::string x;
    std::cin >> t >> x;
    std::vector<int> res;
    for (int i = 0; i < t.size() - x.size() + 1; ++i) {
        bool b = true;
        for (int j = 0; j < x.size(); ++j) {
            if (t[i + j] != x[j]) {
                b = false;
                break;
            }
        }
        if (b) {
            res.push_back(i);
        }
    }
    std::cout << res.size() << '\n';
    for (int i = 0; i < res.size(); ++i) {
        std::cout << res[i] << ' ';
    }

    return 0;
}
