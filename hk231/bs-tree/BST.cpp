#include "BST.h"

template <typename Key, typename Type>
void BST<Key, Type>::clear(BSTNode<Key, Type>* root) {
    if (root == nullptr) return;
    clear(root->right());
    clear(root->left());
    return;
}

template <typename Key, typename Type> 
BSTNode<Key, Type>* BST<Key, Type>::insert(BSTNode<Key, Type>* root, const Key& k, const Type& it) {
    if (root == nullptr) return new BSTNode<Key, Type>(k, it, nullptr, nullptr);
    if (k < root->key()) root->setLeft(insert(root->left(), k, it));
    else if (k > root->key()) root->setRight(insert(root->right(), k, it));
    return root;
}

template <typename Key, typename Type>
BSTNode<Key, Type>* BST<Key, Type>::deleteMin(BSTNode<Key, Type>* root) {
    if (root->left() == nullptr) return root->right();
    root->setLeft(deleteMin(root->left()));
    return root;
}

template <typename Key, typename Type>
BSTNode<Key, Type>* BST<Key, Type>::getMin(BSTNode<Key, Type>* root) {
    if (root->left() == nullptr) return root;
    return getMin(root->left());
}

template <typename Key, typename Type>
BSTNode<Key, Type>* BST<Key, Type>::remove(BSTNode<Key, Type>* root, const Key& k) {
    if (root == nullptr) return nullptr;
    else if (k < root->key()) root->setLeft(remove(root->left(), k));
    else if (k > root->key()) root->setRight(remove(root->right(), k));
    else {
        BSTNode<Key, Type>* tmp = root;
        if (root->left() == nullptr) {
            root = root->right();
            delete tmp;
        }
        else if (root->right() == nullptr) {
            root = root->left();
            delete tmp;
        }
        else {
            BSTNode<Key, Type>* tmp2 = getMin(root->right());
            root->setData(tmp2->data());
            root->setKey(tmp2->key());
            root->setRight(deleteMin(root->right()));
            delete tmp2;
        }
    }

    return root;
}

template <typename Key, typename Type>
Type BST<Key, Type>::find(BSTNode<Key, Type>* root, const Key& k) const {
    if (root == nullptr) return nullptr;
    if (k < root->key()) return find(root->left(), k);
    if (k > root->key()) return find(root->right(), k);
    return root->data();
}

template <typename Key, typename Type>
void BST<Key, Type>::print(BSTNode<Key, Type>* root, int level) const {
    if (root == nullptr) return;

    print(root->right(), level + 1);

    for (int i = 0; i < level; ++i) {
        std::cout << "  |";
        for (int j = 0; j < 2; ++j) {
            if (i != level - 1) {
                std::cout << " ";
            } else {
                std::cout << "-";
            }
        }
    }
    std::cout << " " << root->key() << '\n';

    print(root->left(), level + 1);
}

template <typename Key, typename Type>
BST<Key, Type>::BST() {
    root = nullptr;
}

template <typename Key, typename Type>
BST<Key, Type>::~BST() {
    clear(root);
}

template <typename Key, typename Type>
void BST<Key, Type>::clear() {
    clear(root);
    root = nullptr;
}

template <typename Key, typename Type>
void BST<Key, Type>::insert(const Key& k, const Type& t) {
    root = insert(root, k, t);
}

template <typename Key, typename Type>
Type BST<Key, Type>::remove(const Key& k) {
    Type tmp = find(root, k);
    if (tmp != Type()) {
        root = remove(root, k);
    }
    return tmp;
}

template <typename Key, typename Type>
Type BST<Key, Type>::removeAny() {
    if (root != nullptr) {
        Type tmp = root->data();
        root = remove(root, root->key());
        return tmp;
    }
    return nullptr;
}

template <typename Key, typename Type>
Type BST<Key, Type>::find(const Key& k) {
    return find(root, k);
}

template <typename Key, typename Type>
void BST<Key, Type>::print() const {
    if (root == nullptr) std::cout << "The tree is empty\n";
    else print(root, 0);
}