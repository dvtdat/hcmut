#include <bits/stdc++.h>

using namespace std;

template <typename E>
class HuffNode {
public:
    virtual ~HuffNode() {}
    virtual int weight() const = 0;
    virtual bool isLeaf() const = 0;
};

template <typename E>
class LeafNode : public HuffNode<E> {
private:
    E it;
    int wgt;

public:
    LeafNode(const E& val, int freq) { it = val; wgt = freq; }
    int weight() const override { return wgt; }
    E val() const { return it; }
    bool isLeaf() const override { return true; }
};

template <typename E>
class InternalNode : public HuffNode<E> {
private:
    HuffNode<E>* lc;
    HuffNode<E>* rc;
    int wgt;

public:
    InternalNode(HuffNode<E>* l, HuffNode<E>* r): lc(l), rc(r) {
        wgt = l->weight() + r->weight();
    }
    int weight() const override { return wgt; }
    bool isLeaf() const override { return false; }
    HuffNode<E>* left() const { return lc; }
    HuffNode<E>* right() const { return rc; }
    void setLeft(HuffNode<E>* b) { lc = b; }
    void setRight(HuffNode<E>* b) { rc = b; }
};

template <typename E>
class HuffTree {
private:
    HuffNode<E>* Root;

public:
    HuffTree(E& val, int freq) {
        Root = new LeafNode<E>(val, freq);
    }
    
    HuffTree(HuffTree<E>* l, HuffTree<E>* r) {
        Root = new InternalNode<E>(l->root(), r->root());
    }

    ~HuffTree() {}
    HuffNode<E>* root() { return Root; }
    int weight() { return Root->weight(); }
};

template <typename E>
struct minTreeComp {
    bool operator()(const HuffTree<E>* lhs, const HuffTree<E>* rhs) const {
        return (lhs->root()->weight() > rhs->root()->weight());
    }
};

template <typename E>
HuffTree<E>* buildHuff(HuffTree<E>** TreeArray, int count) {
    priority_queue<HuffTree<E>*> forest(TreeArray, TreeArray + count);
    HuffTree<E> *temp1, *temp2, *temp3 = nullptr;
    
    while (forest.size() > 1) {
        temp1 = forest.top();
        forest.pop();
        
        temp2 = forest.top();
        forest.pop();
        
        temp3 = new HuffTree<E>(temp1, temp2);
        forest.push(temp3);
    }
    
    return temp3;
}

int main() {
    char A = 'A';
    char B = 'B';
    char C = 'C';

    HuffTree<char> treeA(A, 10);
    HuffTree<char> treeB(B, 5);
    HuffTree<char> treeC(C, 15);

    HuffTree<char>* TreeArray[] = { &treeA, &treeB, &treeC };

    HuffTree<char>* huffmanTree = buildHuff(TreeArray, 3);

    cout << "Weight of Huffman tree: " << huffmanTree->weight() << endl;

    return 0;
}

