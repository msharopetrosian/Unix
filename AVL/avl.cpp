#include "avl.h"
#include <iostream>

template <typename T>
bool AVL<T>::insert(const T& value) {
    bool inserted = false;
    root = insertRecursive(root, value, inserted);
    return inserted;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::insertRecursive(
    Node* node, const T& value, bool& inserted)
{
    if (!node) {
        inserted = true;
        return new Node(value);
    }

    if (value < node->value)
        node->left = insertRecursive(node->left, value, inserted);
    else if (value > node->value)
        node->right = insertRecursive(node->right, value, inserted);
    else {
        inserted = false;
        return node;
    }

    updateHeight(node);

    int bf = balanceFactor(node);

    // Left Left
    if (bf > 1 && value < node->left->value)
        return rotateRight(node);

    // Right Right
    if (bf < -1 && value > node->right->value)
        return rotateLeft(node);

    // Left Right
    if (bf > 1 && value > node->left->value) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left
    if (bf < -1 && value < node->right->value) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

template <typename T>
void AVL<T>::inOrderTraversalHelper(const Node* root)const 
{
    if (!root) return;
    inOrderTraversalHelper(root->left);
    std::cout << root->value << " ";
    inOrderTraversalHelper(root->right);
}

template <typename T>
void AVL<T>::inOrderTraversal() const
{
    inOrderTraversalHelper(root);
}

template <typename T>
void AVL<T>::preOrderTraversalHelper(const Node* root)const 
{
    if (!root) return;
    std::cout << root->value << " ";
    preOrderTraversalHelper(root->left);
    preOrderTraversalHelper(root->right);
}

template <typename T>
void AVL<T>::preOrderTraversal() const
{
     preOrderTraversalHelper(root);
}

template <typename T>
void AVL<T>::postOrderTraversalHelper(const Node* root)const 
{
    if (!root) return;
    postOrderTraversalHelper(root->left);
    postOrderTraversalHelper(root->right);
    std::cout << root->value << " ";
}

template <typename T>
void AVL<T>::postOrderTraversal() const
{
     postOrderTraversalHelper(root);
}

template <typename T>
int AVL<T>::depth() const
{
    return depthHelper(root);
}

template <typename T>
int AVL<T>::depthHelper(const Node* node) const 
{
    if (!node) return 0;
    int left = depthHelper(node->left);
    int right = depthHelper(node->right);
    return 1 + std::max(left, right);
}

template <typename T>
AVL<T>::~AVL() {
    destroy(root);
}

template <typename T>
int AVL<T>::height(const Node* node) const {
    return node ? node->height : 0;
}

template <typename T>
int AVL<T>::balanceFactor(const Node* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

template <typename T>
void AVL<T>::updateHeight(Node* node) {
    if (node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
}

template <typename T>
typename AVL<T>::Node* AVL<T>::rotateRight(Node* y) {
    Node* x  = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left  = T2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::rotateLeft(Node* x) {
    Node* y  = x->right;
    Node* T2 = y->left;

    y->left  = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

template <typename T>
void AVL<T>::destroy(Node* node)
{
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

template <typename T>
bool AVL<T>::erase(const T& value) {
    bool removed = false;
    root = eraseRecursive(root, value, removed);
    return removed;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::eraseRecursive(
    Node* node, const T& value, bool& removed)
{
    if (!node) {
        removed = false;
        return nullptr;
    }

    if (value < node->value) {
        node->left = eraseRecursive(node->left, value, removed);
    }
    else if (value > node->value) {
        node->right = eraseRecursive(node->right, value, removed);
    }
    else {
        removed = true;

        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;

            if (!temp) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp;
            }

            delete temp;
        }
        else {
            Node* successor = node->right;
            while (successor->left) {
                successor = successor->left;
            }

            node->value = successor->value;

            node->right = eraseRecursive(node->right, successor->value, removed);
        }
    }

    if (!node) {
        return nullptr;
    }

    updateHeight(node);

    int bf = balanceFactor(node);

    if (bf > 1) {
        if (balanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }
        else {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    if (bf < -1) {
        if (balanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }
        else {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }

    return node;
}

bool AVL<T>::search(const T& value) {
    Node* x = root;
    while (x != nullptr) {
        if (value == x->value)      return true;
        else if (value < x->value)  x = x->left;
        else                        x = x->right;
    }
    return false;
}
