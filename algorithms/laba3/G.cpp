#include <iostream>

bool check (int d, int chairs[], int N, int K) {
    int count = 1;
    int cow = chairs [0];
    for (int j = 1; j < N; ++j) {
        if ((chairs[j] - cow) >= d) {
            ++count;
            cow = chairs[j];
        }
    }
    if (count >=  K) {
        return true;
    }
    return false;
}

int main () {
    int N, K;
    std::cin >> N >> K;
    int* chairs = new int [N];
    for (int i = 0; i < N; ++i) {
        std::cin >> chairs[i];
    }
    int left = 0;
    int right = chairs[N-1] - chairs[0] + 1;
    while (right - left > 1) {
        int mid = (left + right) / 2;
        if (check(mid, chairs, N, K)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    std::cout << left;

    return 0;
}
