#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int _key): key(_key), left(nullptr), right(nullptr){}
};

struct Tree {
    Node* root;
    Tree(): root(nullptr){}

    Node* Build(int* arr, int left, int right) {
        if (left > right) {
            return nullptr;
        }
        int mid = (right + left) / 2;
        Node* p = new Node(arr[mid]);
        if (root == nullptr) {
            root = p;
        }
        p->left = Build(arr, left, mid - 1);
        p->right = Build(arr, mid + 1, right);

        return p;
    }

    void Preorder(Node* p) {
        if (p == nullptr) {
            return;
        }
        std::cout << p->key << " ";
        Preorder(p->left);
        Preorder(p->right);
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

int main() {
    int n;
    std::cin >> n;
    int* arr = new int[n];
    Tree tree;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    tree.Build(arr, 0, n - 1);
    tree.Preorder(tree.root);
    tree.Postorder(tree.root);
    return 0;
}
