#pragma once

template <typename T>
class RBT {
public:
    RBT();
    ~RBT();

    void insert(const T& value);
    bool erase(const T& value);
    bool search(const T& value);
private:
    struct Node {
        T value;
        Node* parent = nullptr;
        Node* left   = nullptr;
        Node* right  = nullptr;
        bool  color;           // true = red, false = black

        Node(const T& val, bool col = true)
            : value(val), parent(nullptr), left(nullptr), right(nullptr), color(col) {}
    };

public:
    void leftRotate(Node* x);
    void rightRotate(Node* y);

    void insertFixup(Node* z);
    void transplant(Node* u, Node* v);
    void deleteFixup(Node* x);
    void inorder();
    void inorderHelper(Node* node);

private:
    Node* NIL = nullptr;
    Node* root = nullptr;

    void destroy(Node* node);
    Node* treeMinimum(Node* x) {
        while (x->left != NIL)
            x = x->left;
        return x;
    }
};
