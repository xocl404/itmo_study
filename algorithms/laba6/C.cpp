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
    if (!root) {
        return 0;
    }
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
    if (!root) {
        return 0;
    }
    int l = 0;
    int r = 0;
    if (root->left) {
        l = root->left->height;
    }
    if (root->right) {
        r = root->right->height;
    }
    return l - r;
}

Node* LeftRotate (Node* root) {
    Node* t = root->right;
    root->right = t->left;
    t->left = root;
    root->height = GetHeight(root);
    t->height = GetHeight(t);
    return t;
}

Node* RightRotate (Node* root) {
    Node* t = root->left;
    root->left = t->right;
    t->right = root;
    root->height = GetHeight(root);
    t->height = GetHeight(t);
    return t;
}

Node* Balance (Node* root) {
    root->height = GetHeight(root);
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
    }
    if (R[index] != 0) {
        root->right = BuildTree(K, L, R, R[index] - 1, root->right);
    }
    root->height = GetHeight(root);

    return Balance(root);
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
    int l = 0;
    int r = 0;
    if (root->left) {
        l = root->left->number;
    }
    if (root->right) {
        r = root->right->number;
    }
    std::cout << root->key << " " << l << " " << r << '\n';
    Preorder(root->left);
    Preorder(root->right);
}

Node* Insert(Node* root, int x) {
    if (!root) {
        return new Node(x);
    }
    if (root->key > x) {
        root->left = Insert(root->left, x);
        root->height = GetHeight(root);
    } else if (root->key < x) {
        root->right = Insert(root->right, x);
        root->height = GetHeight(root);
    }
    return Balance(root);
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
    if (n) {
        root = BuildTree(K, L, R, 0, root);
    }
    int x;
    std::cin >> x;
    root = Insert(root, x);
    std::cout << n + 1 << '\n';
    int num = 0;
    GetNumber(root, num);
    Preorder (root);

    return 0;
}
