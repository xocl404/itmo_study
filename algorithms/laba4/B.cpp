#include <iostream>
#include <vector>

struct PriorityQueue {
    int number;
    std::vector<int>key;
};

void SiftDown (std::vector<int>&arr, int n, int i) {
    int j = 2*i;
    if (j + 2 > n) {
        return;
    }
    if (j + 2 == n) {
        if (arr[j + 1] < arr[i]) {
            std::swap (arr[i],arr[j+1]);
        }
        return;
    }
    if (arr[j+1] < arr[i]  || arr[j+2] < arr[i]) {
        if (arr[j+1] <= arr[j+2]) {
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

void SiftUp (std::vector<int>&arr, int i) {
    int j = (i - 1) / 2;
    if (j<0) {
        return;
    }
    if (arr[j] <= arr[i]) {
        return;
    }
    std::swap (arr[i],arr[j]);
    i = j;
    SiftUp (arr, i);
}

void Heap (std::vector<int>&arr, int n) {
    for (int i = n/2; i >= 0; --i) {
        SiftDown (arr,n,i);
    }
}

int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::string operation;
    std::vector<PriorityQueue>queue;
    int i = 0;
    while (std::cin >> operation) {
            if (operation == "create") {
                queue.emplace_back();
                queue[i++].number = 0;

            } else if (operation == "insert") {
                int k;
                int x; 
                std::cin >> k >> x;
                queue[k].key.push_back(x);
                SiftUp (queue[k].key, queue[k].number);
                ++queue[k].number;

            } else if (operation == "extract-min") {
                int k;
                std::cin >> k;
                if (queue[k].number) {
                    std::cout << queue[k].key[0] << '\n';
                    std::swap(queue[k].key[0], queue[k].key[--queue[k].number]);
                    queue[k].key.pop_back();
                    SiftDown(queue[k].key, queue[k].number, 0);
                } else {
                    std::cout << "*\n";
                }

            } else if (operation == "merge") {
                int k;
                int m;
                std::cin >> k >> m;
                queue.emplace_back();
                queue[i].number = queue[k].number + queue[m].number;
                for (int j = 0; j < queue[k].number; ++j) {
                    queue[i].key.push_back(queue[k].key[j]);
                }
                for (int j = 0; j < queue[m].number; ++j) {
                    queue[i].key.push_back(queue[m].key[j]);
                }
                Heap(queue[i].key, queue[i].number);
                ++i;

            } else if (operation == "decrease-key") {
                int k;
                int x; 
                int y; 
                std::cin >> k >> x >> y;
                for (int j = 0; j < queue[k].number; ++j) {
                    if (queue[k].key[j] == x) {
                        queue[k].key[j] = y;
                        SiftUp(queue[k].key, j);
                        break;
                    }
                }
            }
    }

    return 0;
}
