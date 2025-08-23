#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    int number;
    Node(int _key): key(_key), left(nullptr), right(nullptr), height(1), number(1) {};
};

int GetHeight (Node* root){
    if (!root->left && !root->right) {
        return 1;
    } else if (root->left && !root->right) {
        return root->left->height + 1;
    } else if (!root->left && root->right) {
        return root->right->height + 1;
    } else {
        return std::max(root->left->height, root->right->height) + 1;
    }
}

int GetBalance (Node* root) {
    if (!root->left && !root->right) {
        return 0;
    } else if (root->left && !root->right) {
        return root->left->height;
    } else if (!root->left && root->right) {
        return - root->right->height;
    } else {
        return root->left->height - root->right->height;
    }
}

Node* LeftRotate (Node* root) {
    Node* t = root->right;
    root->right = t->left;
    t->left = root;
    return t;
}

Node* RightRotate (Node* root) {
    Node* t = root->left;
    root->left = t->right;
    t->right = root;
    return t;
}

Node* Balance (Node* root) {
    if (GetBalance(root) == 2) {
        if (GetBalance(root->left) < 0) {
            root->left = LeftRotate(root->left);
        }
        return RightRotate(root);
    }
    if (GetBalance(root) == -2) {
        if (GetBalance(root->right) > 0) {
            root->right = RightRotate(root->right);
        }
        return LeftRotate(root);
    }
    return root;
}

Node* BuildTree (int* K, int* L, int* R, int index, Node* root) {
    root = new Node(K[index]);
    if (L[index] != 0) {
        root->left = BuildTree(K, L, R, L[index] - 1, root->left);
        root->height = GetHeight(root);
    }
    if (R[index] != 0) {
        root->right = BuildTree(K, L, R, R[index] - 1, root->right);
        root->height = GetHeight(root);
    }

    return root;
}

void GetNumber(Node* root, int& num) {
    if (!root) {
        return;
    }
    root->number = ++num;
    GetNumber(root->left, num);
    GetNumber(root->right, num);
}

void Preorder(Node* root) {
    if (!root) {
        return;
    }
    std::cout << root->key << " ";
    if (root->left) {
        std::cout << root->left->number << " ";
    } else {
        std::cout << 0 << " ";
    }
    if (root->right) {
        std::cout << root->right->number << '\n';
    } else {
        std::cout << 0 << '\n';
    }
    Preorder(root->left);
    Preorder(root->right);
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
    root = Balance(root);
    std::cout << n << '\n';
    int num = 0;
    GetNumber(root, num);
    Preorder (root);

    return 0;
}
