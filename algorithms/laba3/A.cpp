#include <iostream>

struct Node {
    int key;
    Node* prev;
    Node (int _key) : key (_key), prev (nullptr) {}
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
        Node *x = new Node(_key);
        if (IsEmpty()) {
            head = x;
            tail = x;
            return;
        }
        x->prev = tail;
        tail = x;
    }

    void PrintTail () {
        if (IsEmpty()) {
            return;
        }
        std::cout << tail->key << "\n";
    }

    void DeleteTail () {
        if (IsEmpty()) {
             return;
         }
        if (head == tail) {
             Node* x = head;
             head = nullptr;
             tail  = nullptr;
             delete x;
             return;
        }
        Node* x=tail;
        tail = x->prev;
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
            list.PrintTail ();
            list.DeleteTail ();
        }
    }

    return 0;
}
