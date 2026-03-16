#include "binarytree.cpp"
#include <iostream>

int main()
{
    BinaryTree<int> tree;
    tree.insert(13);
    tree.insert(4);
    tree.insert(10);
    tree.insert(70);
    tree.insert(30);
    tree.insert(27);
    tree.insert(54);
    tree.insert(78);
    tree.insert(67);

    std::cout << "In order: ";
    tree.inOrderTraversal();
    std::cout << "\n";

    std::cout << "Pre-order:  ";
    tree.preOrderTraversal();
    std::cout << "\n";

    std::cout << "Post-order: ";
    tree.postOrderTraversal();
    std::cout << "\n";

    std::cout << "Before erase 30:\n";
    tree.inOrderTraversal(); std::cout << "\n";

    tree.erase(30);

    std::cout << "After erase 30:\n";
    tree.inOrderTraversal(); std::cout << "\n"; 

    std::cout << "Maximum depth: " << tree.depth() << "\n";   // 3

    return 0;
}
