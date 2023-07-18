#include "BST.h"

template <typename Key, typename T>
void BST<Key, T>::clearhelp(BSTNode<Key, T>*) {
    if (root == nullptr) return;
    clearhelp(root->right());
    clearhelp(root->left());
    return;
}

template <typename Key, typename T>
BSTNode<Key, T>* BST<Key, T>::inserthelp(BSTNode<Key, T>* root, const Key& k, const T& it) {
    if (root == nullptr) return new BSTNode<Key, T>(k, it, nullptr, nullptr);
    if (k < root->key()) root->setLeft(inserthelp(root->left(), k, it));
    else if (k > root->key()) root->setRight(inserthelp(root->right(), k, it));
    return root;
}

template <typename Key, typename T>
BSTNode<Key, T>* BST<Key, T>::deletemin(BSTNode<Key, T>* root) {
    if (root->left() == nullptr) return root->right();
    else
    {
        root->setLeft(deletemin(root->left()));
        return root;
    }
}

template <typename Key, typename T>
BSTNode<Key, T>* BST<Key, T>::getmin(BSTNode<Key, T>* root) {
    if (root->left() == nullptr) return root;
    else return getmin(root->left());
}

template <typename Key, typename T>
BSTNode<Key, T>* BST<Key, T>::removehelp(BSTNode<Key, T>* root, const Key& k) {
    if (root == nullptr) return nullptr;
    else if (k < root->key()) root->setLeft(removehelp(root->left(), k));
    else if (k > root->key()) root->setRight(removehelp(root->right(), k));
    else
    {
        BSTNode<Key, T>* tmp = root;
        if (root->left() == nullptr)
        {
            root = root->right();
            delete tmp;
        }
        else if (root->right() == nullptr)
        {
            root = root->left();
            delete tmp;
        }
        else
        {
            BSTNode<Key, T>* tmp2 = getmin(root->right());
            root->setElement(tmp2->element());
            root->setKey(tmp2->key());
            root->setRight(deletemin(root->right()));
            delete tmp2;
        }
    }

    return root;
}


template <typename Key, typename T>
T BST<Key, T>::findhelp(BSTNode<Key, T>* root, const Key& k) const {
    if (root == nullptr) return nullptr;
    if (k < root->key()) return findhelp(root->left(), k);
    else if (k > root->key()) return findhelp(root->right(), k);
    else return root->element();
}

template <typename Key, typename T>
void BST<Key, T>::printhelp(BSTNode<Key, T>* root, int level) const {
    if (root == nullptr) return;

    printhelp(root->right(), level + 1);

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

    printhelp(root->left(), level + 1);
}
