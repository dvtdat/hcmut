#ifndef BST_H
#define BST_H

#include "Dictionary.h"
#include "BSTNode.h"

template <typename Key, typename T>
class BST : public Dictionary<Key, T> {
private:
    BSTNode<Key, T>* root;
    int nodeCnt;

    void clearhelp(BSTNode<Key, T>*);
    BSTNode<Key, T>* inserthelp(BSTNode<Key, T>*, const Key&, const T&);
    BSTNode<Key, T>* deletemin(BSTNode<Key, T>*);
    BSTNode<Key, T>* getmin(BSTNode<Key, T>*);
    BSTNode<Key, T>* removehelp(BSTNode<Key, T>*, const Key&);
    T findhelp(BSTNode<Key, T>*, const Key&) const;
    void printhelp(BSTNode<Key, T>*, int) const;
public:
    BST() { root = nullptr; nodeCnt = 0; }
    ~BST() { clearhelp(root); }

    void clear() {
        clearhelp(root); root = nullptr; nodeCnt = 0;
    }

    void insert(const Key& k, const T& t) {
        root = inserthelp(root, k, t);
        nodeCnt++;
    }

    T remove(const Key& k) {
        T tmp = findhelp(root, k);
        if (tmp != T()) {
            root = removehelp(root, k);
            nodeCnt--;
        }
        return tmp;
    }

    T removeAny() {
        if (root != nullptr)
        {
            T tmp = root->element();
            root = removehelp(root, root->key());
            nodeCnt--;
            return tmp;
        }
        else return nullptr;
    }

    T find(const Key& k) const { return findhelp(root, k); }
    int size() { return nodeCnt; }
    
    void print() const {
        if (root == nullptr) std::cout << "The BST is empty.\n";
        else printhelp(root, 0);
    }
};

#endif // BST_H