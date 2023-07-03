#include "BinaryNode.h"

template <typename T>
void visit(BinaryNode<T>* node) {
    std::cout << node->element() << " ";
}

template <typename T>
void preorder(BinaryNode<T>* root) {
    if (root == nullptr) return;
    visit(root);
    preorder(root->left());
    preorder(root->right());
}

template <typename T>
void inorder(BinaryNode<T>* root) {
    if (root == nullptr) return;
    inorder(root->left());
    visit(root);
    inorder(root->right());
}

template <typename T>
void postorder(BinaryNode<T>* root) {
    if (root == nullptr) return;
    postorder(root->left());
    postorder(root->right());
    visit(root);
}

template <typename T>
void preorder2(BinaryNode<T>* root) {
    // may cause error as the function dont check for empty tree
    visit(root);
    if (root->left() != nullptr) preorder2(root->left());
    if (root->right() != nullptr) preorder2(root->right());
}

template <typename T>
int countNode(BinaryNode<T>* root) {
    if (root == nullptr) return 0;
    return 1 + countNode(root->left()) + countNode(root->right());
}