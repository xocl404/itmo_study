#include <iostream>
#include <vector>

using namespace std;

bool IsFIO (const std::string& str) {
    if (str[0] < 65 || str[0] > 90) return false;
    for (int i = 1; i < str.size(); ++i) {
        if (str[i] < 97 || str[i] > 122) return false;
    }
    return true;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int m;
    cin >> m;
    cin.ignore();
    for (int i = 0; i < m; ++i) {
        string str;
        getline(cin, str);
        int ws = -1;
        vector<string> v;
        for (int j = 0; j < str.size(); ++j) {
            if (str[j] == ' ') {
                v.push_back(str.substr(ws + 1, j - ws - 1));
                ws = j;
            }
        }
        v.push_back(str.substr(ws + 1, str.size() - ws - 1));
        if (v.size() != 8) {
            std::cout << "NO\n";
            continue;
        }
        bool b = true;
        for (int j = 0; j < 3; ++j) {
            if (b) b = IsFIO(v[j]);
        }
        if (!b) {
            std::cout << "NO\n";
            continue;
        }
        if (v[3].size() != 2 || v[3][0] > 57 || v[3][0] < 48 || v[3][1] > 57 || v[3][1] < 48) b = false;
        if (!b) {
            std::cout << "NO\n";
            continue;
        }
        if (v[4].size() == 11 && (v[4][0] == '8' || v[4][0] == '7')) {
            for (int j = 1; j < 11; ++j) {
                if (v[4][j] > 57 || v[4][j] < 48) b = false;
            }
        } else if (v[4].size() == 12 && v[4][0] == '+' && v[4][1] == '7') {
            for (int j = 2; j < 12; ++j) {
                if (v[4][j] > 57 || v[4][j] < 48) b = false;
            }
        } else if (v[4].size() == 15 && v[4][0] == '+' && v[4][1] == '7' && v[4][2] == '(' && v[4][6] == ')' && v[4][10] == '-') {
            for (int j = 3; j < 15; ++j) {
                if (j == 6 || j == 10) continue;
                if (v[4][j] > 57 || v[4][j] < 48) b = false;
            }
        } else if (v[4].size() == 17 && v[4][0] == '+' && v[4][1] == '7' && v[4][2] == '(' && v[4][6] == ')' && v[4][7] == '-' && v[4][11] == '-' && v[4][14] == '-') {
            for (int j = 3; j < 15; ++j) {
                if (j == 6 || j == 7 || j == 11 || j == 14) continue;
                if (v[4][j] > 57 || v[4][j] < 48) b = false;
            }
        } else {
            b = false;
        }
        if (!b) {
            std::cout << "NO\n";
            continue;
        }
        if (v[5].size() == 6 && v[5][0] == 'g' && v[5][1] == '.' && v[5][5] == ',') {
            for (int j = 2; j < 5; ++j) {
                if (v[5][j] < 65 || v[5][j] > 90) b = false;
            }
        } else {
            b = false;
        }
        if (!b) {
            std::cout << "NO\n";
            continue;
        }
        if (v[6].size() > 4 && v[6][0] == 'u' && v[6][1] == 'l' && v[6][2] == '.' && v[6][3] >= 65 && v[6][3] <= 90 && v[6][v[6].size() - 1] == ',') {
            for (int j = 4; j < v[6].size() - 1; ++j) {
                if (v[6][j] < 97 || v[6][j] > 122) {
                    b = false;
                    break;
                }
            }
        } else {
            b = false;
        }
        if (!b) {
            std::cout << "NO\n";
            continue;
        }
        if (v[7].size() > 3 && v[7][0] == 'd' && v[7][1] == '.') {
            for (int j = 2; j < v[7].size(); ++j) {
                if (v[7][j] < 48 || v[7][j] > 57) {
                    b = false;
                    break;
                }
            }
        } else {
            b = false;
        }
        if (!b) {
            std::cout << "NO\n";
            continue;
        }
        std::cout << "YES\n";
    }

    return 0;
}
