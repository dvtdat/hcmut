#include <iostream>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;
    Node(): data(T()), next(nullptr), prev(nullptr) {}
    Node(const T& data, Node<T>* next, Node<T>* prev): data(data), next(next), prev(prev) {}
};

template <typename T>
class LList : public List<T> {
public:
    Node<T>* head;
    Node<T>* tail;
    Node<T>* curr;
    int cnt;

    LList() : head(nullptr), tail(nullptr), curr(nullptr), cnt(0) {}

    void insert(const Node<T>& newNode) {
        curr->next = newNode;
        newNode->prev = curr;
        curr->next->next->prev = newNode;
        newNode->next = curr->next->next;   
        cnt++;     
    }

    void remove() {
        Node<T>* tmp = curr->next;

        if (tmp == tail) return; 
        curr->next = curr->next->next;
        curr->next->prev = curr;
        
        delete tmp;
    }    

    void append(const Node<T>& newNode) {

    }
};

int main() {

}