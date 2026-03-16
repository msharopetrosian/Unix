#pragma once

template <typename T>
class BinaryTree
{
    public:
    BinaryTree() : d_root(nullptr){}
    bool insert(const T& value);
    bool erase(const T& value);
    void inOrderTraversal() const;
    void preOrderTraversal() const;
    void postOrderTraversal() const;
    int depth() const;
    private:
    struct Node{
        Node* left = nullptr;
        Node* right = nullptr;
        T value;

        Node(const T& val) : value(val) {}
    };

    void destroy(Node* node);
    void inOrderTraversalHelper(const Node* root) const;
    void preOrderTraversalHelper(const Node* root) const;
    void postOrderTraversalHelper(const Node* root) const;
    int depthHelper(const Node* node) const;

    Node* eraseHelper(Node* node, const T& value);
    Node* findMinNode(Node* node) const;
    private:
    Node* d_root;
};
