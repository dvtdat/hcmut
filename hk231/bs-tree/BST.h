#ifndef BST_H
#define BST_H

#include "BSTNode.cpp"

template <typename Key, typename Type>
class BST {
private:
    BSTNode<Key, Type>* root;

    void clear(BSTNode<Key, Type>*);
    BSTNode<Key, Type>* insert(BSTNode<Key, Type>*, const Key&, const Type&);
    BSTNode<Key, Type>* deleteMin(BSTNode<Key, Type>*);
    BSTNode<Key, Type>* getMin(BSTNode<Key, Type>*);
    BSTNode<Key, Type>* remove(BSTNode<Key, Type>*, const Key&);
    Type find(BSTNode<Key, Type>*, const Key&) const;
    void print(BSTNode<Key, Type>*, int) const;
public:
    BST();
    ~BST();

    void clear();
    void insert(const Key&, const Type&);
    Type remove(const Key&);
    Type removeAny();
    Type find(const Key&);

    void print() const;
};


#endif // BST_H