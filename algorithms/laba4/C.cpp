#include <iostream>

struct Shawarmist {
    long long keysort;
    long long key;
};

void SiftDown(Shawarmist *a, long long i, long long n) {
    long long j = 2 * i;
    if (j + 2 > n) {
        return;
    }
    if (j + 1 == n - 1) {
        if (a[j + 1].keysort < a[i].keysort) {
            std::swap (a[j + 1], a[i]);
            SiftDown(a, j + 1, n);
        }
        if (a[j + 1].keysort == a[i].keysort && a[j + 1].key < a[i].key) {
            std::swap (a[j + 1], a[i]);
            SiftDown(a, j + 1, n);
        }
        return;
    }
    if (a[j + 1].keysort > a[i].keysort && a[j + 2].keysort > a[i].keysort) {
        return;
    }
    if (a[j + 1].keysort == a[j + 2].keysort) {
        if (a[j + 1].key < a[j + 2].key) {
            std::swap(a[i], a[j + 1]);
            SiftDown(a, j + 1, n);
        } else {
            std::swap(a[i], a[j + 2]);
            SiftDown(a, j + 2, n);
        }
    }
    if (a[j + 1].keysort < a[j + 2].keysort) {
        if (a[j + 1].keysort == a[i].keysort && a[j + 1].key < a[i].key) {
            std::swap(a[i], a[j + 1]);
            SiftDown(a, j + 1, n);
        }
        if (a[j + 1].keysort < a[i].keysort) {
            std::swap(a[i], a[j + 1]);
            SiftDown(a, j + 1, n);
        }
        return;
    }
    if (a[j + 1].keysort > a[j + 2].keysort) {
        if (a[j + 2].keysort == a[i].keysort && a[j + 2].key < a[i].key) {
            std::swap(a[i], a[j + 2]);
            SiftDown(a, j + 2, n);
        }
        if (a[j + 2].keysort < a[i].keysort) {
            std::swap(a[i], a[j + 2]);
            SiftDown(a, j + 2, n);
        }
        return;
    }

}

void SiftUp(Shawarmist *a, long long i) {
    long long j = (i - 1) / 2;
    if (i == 0 || a[j].keysort < a[i].keysort) {
        return;
    }
    if (a[j].keysort > a[i].keysort) {
        std::swap(a[i],a[j]);
    } else if (a[j].key > a[i].key) {
        std::swap (a[i],a[j]);
    } else {
        return;
    }
    SiftUp(a, j);
}

int main() {
    long long n;
    long long m;
    std::cin >> n >> m;
    long long size_free = n;
    long long size_busy = 0;
    Shawarmist* free = new Shawarmist[n];
    Shawarmist* busy = new Shawarmist[n];
    for (long long i = 0; i < n; ++i) {
        std::cin >> free[i].keysort;
        free[i].key = 0;
        SiftUp(free, i);
    }
    long long sum = 0;
    for (long long i = 0; i < m; ++i) {
        long long t;
        long long f;
        std::cin >> t >> f;
        if (size_busy != 0) {
            while (busy[0].keysort <= t) {
                ++size_free;
                free[size_free - 1].keysort = busy[0].key;
                SiftUp(free, size_free - 1);
                std::swap(busy[0], busy[size_busy - 1]);
                --size_busy;
                SiftDown(busy, 0, size_busy);
                if (size_busy == 0) {
                    break;
                }
            }
        }
        if (size_free != 0) {
            sum += free[0].keysort * f;
            ++size_busy;
            busy[size_busy - 1].keysort = t + f;
            busy[size_busy - 1].key = free[0].keysort;
            SiftUp(busy, size_busy - 1);
            std::swap(free[0], free[size_free - 1]);
            --size_free;
            SiftDown(free, 0, size_free);
        }
    }
    std::cout << sum;

    return 0;
}
