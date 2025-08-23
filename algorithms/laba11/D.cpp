#include <iostream>
#include <vector>
#include <set>

bool IsFreeOwner (const std::vector<bool>& owners) {
    for (int i = 0; i < owners.size(); ++i) {
        if (!owners[i]) return true;
    }
    return false;
}

int main () {
    int N;
    std::cin >> N;
    std::vector<std::vector<int>> cats_preferences (N, std::vector<int>(N));
    std::vector<std::vector<int>> owners_preferences (N, std::vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> cats_preferences[i][j];
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> owners_preferences[i][j];
        }
    }
    std::vector<int> owners (N, -1);
    std::vector<bool> cats (N, false);
    while (IsFreeOwner (cats)) {
        for (int cat = 0; cat < N; ++cat) {
            if (cats[cat]) continue;
            int owner = cats_preferences[cat][0];
            if (owners[owner] == -1) {
                cats[cat] = true;
                owners[owner] = cat;
            } else {
                int cat_raiting = -1;
                int new_cat_raiting = -1;
                for (int j = 0; j < N; ++j) {
                    if (cat_raiting != -1 && new_cat_raiting != -1) break;
                    if (owners_preferences[owner][j] == owners[owner]) cat_raiting = j;
                    if (owners_preferences[owner][j] == cat) new_cat_raiting = j;
                }
                if (new_cat_raiting < cat_raiting) {
                    cats[owners[owner]] = false;
                    cats_preferences[owners[owner]].erase (cats_preferences[owners[owner]].begin());
                    owners[owner] = cat;
                    cats[cat] = true;
                } else {
                    cats_preferences[cat].erase (cats_preferences[cat].begin());
                }
            }
        }
    }
    std::set<std::pair<int, int>> result;
    for (int i = 0; i < N; ++i) {
        result.insert({owners[i], i});
    }
    for (auto& i : result) {
        std::cout << i.first << ' ' << i.second << '\n';
    }

    return 0;
}
