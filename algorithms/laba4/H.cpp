#include <iostream>
#include <string>

int main() {
    int N;
    std::cin >> N;
    int sum[10000];
    int size_sum = 0;
    for (int i = 0;i < 10000; ++i) {
        sum[i] = 0;
    }
    for (int i = 0; i < N; ++i) {
        std::string str;
        std::cin >> str;
        for (int j = str.length() - 1; j >= 0; --j) {
            sum[str.length() - 1 - j] += (int)str[j] - (int)'0';
            if (str.length() - 1 - j >= size_sum) {
                ++size_sum;
            }
        }
    }
    int d = 0;
    for (int i = 0; i < size_sum; ++i) {
        sum[i] += d;
        d = sum[i] / 10;
        sum[i] %= 10;
        if (d != 0 && i == size_sum - 1) {
            ++size_sum;
        }
    }
    for (int i = size_sum - 1; i >= 0; --i) {
        std::cout << sum[i];
    }

    return 0;
}
