#include "rbtree.cpp"
#include <iostream>

int main() {
    RBT<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(5);
    tree.insert(1);
    tree.insert(25);
    std::cout << "After insertions: ";
    tree.inorder();

    std::cout << tree.erase(10) << "\n";
    std::cout << "After erasing 10: ";
    tree.inorder();

    std::cout << tree.erase(25) << "\n";
    std::cout << "After erasing 25: ";
    tree.inorder();

    std::cout << tree.erase(99) << "\n";

    std::cout << tree.erase(20) << "\n";
    std::cout << "After erasing 20: ";
    tree.inorder();

    return 0;
}
