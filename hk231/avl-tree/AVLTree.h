#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

template <typename Key, typename Type>
class Node {
public:
    Key key;
    Type it;
    int height;
    Node* left;
    Node* right;

    Node() {}
    Node(Key key, Type it, Node* left = nullptr, Node* right = nullptr): key(key), it(it), height(1), left(left), right(right) {}
    ~Node() {}

    void setKey(const Key&);
    void setData(const Type&);
    void setLeft(Node<Key, Type>*);
    void setRight(Node<Key, Type>*);
    void setHeight(int);

    int getHeight() const;
    int getBalanceFactor() const;
};

template <typename Key, typename Type>
class AVLTree {
private:
    Node<Key, Type>* root;

    Node<Key, Type>* leftRotate(Node<Key, Type>*);
    Node<Key, Type>* rightRotate(Node<Key, Type>*);

    Node<Key, Type>* removeMin(Node<Key, Type>*);
    Node<Key, Type>* getMin(Node<Key, Type>*);

    void clear(Node<Key, Type>*);
    Type search(Node<Key, Type>*, const Key&) const;
    Node<Key, Type>* insert(Node<Key, Type>*, const Key&, const Type&);
    Node<Key, Type>* remove(Node<Key, Type>*, const Key&);
    void print(Node<Key, Type>*, int) const;
public:
    AVLTree();
    ~AVLTree();

    void clear();
    Type search(const Key&);
    void insert(const Key&, const Type&);
    void remove(const Key&);
    void print() const;
};

#endif // AVLTREE_H