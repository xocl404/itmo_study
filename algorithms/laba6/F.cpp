#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int _key): key(_key), left(nullptr), right(nullptr), height(1) {}
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
    if (!root) {
        return 0;
    }
    if (!root->left && !root->right) {
        return 0;
    } else if (root->left && !root->right) {
        return - root->left->height;
    } else if (!root->left && root->right) {
        return root->right->height;
    } else {
        return root->right->height - root->left->height;
    }
}

Node* LeftRotate (Node* root) {
    Node* t = root->right;
    root->right = t->left;
    t->left = root;
    root->height = GetHeight (root);
    t->height = GetHeight (t);
    return t;
}

Node* RightRotate (Node* root) {
    Node* t = root->left;
    root->left = t->right;
    t->right = root;
    root->height = GetHeight (root);
    t->height = GetHeight (t);
    return t;
}

Node* Balance (Node* root) {
    root->height = GetHeight(root);
    if (GetBalance(root) == -2) {
        if (GetBalance(root->left) > 0) {
            root->left = LeftRotate(root->left);
        }
        return RightRotate(root);
    }
    if (GetBalance(root) == 2) {
        if (GetBalance(root->right) < 0) {
            root->right = RightRotate(root->right);
        }
        return LeftRotate(root);
    }
    return root;
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
    root->height = GetHeight(root);
    return Balance(root);
}

bool Exists(Node* root, int x) {
    if (root == nullptr) {
        return false;
    } else if (root->key == x) {
        return true;
    } else if (root->key > x) {
        return Exists(root->left, x);
    } else {
        return Exists(root->right, x);
    }
}

Node* Max(Node* root) {
    if (root->right == nullptr) {
        return root;
    } else {
        return Max(root->right);
    }
}

Node* Delete(Node* root, int x) {
    if (!root) {
        return root;
    }
    if (x < root->key) {
        root->left = Delete(root->left, x);
    } else if (x > root->key) {
        root->right = Delete(root->right, x);
    } else {
        if (!root->left) {
            Node *t = root->right;
            delete root;
            return t;
        } else if (!root->right) {
            Node *t = root->left;
            delete root;
            return t;
        }
        Node *t = Max(root->left);
        root->key = t->key;
        root->left = Delete(root->left, t->key);
    }
    root->height = GetHeight(root);

    return Balance(root);
}

int main () {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    Node* root = nullptr;
    for (int i = 0; i < n; ++i) {
        char operation;
        int x;
        std::cin >> operation >> x;
        if (operation == 'A') {
            root = Insert(root, x);
            std::cout << GetBalance(root) << '\n';
        } else if (operation == 'D') {
            root = Delete(root, x);
            std::cout << GetBalance(root) << '\n';
        } else if (operation == 'C') {
            if (Exists(root, x)) {
                std::cout << "Y\n";
            } else {
                std::cout << "N\n";
            }
        }
    }

    return 0;
}
