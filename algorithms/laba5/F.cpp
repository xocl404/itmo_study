#include <iostream>
#include <stack>

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int _key): key(_key), left(nullptr), right(nullptr) {}
};

Node* BuildTree(int* pre, int n) {
    std::stack<Node*> stack;
    Node* root = new Node(pre[0]);
    stack.push(root);
    for (int i = 1; i < n; ++i) {
        Node* t = nullptr;
        while (!stack.empty() && stack.top()->key <= pre[i]) {
            t = stack.top();
            stack.pop();
        }
        if (t == nullptr) {
            t = stack.top();
            t->left = new Node(pre[i]);
            stack.push(t->left);
        } else {
            t->right = new Node(pre[i]);
            stack.push(t->right);
        }
    }
    return root;
}

void Inorder (Node* root, bool& answer) {
    if (root != nullptr) {
        Inorder(root->left, answer);
        int x;
        std::cin >> x;
        if (x != root->key) {
            answer = false;
        }
        Inorder(root->right, answer);
    }
}

void Postorder (Node* root, bool& answer) {
    if (root != nullptr) {
        Postorder(root->left, answer);
        Postorder(root->right, answer);
        int x;
        std::cin >> x;
        if (x != root->key) {
            answer = false;
        }
    }
}

void PostorderDelete(Node* root) {
    if (root == nullptr) {
        return;
    }
    PostorderDelete(root->left);
    PostorderDelete(root->right);
    delete root;
    root = nullptr;
}

int main() {
    int n;
    std::cin >> n;
    int* pre = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> pre[i];

    }
    Node* root = BuildTree(pre, n);
    bool answer = true;
    Inorder(root, answer);
    Postorder(root, answer);
    if (answer) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    PostorderDelete(root);
    
    return 0;
}
