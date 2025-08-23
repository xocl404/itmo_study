#include <iostream>
#include <string>

struct Node {
    std::string filename;
    Node* left;
    Node* right;
    int height;
    bool first = false;
    bool second = false;
    bool third = false;
    Node(std::string &str, int number): filename(str), left(nullptr), right(nullptr), height(1) {
        if (number == 1) {
            first = true;
        } else if (number == 2) {
            second = true;
        } else if (number == 3) {
            third = true;
        }
    }
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
    t->height = GetHeight (root);
    return t;
}

Node* RightRotate (Node* root) {
    Node* t = root->left;
    root->left = t->right;
    t->right = root;
    root->height = GetHeight (root);
    t->height = GetHeight (root);
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

Node* Insert(Node* root, std::string str, int number) {
    if (!root) {
        return new Node(str, number);
    }
    if (root->filename > str) {
        root->left = Insert(root->left, str, number);
        root->height = GetHeight(root);
    } else if (root->filename < str) {
        root->right = Insert(root->right, str, number);
        root->height = GetHeight(root);
    } else {
        if (number == 1) {
            root->first = true;
        } else if (number == 2) {
            root->second = true;
        } else if (number == 3) {
            root->third = true;
        }
    }
    return Balance(root);
}

void Preorder(Node* root, int &one, int &two, int &three) {
    if (!root) {
        return;
    }
    if (root->first && root->second && !root->third) {
        one += 1;
        two += 1;
    } else if (root->first && !root->second && root->third) {
        one += 1;
        three += 1;
    } else if (!root->first && root->second && root->third) {
        two += 1;
        three += 1;
    } else if (root->first && !root->second && !root->third) {
        one += 3;
    } else if (!root->first && root->second && !root->third) {
        two += 3;
    } else if (!root->first && !root->second && root->third) {
        three += 3;
    }
    Preorder(root->left, one, two, three);
    Preorder(root->right, one, two, three);
}

int main () {
    int n;
    std::cin >> n;
    std::string str;
    Node* root = nullptr;

    for (int i = 0; i < n; ++i) {
        std::cin >> str;
        root = Insert(root, str, 1);
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> str;
        root = Insert(root, str, 2);
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> str;
        root = Insert(root, str, 3);
    }
    int one = 0;
    int two = 0;
    int three = 0;
    Preorder(root, one, two, three);
    std::cout << one << " " << two << " " << three;

    return 0;
}
