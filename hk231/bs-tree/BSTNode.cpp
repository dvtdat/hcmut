#include "BSTNode.h"

template <typename Key, typename Type>
Type& BSTNode<Key, Type>::data() {
    return it;
}

template <typename Key, typename Type>
void BSTNode<Key, Type>::setData(const Type& t) {
    it = t;
}

template <typename Key, typename Type>
Key& BSTNode<Key, Type>::key() {
    return k;
}

template <typename Key, typename Type>
void BSTNode<Key, Type>::setKey(const Key& newKey) {
    k = newKey;
}

template <typename Key, typename Type>
inline BSTNode<Key, Type>* BSTNode<Key, Type>::left() const {
    return lc;
}

template <typename Key, typename Type>
inline BSTNode<Key, Type>* BSTNode<Key, Type>::right() const {
    return rc;
}

template <typename Key, typename Type>
void BSTNode<Key, Type>::setLeft(BSTNode<Key, Type>* newLeft) {
    lc = newLeft;
}

template <typename Key, typename Type>
void BSTNode<Key, Type>::setRight(BSTNode<Key, Type>* newRight) {
    rc = newRight;
}

template <typename Key, typename Type>
bool BSTNode<Key, Type>::isLeaf() {
    return (lc == nullptr && rc == nullptr);
}