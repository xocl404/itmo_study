#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;
    int size;
    Node(int _key): key(_key), left(nullptr), right(nullptr), size(1) {};
};

Node* Insert(Node* root, int x) {
    if (root == nullptr) {
        return new Node(x);
    } else if (root->key > x) {
        ++root->size;
        root->left = Insert(root->left, x);
    } else if (root->key < x) {
        ++root->size;
        root->right = Insert(root->right, x);
    }
    return root;
}

Node* Min(Node* root) {
    if (root->left == nullptr) {
        return root;
    } else {
        return Min(root->left);
    }
}

Node* Delete(Node* root, int x) {
    if (root == nullptr) {
        return root;
    }
    if (x < root->key) {
        --root->size;
        root->left = Delete(root->left, x);
    } else if (x > root->key) {
        --root->size;
        root->right = Delete(root->right, x);
    } else {
        if (root->left == nullptr) {
            Node* t = root->right;
            delete root;
            return t;
        } else if (root->right == nullptr) {
            Node* t = root->left;
            delete root;
            return t;
        }
        Node* t = Min(root->right);
        root->key = t->key;
        root->right = Delete(root->right, t->key);
        --root->size;
    }
    return root;
}

int GetkMaximum (Node* root, int k) {
    int right_size = 0;
    if (root->right != nullptr) {
        right_size = root->right->size;
    }
    if (k == right_size + 1) {
        return root->key;
    } else if (k > right_size + 1) {
        k -= (right_size + 1);
        return GetkMaximum(root->left, k);
    } else {
        return GetkMaximum(root->right, k);
    }
}

void Postorder(Node* p) {
        if (p == nullptr) {
            return;
        }
        Postorder(p->left);
        Postorder(p->right);
        delete p;
}

int main () {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    Node* root = nullptr;
    for (int i = 0; i < n; ++i) {
        int operation;
        int k;
        std::cin >> operation >> k;
        if (operation == 1) {
            root = Insert(root, k);
        } else if (operation == 0) {
            std::cout << GetkMaximum(root, k) << '\n';
        } else if (operation == -1) {
            root = Delete(root, k);
        }
    }
    Postorder(root);
    
    return 0;
}
