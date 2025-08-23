#include <iostream>
#include <string>

int main() {
    std::string str;
    getline(std::cin, str);
    int arr[100];
    int size = 0;
    for (int i = 0; i < str.length(); ++i) {
        if ((int)str[i] >= (int)'0' && (int)str[i] <= (int)'9') {
            arr[size] = (int)str[i] - (int)'0';
            ++size;
        } else if (str[i] == '+') {
            arr[size - 2] += arr[size - 1];
            --size;
        } else if (str[i] == '-') {
            arr[size - 2] -= arr[size - 1];
            --size;
        } else if (str[i] == '*') {
            arr[size - 2] *= arr[size - 1];
            --size;
        }
    }
    std::cout << arr[0];
}
