#include <iostream>

int main () {
    int N;
    std::cin >> N;
    int* arr = new int [N];
    for (int i = 0; i < N; ++i) {
        std::cin >> arr[i];
    }

    bool b = true;
    for (int i = 1; i < N; ++i) {
        if (arr[(i-1)/2] > arr[i]) {
            b = false;
            break;
        }
    }

    if (b) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}
