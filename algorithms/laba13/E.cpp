#include <iostream>

struct Node {
    std::string key;
    Node* left;
    Node* right;
    int size;
    Node(const std::string& key): key(key), left(nullptr), right(nullptr), size(1) {};
};

Node* Insert(Node* root, const std::string& x) {
    if (!root) {
        return new Node(x);
    } else if (root->key >= x) {
        ++root->size;
        root->left = Insert(root->left, x);
    } else if (root->key < x) {
        ++root->size;
        root->right = Insert(root->right, x);
    }
    return root;
}

const std::string& GetkMinimum (Node* root, int k) {
    int left_size = 0;
    if (root->left) {
        left_size = root->left->size;
    }
    if (k == left_size + 1) {
        return root->key;
    } else if (k > left_size + 1) {
        k -= (left_size + 1);
        return GetkMinimum(root->right, k);
    } else {
        return GetkMinimum(root->left, k);
    }
}

int main () {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    Node* root = nullptr;
    for (int i = 0; i < n; ++i) {
        std::string name;
        std::cin >> name;
        if (name[0] >= 48 && name[0] <= 57) {
            int k = std::stoi(name);
            std::cout << GetkMinimum(root, k) << '\n';
            continue;
        }
        root = Insert(root, name);
    }


    return 0;
}
