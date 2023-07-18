#ifndef BSTNODE_H
#define BSTNODE_H

template <typename Key, typename Type>
class BSTNode {
private:
    Key k;
    Type it;
    BSTNode* lc;
    BSTNode* rc;
public:
    BSTNode(): lc(nullptr), rc(nullptr) {}
    BSTNode(Key k, Type it, BSTNode* l = nullptr, BSTNode* r = nullptr): k(k), it(it), lc(l), rc(r) {}
    ~BSTNode() {}

    Type& data();
    void setData(const Type&);
    Key& key();
    void setKey(const Key&);

    inline BSTNode* left() const;
    inline BSTNode* right() const;
    void setLeft(BSTNode<Key, Type>*);
    void setRight(BSTNode<Key, Type>*);

    bool isLeaf();
};

#endif // BSTNODE_H