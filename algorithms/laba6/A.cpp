#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;
    int index;
    int height;
    Node(int _key, int _index): key(_key), left(nullptr), right(nullptr), index(_index), height(1) {};
};

Node* BuildTree (int* K, int* L, int* R, int index, Node* root) {
    root = new Node(K[index], index);
    if (L[index] != 0) {
        root->left = BuildTree(K, L, R, L[index] - 1, root->left);
        if (root->right == nullptr) {
            root->height = root->left->height + 1;
        } else {
            root->height = std::max(root->left->height, root->right->height) + 1;
        }
    }
    if (R[index] != 0) {
        root->right = BuildTree(K, L, R, R[index] - 1, root->right);
        if (root->left == nullptr) {
            root->height = root->right->height + 1;
        } else {
            root->height = std::max(root->left->height, root->right->height) + 1;
        }
    }

    return root;
}

void Preorder(Node* root, int* result) {
    if (!root) {
        return;
    }
    if (root->left && root->right) {
        result[root->index] = root->right->height - root->left->height;
    } else if (!root->left && !root->right) {
        result[root->index] = 0;
    } else if (root->left && !root->right) {
        result[root->index] = -root->left->height;
    } else if (!root->left && root->right) {
        result[root->index] = root->right->height;
    }

    Preorder(root->left, result);
    Preorder(root->right, result);
}

int main() {
    int n;
    std::cin >> n;
    int* K = new int[n];
    int* L = new int[n];
    int* R = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> K[i] >> L[i] >> R[i];
    }
    Node* root = nullptr;
    root = BuildTree(K, L, R, 0, root);
    int* result = new int[n];
    Preorder(root, result);
    for (int i = 0; i < n; ++i) {
        std::cout << result[i] << '\n';
    }

    return 0;
}
