#include "AVLTree.h"


void printThis(std::ostream& os, int num)
{
    os << num <<std::endl;
}

int main()
{
    AVLTree<int> tree;
    tree.insertValue(tree.getRoot(), 1);
    tree.insertValue(tree.getRoot(), 2);
    tree.insertValue(tree.getRoot(), 3);
    tree.insertValue(tree.getRoot(), 4);
    tree.insertValue(tree.getRoot(), 5);
    tree.insertValue(tree.getRoot(), 6);

    printThis(std::cout, 5);
    
    std::cout << "this is the tree inorder:" << std::endl; 
    tree.inOrder(std::cout, tree.getRoot());

    std::cout << "this is the tree postorder:" << std::endl; 
    tree.postOrder(std::cout, tree.getRoot());

    std::cout << "this is the tree preorder:" << std::endl; 
    tree.preOrder(std::cout, tree.getRoot());

    return 0;
}