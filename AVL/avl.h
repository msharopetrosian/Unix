#pragma once

template <typename T>
class AVL
{
    public:
    AVL() : root(nullptr){}
    ~AVL();
    bool insert(const T& value);
    bool erase(const T& value);
    bool search(const T& value);
    void inOrderTraversal() const;
    void preOrderTraversal() const;
    void postOrderTraversal() const;
    int depth() const;
    private:
    struct Node{
        Node* left = nullptr;
        Node* right = nullptr;
        T value;
        int height = 1;

        Node(const T& val) : value(val), height(1) {}
    };

    int height(const Node* node) const;
    int balanceFactor(const Node* node) const;
    void updateHeight(Node* node);

    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insertRecursive(Node* node, const T& value, bool& inserted);
    Node* eraseRecursive(Node* node, const T& value, bool& removed);
    void inOrderTraversalHelper(const Node* root) const;

    void preOrderTraversalHelper(const Node* root) const;
    void postOrderTraversalHelper(const Node* root) const;
    int depthHelper(const Node* node) const;
    private:
    Node* root;
    void destroy(Node* node);
};
