#include <iostream>

struct Node {
    int key;
    Node* next;
    Node (int _key) : key (_key), next (nullptr) {}
};

struct List {
    Node* head;
    Node* tail;
    List () : head (nullptr), tail (nullptr) {}

    bool IsEmpty () {
        if (head == nullptr) {
            return true;
        }
            return false;
    }

    void PushBack (int _key) {
        Node* x = new Node(_key);
        if (IsEmpty()) {
            head = x;
            tail = x;
            return;
        }
        tail->next = x;
        tail = x;
    }

    void PrintHead () {
        if (IsEmpty()) {
            return;
        }
        std::cout << head->key << "\n";
    }

    void DeleteHead () {
        if (IsEmpty()) {
            return;
        }
        Node* x = head;
        head = x->next;
        delete x;
    }
};

int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    List list;

    for (int i = 0; i < n; ++i) {
        char ch;
        std::cin >> ch;
        if (ch == '+') {
            int _key;
            std::cin >> _key;
            list.PushBack (_key);
        } else if (ch == '-'){
            list.PrintHead ();
            list.DeleteHead ();
        }
    }

    return 0;
}
