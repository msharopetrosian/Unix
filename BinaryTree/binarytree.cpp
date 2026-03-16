#include "binarytree.h"
#include <iostream>

template <typename T>
bool BinaryTree<T>::insert(const T& value)
{
    if (!d_root) {
        d_root = new Node(value);
        return true;
    }
        Node* temp = d_root;
        while(true)
        {
           if (value < temp->value){
                if (temp->left == nullptr){
                    temp->left = new Node(value);
                    return true;
                } 
                temp = temp->left;
           } 
           else if (temp-> value < value){
                if (temp->right == nullptr){
                    temp->right = new Node(value);
                    return true;
                }
                temp = temp->right;
           }
           else {
                return false;
           }
        }
}

template <typename T>
void BinaryTree<T>::inOrderTraversalHelper(const Node* root)const 
{
    if (!root) return;
    inOrderTraversalHelper(root->left);
    std::cout << root->value << " ";
    inOrderTraversalHelper(root->right);
}

template <typename T>
void BinaryTree<T>::inOrderTraversal() const
{
    inOrderTraversalHelper(d_root);
}

template <typename T>
void BinaryTree<T>::preOrderTraversalHelper(const Node* root)const 
{
    if (!root) return;
    std::cout << root->value << " ";
    preOrderTraversalHelper(root->left);
    preOrderTraversalHelper(root->right);
}

template <typename T>
void BinaryTree<T>::preOrderTraversal() const
{
     preOrderTraversalHelper(d_root);
}

template <typename T>
void BinaryTree<T>::postOrderTraversalHelper(const Node* root)const 
{
    if (!root) return;
    postOrderTraversalHelper(root->left);
    postOrderTraversalHelper(root->right);
    std::cout << root->value << " ";
}

template <typename T>
void BinaryTree<T>::postOrderTraversal() const
{
     postOrderTraversalHelper(d_root);
}

template <typename T>
void BinaryTree<T>::destroy(Node* node) 
{
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

template <typename T>
int BinaryTree<T>::depth() const
{
    return depthHelper(d_root);
}

template <typename T>
int BinaryTree<T>::depthHelper(const Node* node) const 
{
    if (!node) return 0;
    int left = depthHelper(node->left);
    int right = depthHelper(node->right);
    return 1 + std::max(left, right);
}

template <typename T>
bool BinaryTree<T>::erase(const T& value)
{
        d_root = eraseHelper(d_root, value);
        return true;    
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::eraseHelper(Node* node, const T& value)
{
    if (node == nullptr) return nullptr;
    if (value < node->value) {
        node->left = eraseHelper(node->left, value);
    }
    else if (node->value < value) {
        node->right = eraseHelper(node->right, value);
    }
    else {
        if (node->left == nullptr) {
            Node* rightChild = node->right;
            delete node;
            return rightChild;
        }
        if (node->right == nullptr) {
            Node* leftChild = node->left;
            delete node;
            return leftChild;
        }

        Node* successor = findMinNode(node->right);
        node->value = successor->value;
        node->right = eraseHelper(node->right, successor->value);
    }
    return node;
}

template <typename T>
typename BinaryTree<T>::Node* 
BinaryTree<T>::findMinNode(Node* node) const
{
    if (node == nullptr) {
        return nullptr;
    }
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
