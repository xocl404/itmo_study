#include "blazingio.hpp"
#include <vector>

struct Student {
    int isu;
    int points;
};

struct Group {
    int number;
    std::vector<Student> v;
    void Erase (int isu) {
        for (int i = 0; i < v.size(); ++i) {
            if (v[i].isu == isu) {
                v.erase(v.begin() + i);
                break;
            }
        }
    }
    int GetMiddle() {
        int sum = 0;
        for (auto& i : v) {
            sum += i.points;
        }
        return sum / v.size();
    }
    int GetMax () {
        int max = 0;
        for (auto& i : v) {
            max = std::max(max, i.points);
        }
        return max;
    }
};

int main() {
    int M, Q;
    std::cin >> M >> Q;
    int m = 1000;
    std::vector<std::vector<Group>> ht (m);
    for (int i = 0; i < Q; ++i) {
        char c;
        int group;
        std::cin >> c >> group;
        if (c == 'a') {
            for (auto& g : ht[group % m]) {
                if (g.number == group) {
                    std::cout << g.GetMiddle() << '\n';
                    break;
                }
            }
        } else if (c == '-') {
            int isu;
            std::cin >> isu;
            for (auto& g : ht[group % m]) {
                if (g.number == group) {
                    g.Erase(isu);
                    break;
                }
            }
        } else if (c == '+') {
            int isu, points;
            std::cin >> isu >> points;
            bool res = false;
            for (auto& g : ht[group % m]) {
                if (g.number == group) {
                    g.v.push_back({isu, points});
                    res = true;
                    break;
                }
            }
            if (!res) {
                ht[group % m].push_back({group});
                ht[group % m][ht[group % m].size() - 1].v.push_back({isu, points});
            }
        } else {
            for (auto& g : ht[group % m]) {
                if (g.number == group) {
                    std::cout << g.GetMax() << '\n';
                    break;
                }
            }
        }
    }


    return 0;
}
