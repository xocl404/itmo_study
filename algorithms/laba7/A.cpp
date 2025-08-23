#include <iostream>

int main () {
    int n;
    std::cin >> n;
    int s = 1;
    for (int i = 0; i < n; ++i) {
        s *= 2;
    }
    char** ans = new char*[s];

    for (int i = 0; i < s; ++i) {
        ans[i] = new char[n + 1];
        ans[i][n] = '\0';
    }
    int d = s;
    for (int i = 0; i < n; ++i) {
        char* based = new char[d];
        for (int x = 0; x < d/2; ++x) {
            based[x] = '0';
            based[d/2 + x] = '1';
        }
        int count = 0;
        bool b = true;
        for (int j = 0; j < s; ++j) {
            if (b) {
                if (count == d) {
                    count = d - 1;
                    b = false;
                    ans[j][i] = based[count];
                    --count;
                } else {
                    ans[j][i] = based[count];
                    ++count;
                }
            } else {
                if (count == -1) {
                    count = 0;
                    b = true;
                    ans[j][i] = based[count];
                    ++count;
                } else {
                    ans[j][i] = based[count];
                    --count;
                }
            }
        }
        d /= 2;
    }

    for (int i = 0; i < s; ++i) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}
