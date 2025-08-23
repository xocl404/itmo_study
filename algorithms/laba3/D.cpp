#include <iostream>

struct Node {
    int key;
    Node* next;
    Node* prev;
    Node (int _key) : key (_key), next (nullptr), prev (nullptr){}
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
        x->prev = tail;
        x->next = nullptr;
        tail = x;
    }

    void DeleteHead () {
        Node* x = head;
        head = x->next;
        delete x;
    }

    void DeleteTail () {
        Node* x = tail;
        tail = x->prev;
        delete x;

    }

    int OutputTail () {
        return tail->key;
    }

    int OutputHead () {
        return head->key;
    }

    void PrintList () {
        Node* x = head;
        while (x != nullptr) {
            std::cout << x->key << " ";
            x = x->next;
        }
    }
};

void BubbleSort (int arr[]) {
    for (int i = 0; i < 2; ++i) {
        for (int j = i+1; j < 3; ++j) {
            if (arr[i] < arr[j]) {
                arr[i] = arr[i] + arr[j];
                arr[j] = arr[i] - arr[j];
                arr[i] = arr[i] - arr[j];
            }
        }
    }
}

int main () {

    int N,M;
    std::cin >> N >> M;
    List list;
    for (int i = 0; i < N; ++i) {
        if (i < M) {
            int _key;
            std::cin >> _key;
            list.PushBack (_key);
        } else if (i >= M) {
            int arr[3];
            std::cin >> arr[0];
            arr[1] = list.OutputTail ();
            arr[2] = list.OutputHead ();
            list.DeleteHead ();
            list.DeleteTail ();
            BubbleSort (arr);
            list.PushBack (arr[1]);
            list.PushBack (arr[0]);
        }
    }
    list.PrintList();

    return 0;
}
