#include "AVLTree.h"

template <typename Key, typename Type>
void Node<Key, Type>::setKey(const Key& newKey) {
    key = newKey;
}

template <typename Key, typename Type>
void Node<Key, Type>::setData(const Type& newData) {
    it = newData;
}

template <typename Key, typename Type>
void Node<Key, Type>::setLeft(Node<Key, Type>* newLeft) {
    left = newLeft;
}

template <typename Key, typename Type>
void Node<Key, Type>::setRight(Node<Key, Type>* newRight) {
    right = newRight;
}

template <typename Key, typename Type>
void Node<Key, Type>::setHeight(int newHeight) {
    height = newHeight;
}

template <typename Key, typename Type>
int Node<Key, Type>::getHeight() const {
    if (this == nullptr) return 0;
    int leftHeight = 0, rightHeight = 0;

    if (this->left != nullptr) leftHeight = this->left->getHeight();
    if (this->right != nullptr) rightHeight = this->right->getHeight();

    return 1 + std::max(leftHeight, rightHeight);
}

template <typename Key, typename Type>
int Node<Key, Type>::getBalanceFactor() const {
    if (this == nullptr) return 0;
    int leftHeight = 0, rightHeight = 0;

    if (this->left != nullptr) leftHeight = this->left->getHeight();
    if (this->right != nullptr) rightHeight = this->right->getHeight();

    return leftHeight - rightHeight;
}

template <typename Key, typename Type>
Node<Key, Type>* AVLTree<Key, Type>::leftRotate(Node<Key, Type>* A) {
    Node<Key, Type>* B = A->right;
    Node<Key, Type>* Y = B->left;

    B->left = A;
    A->right = Y;

    A->setHeight(1 + std::max(A->left->getHeight(), A->right->getHeight()));
    B->setHeight(1 + std::max(B->left->getHeight(), B->right->getHeight()));

    return B;
}

template <typename Key, typename Type>
Node<Key, Type>* AVLTree<Key, Type>::rightRotate(Node<Key, Type>* A) {
    Node<Key, Type>* B = A->left;
    Node<Key, Type>* Y = B->right;

    B->right = A;
    A->left = Y;

    A->setHeight(1 + std::max(A->left->getHeight(), A->right->getHeight()));
    B->setHeight(1 + std::max(B->left->getHeight(), B->right->getHeight()));

    return B;
}

template <typename Key, typename Type>
Node<Key, Type>* AVLTree<Key, Type>::removeMin(Node<Key, Type>* root) {
    if (root->left == nullptr) return root->right;
    root->left = removeMin(root->left);
    return root;
}

template <typename Key, typename Type>
Node<Key, Type>* AVLTree<Key, Type>::getMin(Node<Key, Type>* root) {
    if (root->left == nullptr) return root;
    return getMin(root->left);
}

template <typename Key, typename Type>
void AVLTree<Key, Type>::clear(Node<Key, Type>* root) {
    if (root == nullptr) return;
    clear(root->left);
    clear(root->right);
    return;
}

template <typename Key, typename Type>
Type AVLTree<Key, Type>::search(Node<Key, Type>* root, const Key& k) const {
    if (root == nullptr) return Type();
    if (k < root->key) return search(root->left, k);
    if (k > root->key) return search(root->right, k);
    return root->it;
}

template <typename Key, typename Type>
Node<Key, Type>* AVLTree<Key, Type>::insert(Node<Key, Type>* root, const Key& k, const Type& t) {
    if (root == nullptr) return new Node<Key, Type>(k, t, nullptr, nullptr);
    if (k < root->key) root->left = insert(root->left, k, t);
    if (k > root->key) root->right = insert(root->right, k, t);

    root->setHeight(1 + std::max(root->left->getHeight(), root->right->getHeight()));

    int BF = root->getBalanceFactor();

    // The extra node is in the left child of the left child of root
    if (BF > 1 && k < root->left->key) {
        return rightRotate(root);
    }

    // The extra node is in the right child of the right child of root
    if (BF < -1 && k > root->right->key) {
        return leftRotate(root);
    }

    // The extra node is in the right child of the left child of root
    if (BF > 1 && k > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // The extra node is in the left child of the right child of root
    if (BF < -1 && k < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

template <typename Key, typename Type>
Node<Key, Type>* AVLTree<Key, Type>::remove(Node<Key, Type>* root, const Key& k) {
    if (root == nullptr) return nullptr;
    else if (k < root->key) root->left = remove(root->left, k);
    else if (k > root->key) root->right = remove(root->right, k);
    else {
        Node<Key, Type>* ptr = root;
        if (root->left == nullptr) {
            root = root->right;
            delete ptr;
            return root;
        }
        else if (root->right == nullptr) {
            root = root->left;
            delete ptr;
            return root;
        }
        else {
            ptr = getMin(root->right);
            root->it = ptr->it;
            root->key = ptr->key;
            root->right = removeMin(root->right);
            delete ptr;
        }
    }

    root->setHeight(1 + std::max(root->left->getHeight(), root->right->getHeight()));

    int BF = root->getBalanceFactor();

    if (BF > 1 && root->left->getBalanceFactor() >= 0) {
        return rightRotate(root);
    }

    if (BF < -1 && root->right->getBalanceFactor() <= 0) {
        return leftRotate(root);
    }
    
    if (BF > 1 && root->left->getBalanceFactor() < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (BF < -1 && root->right->getBalanceFactor() > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

template <typename Key, typename Type>
void AVLTree<Key, Type>::print(Node<Key, Type>* root, int level) const {
    if (root == nullptr) return;

    print(root->right, level + 1);

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
    std::cout << " " << root->key << '\n';

    print(root->left, level + 1);
}

template <typename Key, typename Type>
AVLTree<Key, Type>::AVLTree() {
    root = nullptr;
}

template <typename Key, typename Type>
AVLTree<Key, Type>::~AVLTree() {
    clear();
}

template <typename Key, typename Type>
void AVLTree<Key, Type>::clear() {
    clear(root);
    root = nullptr;
}

template <typename Key, typename Type>
Type AVLTree<Key, Type>::search(const Key& k) {
    return search(root, k);
}

template <typename Key, typename Type>
void AVLTree<Key, Type>::insert(const Key& k, const Type& t) {
    std::cout << "Inserting element with key " << k << " and data of \"" << t << "\"\n"; 
    root = insert(root, k, t);
}

template <typename Key, typename Type>
void AVLTree<Key, Type>::remove(const Key& k) {
    Type tmp = search(root, k);
    if (tmp != Type()) {
        std::cout << "Deleting element with key " << k << "\n"; 
        root = remove(root, k);
    }
    else {
        std::cout << "There is no key with value of " << k << "\n";
    }
}

template <typename Key, typename Type>
void AVLTree<Key, Type>::print() const {
    if (root == nullptr)
    {
        std::cout << "The tree is empty\n";
        return;
    }
    print(root, 0);
    std::cout << '\n';
}