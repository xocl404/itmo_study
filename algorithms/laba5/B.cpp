#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int _key): key(_key), left(nullptr), right(nullptr) {}
};

Node* Insert(Node* root, int x) {
    if (root == nullptr) {
        return new Node(x);
    } else if (root->key > x) {
        root->left = Insert(root->left, x);
    } else if (root->key < x) {
        root->right = Insert(root->right, x);
    }
    return root;
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
        root->left = Delete(root->left, x);
    } else if (x > root->key) {
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
    }
    return root;
}

Node* Next (Node* root, int x) {
    Node* t = root;
    Node* next = nullptr;
    while (t != nullptr) {
        if (t->key > x) {
            next = t;
            t = t->left;
        } else {
            t = t->right;
        }
    }
    return next;
}

Node* Prev (Node* root, int x) {
    Node* t = root;
    Node* prev = nullptr;
    while (t != nullptr) {
        if (t->key < x) {
            prev = t;
            t = t->right;
        } else {
            t = t->left;
        }
    }
    return prev;
}

void Postorder(Node* p) {
        if (p == nullptr) {
            return;
        }
        Postorder(p->left);
        Postorder(p->right);
        delete p;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);


    std::string operation;
    Node* root = nullptr;
    while (std::cin >> operation) {
        if (operation == "insert") {
            int x;
            std::cin >> x;
            root = Insert(root, x);

        } else if (operation == "delete") {
            int x;
            std::cin >> x;
            root = Delete(root, x);

        } else if (operation == "exists") {
            int x;
            std::cin >> x;
            if (Exists (root, x)) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }

        } else if (operation == "next") {
            int x;
            std::cin >> x;
            if (Next(root, x) != nullptr) {
                std::cout << Next(root, x)->key << '\n';
            } else {
                std::cout << "none\n";
            }

        } else if (operation == "prev") {
            int x;
            std::cin >> x;
            if (Prev(root, x) != nullptr) {
                std::cout << Prev(root, x)->key << '\n';
            } else {
            std::cout << "none\n";
            }
        }
    }
    Postorder(root);

    return 0;
}
