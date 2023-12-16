#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class BinarySearchTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    
    void add(Node** root, T value) {
        if (*root == nullptr) {
            *root = new Node(value);
            return;
        }

        if (value <= (*root)->value) add(&(*root)->pLeft, value);
        if (value > (*root)->value) add(&(*root)->pRight, value);
    }

    void add(T value) {
        add(&root, value);
    }

    Node* deleteMin(Node** root) {
        if (*root == nullptr) return nullptr;
        if ((*root)->pLeft == nullptr) {
            Node* rightNode = (*root)->pRight;
            delete *root;
            return rightNode;
        }

        (*root)->pLeft = deleteMin(&(*root)->pLeft);
        return *root;
    }

    Node* getMin(Node* root) {
        if (root->pLeft == nullptr) return root;
        return getMin(root->pLeft);
    }

    void deleteNode(Node** root, T value) {
        if (*root == nullptr) return;
        else if (value < (*root)->value) deleteNode(&(*root)->pLeft, value);
        else if (value > (*root)->value) deleteNode(&(*root)->pRight, value);
        else {
            Node* tmp = *root;
            if ((*root)->pLeft == nullptr) {
                *root = (*root)->pRight;
                delete tmp;
            } else if ((*root)->pRight == nullptr) {
                *root = (*root)->pLeft;
                delete tmp;
            } else {
                Node* mn = getMin((*root)->pRight);
                (*root)->value = mn->value;
                (*root)->pRight = deleteMin(&(*root)->pRight);
            }
        }
    }
   
    void deleteNode(T value) {
        deleteNode(&root, value);
    }

    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }
    
    string inOrder() {
        return inOrderRec(this->root);
    }
    
    class Node {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;
    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};

int main() {
    BinarySearchTree<int> bst;
    bst.add(9);
    bst.add(2);
    bst.add(2);
    bst.add(2);
    bst.add(10);
    bst.add(8);
    cout << bst.inOrder()<<endl;
    bst.add(11);
    bst.deleteNode(2);
    bst.deleteNode(2);
    bst.deleteNode(2);
    cout << bst.inOrder();
}