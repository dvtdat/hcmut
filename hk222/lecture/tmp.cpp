#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;
};

void push(Node** pHead, int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = *pHead;
    *pHead = newNode;
}

int getCount(Node* pHead) {
    if (pHead == NULL) return 0;
    else return 1 + getCount(pHead->next);
}

int main() {
    Node* head = NULL;

    push(&head, 1);
    push(&head, 3);
    push(&head, 10);
}