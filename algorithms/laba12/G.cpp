#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    int m = 50000;
    vector<vector<int>> hf (m);
    vector<int> degree (n, 0);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        ++degree[u - 1];
        ++degree[v - 1];
    }
    int counter1 = 0;
    for (int i = 0; i < n; ++i) {
        if (degree[i]) {
            int h = degree[i] * n % m;
            hf[h].push_back(degree[i]);
        } else {
            ++counter1;
        }
    }
    degree.assign(n, 0);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        ++degree[u - 1];
        ++degree[v - 1];
    }
    int counter2 = 0;
    for (int i = 0; i < n; ++i) {
        if (degree[i]) {
            int h = degree[i] * n % m;
            bool b = false;
            for (int j = 0; j < hf[h].size(); ++j) {
                if (hf[h][j] == degree[i]) {
                    b = true;
                    hf[h].erase(hf[h].begin() + j);
                    break;
                }
            }
            if (!b) {
                cout << "NO";
                return 0;
            }
        } else {
            ++counter2;
        }
    }
    if (counter1 != counter2) {
        cout << "NO";
    } else {
        cout << "YES";
    }


    return 0;
}
