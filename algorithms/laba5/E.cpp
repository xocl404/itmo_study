#include <iostream>
#include <string>

struct Node {
    std::string filename;
    bool first = false;
    bool second = false;
    bool third = false;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(std::string str, int number){
        filename = str;
        if (number == 1) {
            first = true;
        } else if (number == 2) {
            second = true;
        } else if (number == 3) {
            third = true;
        }
    }
};

Node* Insert (Node* root, std::string str, int number) {
    if (root == nullptr) {

        return new Node(str, number);
    } else if (root->filename > str) {
        root->left = Insert(root->left, str, number);
    } else if (root->filename < str) {
        root->right = Insert(root->right, str, number);
    } else if (root->filename == str) {
        if (number == 1) {
            root->first = true;
        } else if (number == 2) {
            root->second = true;
        } else if (number == 3) {
            root->third = true;
        }
    }

    return root;
}

void Preorder(Node* root, int &one, int &two, int &three) {
    if (root == nullptr) {

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

void Postorder(Node* root) {
    if (root == nullptr) {
        return;
    }
    Postorder(root->left);
    Postorder(root->right);
    delete root;
    root = nullptr;
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
    Postorder(root);
    
    return 0;
}
