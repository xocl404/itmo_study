#include <iostream>
#include <string>

void SiftDown (int **arr, int n, int i) {
    int j = 2*i;
    if (j + 2 > n) {
        return;
    }
    if (j + 2 == n) {
        if (arr[1][j + 1] > arr[1][i]) {
            std::swap (arr[0][i],arr[0][j+1]);
            std::swap (arr[1][i],arr[1][j+1]);
        }
        if (arr[1][j + 1] == arr[1][i] && arr[0][j + 1] > arr[0][i]) {
            std::swap (arr[0][i],arr[0][j+1]);
            std::swap (arr[1][i],arr[1][j+1]);
        }
        return;
    }
    if (arr[1][j+1] >= arr[1][i]  || arr[1][j+2] >= arr[1][i]) {
        if (arr[1][j+1] > arr[1][j+2]) {
            std::swap (arr[1][i], arr[1][j+1]);
            std::swap (arr[0][i], arr[0][j+1]);
            i = j+1;
        } else if (arr[1][j+1] < arr[1][j+2]) {
            std::swap (arr[1][i], arr[1][j+2]);
            std::swap (arr[0][i], arr[0][j+2]);
            i = j+2;
        } else if (arr[1][j+1] == arr[1][j+2]) {
            if (arr[0][j+1] > arr[0][j+2]) {
                std::swap (arr[1][i], arr[1][j+1]);
                std::swap (arr[0][i], arr[0][j+1]);
                i = j+1;
            } else {
                std::swap (arr[1][i], arr[1][j+2]);
                std::swap (arr[0][i], arr[0][j+2]);
                i = j+2;
            }
        }
    } else {
        return;
    }
    SiftDown (arr,n,i);
}

void SiftUp (int** arr, int i) {
    int j = (i - 1) / 2;
    if (j < 0) {
        return;
    }
    if (arr[1][j] > arr[1][i]) {
        return;
    }
    if (arr[1][j] < arr[1][i]) {
    std::swap(arr[1][i], arr[1][j]);
    std::swap(arr[0][i], arr[0][j]);
    i = j;
    }
    if (arr[1][j] == arr[1][i]) {
        if (arr[0][j] < arr[0][i]) {
            std::swap(arr[0][i], arr[0][j]);
            std::swap(arr[1][i], arr[1][j]);
            i = j;
        } else {
            return;
        }
    }
    SiftUp (arr, i);
}

void Heap (int **arr, int n) {
    for (int i = n/2; i >=0; --i) {
        SiftDown (arr,n,i);
    }
}

void ExtractMax (int **arr, int n) {
    std::swap(arr[0][0], arr[0][n-1]);
    std::swap(arr[1][0], arr[1][n-1]);
    SiftDown (arr, n - 1, 0);
}

void Delete (int **arr, int n, int i) {
    std::swap(arr[0][i], arr[0][n-1]);
    std::swap(arr[1][i], arr[1][n-1]);
    SiftDown(arr, n - 1, i);
    SiftUp(arr,i);
}

int main () {
    int n;
    std::cin >> n;
    int** rating = new int*[2];
    int** honorarium = new int*[2];
    for (int i = 0; i < 2; ++i) {
        rating[i] = new int[n];
        honorarium[i] = new int[n];
    }
    for (int i = 0; i < n; ++i) {
        int c;
        int r;
        int h;
        std::cin >> c >> r >> h;
        rating[0][i] = c;
        rating[1][i] = r;
        honorarium[0][i] = c;
        honorarium[1][i] = h;
    }
    int m;
    std::cin >> m;
    bool* answer = new bool[m];
    for (int i = 0; i < m; ++i) {
        std::string str;
        std::cin >> str;
        if (str == "YES") {
            answer[i] = true;
        } else {
            answer[i] = false;
        }
    }
    Heap(rating, n);
    Heap(honorarium, n);

    int* calling = new int[m];
    int* result = new int[n];
    int ia = 0;
    int ic = 0;
    int size = n;
    for (int i = 0; i < n; ++i) {
        if (rating[0][0] == honorarium[0][0]) {
            result[ia] = rating[0][0];;
            ++ia;
            ExtractMax (rating, size);
            ExtractMax (honorarium, size);
            size -= 1;
        } else if (ic < m) {
            calling[ic] = rating[0][0];
            if (answer[ic]) {
                result[ia] = rating[0][0];
                ++ia;
                for (int j = 0; j < size; ++j) {
                    if (honorarium[0][j] == rating[0][0]) {
                        Delete(honorarium, size, j);
                        break;
                    }
                }
                ExtractMax (rating, size);
                --size;
            } else {
                for (int j = 0; j < size; ++j) {
                    if (honorarium[0][j] == rating[0][0]) {
                        Delete(honorarium, size, j);
                        break;
                    }
                }
                ExtractMax (rating, size);
                --size;
            }
            ++ic;
        } else {
            ExtractMax (rating, size);
            --size;
        }
    }

    for (int i = 0; i < m; ++i) {
        std::cout << calling[i] << " ";
    }
    std::cout << '\n';
    for (int i = 0; i < ia; ++i) {
        std::cout << result[i] << " ";
    }

    return 0;
}
