#ifndef BSTNODE_H
#define BSTNODE_H

#include "BinaryNode.h"

template <typename Key, typename T>
class BSTNode : public BinaryNode<T> {
private:
    Key k;          // node's key
    T it;           // node's value
    BSTNode* lc;
    BSTNode* rc;
    /* There is no such pointer for parent's node. TODO: explain why*/
public:
    BSTNode() { lc = rc = nullptr; }
    BSTNode(Key K, T t, BSTNode* l = nullptr, BSTNode* r = nullptr): k(K), it(t), lc(l), rc(r) {}
    ~BSTNode() {}

    T& element() { return it; }
    void setElement(const T& t) { it = t; }
    Key& key() { return k; }
    void setKey(const Key& K) { k = K; }

    inline BSTNode* left() const { return lc; }
    void setLeft(BinaryNode<T>* b) { lc = (BSTNode*)b; }
    inline BSTNode* right() const { return rc; }
    void setRight(BinaryNode<T>* b) { rc = (BSTNode*)b; }

    bool isLeaf() { return (lc == nullptr) && (rc == nullptr); }
};

#endif // BSTNODE_H