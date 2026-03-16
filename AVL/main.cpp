#include "avl.cpp"
#include <iostream>

int main()
{
    AVL<int> tree;

    int values[] = {13, 4, 10, 70, 30, 27, 54, 78, 67};
    for (int v : values) {
        bool inserted = tree.insert(v);
        std::cout << "Inserted " << v << " → " << (inserted ? "yes" : "no (duplicate)") << "\n";
    }

    std::cout << "\nIn order:    ";
    tree.inOrderTraversal();
    std::cout << "\n";

    std::cout << "Pre-order:   ";
    tree.preOrderTraversal();
    std::cout << "\n";

    std::cout << "Post-order:  ";
    tree.postOrderTraversal();
    std::cout << "\n";

    std::cout << "Max depth:   " << tree.depth() << "\n";

     tree.erase(30);
    std::cout << "After erase 30 → depth = " << tree.depth() << "\n";

    return 0;
}
