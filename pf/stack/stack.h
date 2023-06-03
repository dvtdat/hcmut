#ifndef MYSTACK_H
#define MYSTACK_H

template<typename T>
class MyStack;

template<typename T>
class Node
{
    friend class MyStack<T>;        // help MyStack have the permission to access Node properties
private:
    T data;
    Node<T>* next;
public:
    Node(const T& value, Node<T>* next);
};

template<typename T>
class MyStack
{
private:
    Node<T>* pS;
    int nS;
public:
    MyStack();                          // custom constructor
    MyStack(const MyStack<T>& S);       // copy constructor
    MyStack(MyStack&& S);               // move constructor, use with std::move
    ~MyStack() {}                       // destructor

    MyStack& operator=(const MyStack& S);        // copy assignment
    MyStack& operator=(MyStack&& S);             // move assignment, use with std::move

    void clear();
    void push(T value);
    T& top();
    void pop();
    bool empty();
    int size();
};

#endif // MYSTACK_H