#include <iostream>

struct Node {
    int key;
    int level;
    Node* left;
    Node* right;
    Node(int _key): key(_key), level(0), left(nullptr), right(nullptr){}
};

struct Tree {
    Node *root;
    Tree() : root(nullptr) {}

    int Insert (int _key, int size) {
        Node* p = new Node(_key);
        if (root == nullptr) {
            ++size;
            root = p;
            return size;
        }
        Node* t = root;
        while(t != nullptr) {
            if (_key > t->key) {
                ++p->level;
                if (p->level >= size) {
                    ++size;
                }
                if (t->right == nullptr) {
                    t->right = p;
                    return size;
                }
                t = t->right;
            } else if (_key < t->key) {
                ++p->level;
                if (p->level >= size) {
                    ++size;
                }
                if (t->left == nullptr) {
                    t->left = p;
                    return size;
                }
                t = t->left;
            } else {
                return size;
            }
        }
    }

    void Preorder(Node *p, int* result) {
        if (p == nullptr) {
            return;
        }
        result[p->level] = std::max(result[p->level], p->key);
        Preorder(p->left, result);
        Preorder(p->right, result);
    }
    
    void Postorder(Node* p) {
        if (p == nullptr) {
            return;
        }
        Postorder(p->left);
        Postorder(p->right);
        delete p;
    }
};

int main () {
    int n;
    std::cin >> n;
    Tree tree;
    int size = 0;
    for (int i = 0; i < n; ++i) {
        int _key;
        std::cin >> _key;
        size = tree.Insert(_key, size);
    }
    int* result = new int[size];
    for (int i = 0; i < size; ++i) {
        result[i] = 0;
    }
    tree.Preorder(tree.root, result);
    for (int i = 0; i < size; ++i) {
        std::cout << result[i] << " ";
    }
    tree.Postorder(tree.root);

    return 0;
}
