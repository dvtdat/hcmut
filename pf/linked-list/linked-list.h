#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

struct Node {
public:
    int data;
    Node* next;
    Node(int data, Node* next) : data(data), next(next) {};
};

void pushNode(Node* &head, int data)
{
    if (head == nullptr)
    {
        head = new Node(data, head);
        return;
    }

    Node* pre = head;
    while (pre->next)
    {
        pre = pre->next;
    }
    pre->next = new Node(data, pre->next);
}

void insertNode(Node* &head, int data, int index)
{
    if (index < 1)
    {
        head = new Node(data, head);
        return;
    }

    Node* pre = head;
    while (index > 1 && pre->next)
    {
        pre = pre->next;
        index--;
    }
    pre->next = new Node(data, pre->next);
    return;
}

void deleteList(Node* &head)
{
    Node* cur;
    
    while (head->next)
    {
        cur = head;
        head = head->next;
        delete cur;
    }

    head = nullptr;
}

void removeNode(Node* &head, int index)
{
    if (head == nullptr) return;
    if (index < 1)
    {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        return;
    }

    Node* pre = head;
    while (index > 1 && pre->next)
    {
        pre = pre->next;
        index--;
    }

    Node* cur = pre->next;
    Node* aft = cur->next;
    pre->next = aft;
    delete cur;
    return;
}

void removeLastNode(Node* &head)
{
    if (head == nullptr) return;
    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }

    Node* pre = head;
    while (pre->next->next)
    {
        pre = pre->next;
    }

    pre->next = nullptr;
    delete(pre->next);
}

void removeNodeEqualValue(Node* &head, int value)
{
    Node* pre = head;
    while (pre->next)
    {
        Node* cur = pre->next;
        if (cur->data == value)
        {
            Node* aft = cur->next;
            pre->next = aft;
            delete cur;
            continue;
        }
        
        pre = pre->next;
    }
}

void changeData(Node* &head, int index, int value)
{
    if (head == nullptr) return;
    Node* pre = head;
    while (index > 1 && pre->next)
    {
        pre = pre->next;
        index--;
    }

    pre->data = value;
}

void reverseList(Node* &head)
{
    if (head == nullptr) return;

    Node* pre = head;
    Node* tmp = nullptr;

    while (pre != nullptr)
    {
        Node* cur = pre->next;
        pre->next = tmp;
        tmp = pre;
        pre = cur;
    }

    head = tmp;
}

void convertSinglyToCircular(Node* &head)
{
    Node* pre = head;
    while (pre->next)
    {
        pre = pre->next;
    }
    pre->next = head;
}

bool checkCircular(Node* head)
{
    if (head == nullptr) return true;
    Node* pre = head;

    while (pre->next && pre->next != head)
    {
        pre = pre->next;
    }

    return (pre->next == head);
}

int countCircular(Node* head)
{
    if (!checkCircular(head)) return 0;
    if (head == nullptr) return 0;

    int count = 0;
    Node* pre = head;
    while (pre->next != head)
    {
        pre = pre->next;
        count++;
    }

    return count + 1;
}

int countValue(Node* head, int value)   //recursive approach
{
    if (head == nullptr) return 0;
    return (head->data == value) + countValue(head->next, value);
}

int getSize(Node* head)                 //recursive approach
{
    if (head->next == nullptr) return 1;
    return 1 + getSize(head->next);
}

int getSum(Node* head)
{
    if (head == nullptr) return 0;
    return head->data + getSum(head->next);
}

Node* mergeListShallow(Node* &head1, Node* &head2)
{
    Node* tmp = head1;
    Node* pre = tmp;
    while (pre->next)
    {
        pre = pre->next;
    }
    pre->next = head2;

    return tmp;
}

void printList(Node* head)
{
    if (head == nullptr) return;
    for(Node* p = head; p; p = p->next)
    {
        cout << p->data << ' ';
    }
    cout << '\n'; 
}