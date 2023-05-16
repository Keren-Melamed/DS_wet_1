#include "AVLTree.h"
 using namespace std;

int main()
{
    int num = 13;
    //int num = 50, a = 30, b = 20, c = 40, d = 70, e = 60, f = 80;
    int a = 10, b = 15, c = 5, d = 11, e = 4, f = 8, g = 16, h = 6, i = 7, j = 31, k = 463;
    int aa = 28, bb = 51, cc = 119, dd = 97, ee = 50, ff = 3, gg = 238;
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

    cout << endl << "now inserting "<< h << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), h));

    cout << endl << "now inserting "<< i << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), i));

    cout << endl << "now inserting "<< j << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), j));

    cout << endl << "now inserting "<< k << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), k));

    cout << endl << "now inserting "<< aa << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), aa));

    cout << endl << "now inserting "<< bb << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), bb));

    cout << endl << "now inserting "<< cc << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), cc));

    cout << endl << "now inserting "<< dd << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), dd));

    cout << endl << "now inserting "<< ee << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), ee));

    cout << endl << "now inserting "<< ff << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), ff));

    cout << endl << "now inserting "<< gg << endl;
    tree.setRoot(tree.insertValue(tree.getRoot(), gg));

    cout << endl << "this is the tree inorder:" << endl;
    tree.inOrder(cout, tree.getRoot());
    cout << endl;

    cout << endl <<"this is the tree preorder:" << endl; 
    tree.preOrder(cout, tree.getRoot());
    cout << endl;


    cout << endl << "now removing: " << b << endl;

    tree.setRoot(tree.removeValue(tree.getRoot(), b));
    cout << endl << "this is the tree inorder:" << endl;
    tree.inOrder(cout, tree.getRoot());
    cout << endl;

    cout << endl <<"this is the tree preorder:" << endl;
    tree.preOrder(cout, tree.getRoot());
    cout << endl;


    cout << endl << "now removing: " << c << endl;

    tree.setRoot(tree.removeValue(tree.getRoot(), c));
    cout << endl << "this is the tree inorder:" << endl;
    tree.inOrder(cout, tree.getRoot());
    cout << endl;

    cout << endl <<"this is the tree preorder:" << endl;
    tree.preOrder(cout, tree.getRoot());
    cout << endl;

    cout << endl << "now removing: " << num << endl;

    tree.setRoot(tree.removeValue(tree.getRoot(), num));
    cout << endl << "this is the tree inorder:" << endl;
    tree.inOrder(cout, tree.getRoot());
    cout << endl;

    cout << endl <<"this is the tree preorder:" << endl;
    tree.preOrder(cout, tree.getRoot());
    cout << endl;

    cout << endl << "now removing: " << bb << endl;

    tree.setRoot(tree.removeValue(tree.getRoot(), bb));
    cout << endl << "this is the tree inorder:" << endl;
    tree.inOrder(cout, tree.getRoot());
    cout << endl;

    cout << endl <<"this is the tree preorder:" << endl;
    tree.preOrder(cout, tree.getRoot());
    cout << endl;

    cout << "looking for 20" << endl;
    Node<int>* foundIt = tree.findObject(tree.getRoot(), 20);
    if (foundIt != nullptr)
    {
        cout << "this is the value found: " << foundIt->getValue() << endl;
    }
    else
    {
        cout << "the value isn't in the tree" << endl;
    }
    delete foundIt;

    /*cout << endl << "this is the root's height: " << tree.getRoot()->getHeight() << endl;
    cout << "this is the root's right node's height: " << tree.getRoot()->getRightNode()->getHeight() << endl;
    cout << "this is the root's right node's X 2 height: " << tree.getRoot()->getRightNode()->getRightNode()->getHeight() << endl;
    cout << "this is the root's right node's X 2 left node's height: " << tree.getRoot()->getRightNode()->getRightNode()->getLeftNode()->getHeight() << endl;
    cout << "this is the root's right node's X 2 lefts' right's height: " << tree.getRoot()->getRightNode()->getRightNode()->getLeftNode()->getRightNode()->getHeight() << endl;

    cout << endl << "this is the root's bf: " << tree.balanceFactor(tree.getRoot()) << endl;
    cout << "this is the root's right node's bf: " << tree.balanceFactor(tree.getRoot()->getRightNode()) << endl;
    cout << "this is the root's right node's X 2 bf: " << tree.balanceFactor(tree.getRoot()->getRightNode()->getRightNode()) << endl;
    cout << "this is the root's right node's X 2 left node's bf: " << tree.balanceFactor(tree.getRoot()->getRightNode()->getRightNode()->getLeftNode()) << endl;
    cout << "this is the root's right node's X 2 lefts' right's bf: " << tree.balanceFactor(tree.getRoot()->getRightNode()->getRightNode()->getLeftNode()->getRightNode()) << endl;
    */
     return 0;
}