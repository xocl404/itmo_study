#include <iostream>

void SiftDown (int *arr, int n, int i) {
    int j = 2*i;
    if (j + 2 > n) {
        return;
    }
    if (j + 2 == n) {
        if (arr[j + 1] > arr[i]) {
            std::swap (arr[i],arr[j+1]);
        }
        return;
    }
    if (arr[j+1] > arr[i]  || arr[j+2] > arr[i]) {
        if (arr[j+1] >= arr[j+2]) {
            std::swap (arr[i], arr[j+1]);
            i = j+1;
        } else {
            std::swap (arr[i], arr[j+2]);
            i = j+2;
        }
    } else {
        return;
    }
    SiftDown (arr,n,i);
}

void Heap (int *arr, int n) {
    for (int i = n/2; i >=0; --i) {
        SiftDown (arr,n,i);
    }
}

int main () {
    int n;
    std::cin >> n;
    int* arr = new int [n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    Heap (arr, n);
    for (int i = n - 1; i >= 0; i--){
        std::swap(arr[0], arr[i]);
        SiftDown(arr, i, 0);
    }
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }

    return 0;
}
