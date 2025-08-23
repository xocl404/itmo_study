#include <iostream>
#include <string>

struct Node {
    std::string filename;
    Node* left;
    Node* right;
    int height;
    Node(std::string &str): filename(str), left(nullptr), right(nullptr), height(1) {}
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

Node* Insert(Node* root, std::string str, int& number) {
    if (!root) {
        return new Node(str);
    }
    if (root->filename > str) {
        root->left = Insert(root->left, str, number);
        root->height = GetHeight(root);
    } else if (root->filename < str) {
        root->right = Insert(root->right, str, number);
        root->height = GetHeight(root);
    } else {
        int size = 0;
        char* mas = new char[str.length()];
        for (int i = 0; i < str.length(); ++i) {
            bool b = true;
            for (int j = 0; j < size; ++j) {
                if (str[i] == mas[j]) {
                    b = false;
                    break;
                }
            }
            if (b) {
                mas[size] = str[i];
                ++size;
            }
        }
        number += size;
    }
    return Balance(root);
}



int main () {
    int n;
    std::cin >> n;
    Node* root = nullptr;
    int number = 0;
    for (int i = 0; i < n; ++i) {
        std::string str;
        std::cin >> str;
        root = Insert(root, str, number);
    }
    std::cout << number;

    return 0;
}
