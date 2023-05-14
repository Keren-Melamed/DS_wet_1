#include "AVLTree.h"
 using namespace std;

void printThis(ostream& os, int num)
{
    os << num <<endl;
}

int main()
{
    int num = 13;
    //int num = 0;
    int a = 10, b = 15, c = 5, d = 11, e = 4, f = 8, g = 16;
    //int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;//, g = 16;

    Node<int> node(num);

    AVLTree<int> tree(node);
    
    cout << endl << "now inserting "<< a << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), a));
    
    cout << endl << "now inserting "<< b << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), b));
    
    cout << endl << "now inserting "<< c << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), c));
    
    cout << endl << "now inserting "<< d << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), d));
    
    cout << endl << "now inserting "<< e << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), e));

    cout << endl << "now inserting "<< f << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), f));
    
    cout << endl << "now inserting "<< g << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), g));

    cout << "this is the tree inorder:" << endl; 
    tree.inOrder(cout, tree.getRoot());
    cout << endl;

    cout << "this is the tree preorder:" << endl; 
    tree.preOrder(cout, tree.getRoot());
    cout << endl;

    cout << "this is the tree postorder:" << endl; 
    tree.postOrder(cout, tree.getRoot());
    cout << endl;


    //tree.printTheTree();
    
    return 0;
}