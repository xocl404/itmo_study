#include <iostream>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;
    vector<int> v;
    for (int i = 1; i <= s.size(); ++i) {
        if (s.size() % i == 0) v.push_back(i);
    }
    for (int i : v) {
        string str;
        for (int j = 0; j < i; ++j) {
            str.push_back(s[j]);
        }
        int j = i;
        bool b = true;
        while (j < s.size()) {
            for (int k = j; k < j + i; ++k) {
                if (s[k] != str[k - j]) {
                    b = false;
                    break;
                }
            }
            if (!b) break;
            j += i;
        }
        if (b) {
            std::cout << i;
            return 0;
        }
    }
    return 0;
}
