#include "RBT.h"
#include <iostream>

template<typename T>
RBT<T>::RBT() {
    NIL = new Node(T{}, false);     // black sentinel
    NIL->left = NIL->right = NIL;
    root = NIL;
}

template<typename T>
RBT<T>::~RBT() {
    destroy(root);
    delete NIL;
}

template<typename T>
void RBT<T>::destroy(Node* node) {
    if (node == NIL) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

template<typename T>
void RBT<T>::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NIL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template<typename T>
void RBT<T>::rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NIL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NIL) {
        root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

template <typename T>
void RBT<T>::insert(const T& value) {
    Node* z = new Node(value);
    Node* y = NIL;
    Node* x = root;

    while (x != NIL){
        y = x;
        if (z->value < x->value){
                x = x->left;
            } else {
                x = x->right;
            }
        }
    z->parent = y;
    if (y == NIL){
        root = z;
    } else if (z->value < y->value){
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = NIL;
    z->right = NIL;
    z->color = true;
    insertFixup(z);
}

template <typename T>
void RBT<T>::insertFixup(Node* z) {
    Node* y;
    while (z->parent->color) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color) {                  // Case 1
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) { // Case 2
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = false;    // Case 3
                z->parent->parent->color = true;
                rightRotate(z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (y->color) {                  // Case 1
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) { // Case 2
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = false;   // Case 3
                z->parent->parent->color = true;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = false;
}

template <typename T>
void RBT<T>::transplant(Node* u, Node* v){
    if (u->parent == NIL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

template <typename T>
bool RBT<T>::erase(const T& value){
    Node* z = root;
    while (z != NIL) {
        if (value < z->value)      z = z->left;
        else if (value > z->value) z = z->right;
        else break;
    }
    if (z == NIL) return false;

    Node* y = z;
    Node* x;
    bool yOriginal = y->color;

    if (z->left == NIL){
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == NIL){
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = treeMinimum(z->right);
        yOriginal = y->color;
        x = y->right;
        if (y != z->right){
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        else {
            x->parent = y;
        }
        transplant(z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z; 

    if (!yOriginal){
        deleteFixup(x);
    }
    return true;
}

template <typename T>
void RBT<T>::deleteFixup(Node* x){
    Node* w; // x's sibling
    while (x != root && !x->color){
        if (x == x->parent->left){ //case 1
            w = x->parent->right;
            if (w->color){
                w->color = false;
                x->parent->color = true;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if(!w->left->color && !w->right->color){ //case 2
                w->color = true;
                x = x->parent;
            }
            else {
                if (!w->right->color){ //case 3
                    w->left->color = false;
                    w->color = true;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color; //case 4
                x->parent->color = false;
                w->right->color = false;
                leftRotate(x->parent);
                x = root;
            }            
        }
       else {
        w = x->parent->left;
            if (w->color){
                w->color = false;
                x->parent->color = true;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if(!w->right->color && !w->left->color){
                w->color = true;
                x = x->parent;
            }
            else {
                if (!w->left->color){
                    w->right->color = false;
                    w->color = true;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = false;
                w->left->color = false;
                rightRotate(x->parent);
                x = root;
            } 
       } 
    }
    x->color = false;
}

template <typename T>
void RBT<T>::inorder() { inorderHelper(root); std::cout << "\n"; }

template <typename T>
void RBT<T>::inorderHelper(Node* node) {
    if (node == NIL) return;
    inorderHelper(node->left);
    std::cout << node->value << " ";
    inorderHelper(node->right);
}

template <typename T>
bool RBT<T>::search(const T& value) {
    Node* x = root;
    while (x != NIL) {
        if (value == x->value)      return true;
        else if (value < x->value)  x = x->left;
        else                        x = x->right;
    }
    return false;
}

template class RBT<int>;
