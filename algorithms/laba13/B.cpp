#include <iostream>
#include <vector>

int main() {
    std::string str;
    std::cin >> str;
    std::vector<int> p(str.size() + 1);
    p[0] = -1;
    for (int i = 1; i <= str.size(); ++i) {
        int k = p[i - 1];
        while (k != -1 && str[k] != str[i - 1]) {
            k = p[k];
        }
        p[i] = k + 1;
    }
    for (int i = 1; i <= str.size(); ++i) {
        std::cout << p[i] << ' ';
    }

    return 0;
}
