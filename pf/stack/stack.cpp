#include "stack.h"

template<typename T>
Node<T>::Node(const T& value, Node<T>* next): data(value), next(next)
{
    // std::cout << "Create new Node...\n";
}

template<typename T>
MyStack<T>::MyStack():  nS(0), pS(0)
{
    // std::cout << "Create new MyStack...\n";
}

template<typename T>
MyStack<T>::MyStack(const MyStack& S)
{
    Node<T>* cur = new Node<T>(S.pS->data, nullptr);
    nS = S.nS;
    pS = cur;

    if (S.pS->next == nullptr) return;

    Node<T>* ptr = S.pS->next;
    while (ptr != nullptr)
    {
        Node<T>* node = new Node<T>(ptr->data, nullptr);
        cur->next = node;
        cur = cur->next;
        ptr = ptr->next;
    }
}

template<typename T>
MyStack<T>::MyStack(MyStack&& S): nS(S.nS), pS(S.pS)
{
    S.nS = 0;
    S.pS = nullptr;
}

template<typename T>
MyStack<T>& MyStack<T>::operator=(const MyStack& S)
{
    if (this == &S) return *this;
    clear();

    Node<T>* cur = new Node<T>(S.pS->data, nullptr);
    nS = S.nS;
    pS = cur;

    if (S.pS->next == nullptr) return *this;

    Node<T>* ptr = S.pS->next;
    while (ptr != nullptr)
    {
        Node<T>* node = new Node<T>(ptr->data, nullptr);
        cur->next = node;
        cur = cur->next;
        ptr = ptr->next;
    }
}

template<typename T>
MyStack<T>& MyStack<T>::operator=(MyStack&& S)
{
    clear();
    nS = S.nS;
    pS = S.pS;

    S.nS = 0;
    S.pS = nullptr;

    return *this;
}

template<typename T>
void MyStack<T>::clear()
{
    while (!empty()) pop();
}

template<typename T>
void MyStack<T>::push(T value)
{
    nS++;
    Node<T>* node = new Node<T>(value, pS);
    pS = node;
}

template<typename T>
T& MyStack<T>::top()
{
    if (nS < 1) throw -1;
    return pS->data;
}

template<typename T>
void MyStack<T>::pop()
{
    if (nS < 1) throw -1;
    nS--;
    Node<T>* node = pS;
    pS = pS->next;
    delete node;
}

template<typename T>
bool MyStack<T>::empty()
{
    return (nS == 0);
}

template<typename T>
int MyStack<T>::size()
{
    return nS;
}