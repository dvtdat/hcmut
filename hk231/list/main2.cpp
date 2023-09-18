#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename U>
class Node {
public:
    U data;
    Node<U>* next;
    Node(): data(U()), next(nullptr) {}
    Node(const U& data, Node<U>* next): data(data), next(next) {}
};

int main() {
    Node<int>* head = new Node<int>(15, nullptr);

    Node<int>* tmp1 = new Node<int>(16, nullptr);
    Node<int>* tmp2 = new Node<int>(17, nullptr);

    Node<int>* tail = tmp2;

    head->next = tmp1;
    tmp1->next = tmp2;

    Node<int>* cur = head;
    while (cur != nullptr) {
        cout << cur->data << ' ';
        cur = cur->next;
    }
    cout << '\n';

    

    cur = head;
    while (cur != nullptr) {
        cout << cur->data << ' ';
        cur = cur->next;
    }
}