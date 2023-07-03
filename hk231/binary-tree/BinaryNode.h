#ifndef BINARYNODE_H
#define BINARYNODE_H

// Binary tree node ADT (abstract data type)
template <typename T>
class BinaryNode {
public:
    virtual ~BinaryNode() {}                // base destructor
    
    virtual T& element() = 0;               // return the node's value
    virtual void setElement(const T&) = 0;  // set the node's value

    virtual BinaryNode* left() const = 0;   // return left child
    virtual BinaryNode* right() const = 0;  // return right child

    virtual void setLeft(BinaryNode*) = 0;  // set left child
    virtual void setRight(BinaryNode*) = 0; // set right child

    virtual bool isLeaf() = 0;
};

#endif // BINARYNODE_H