#include "AVLTree.h"
#include "User.h"
#include "Group.h"

using namespace std;


int main()
{
    Group* a = new Group(3906, false, 0);
    Group* b = new Group(3182, false, 0);
    Group* c = new Group(8180, false, 0);
    Group* d = new Group(2254, false, 0);


    User* aa = new User(5740, false);
    User* bb = new User(5046, true);
    User* gg = new User(5450, true);
    User* cc = new User(3655, true);
    User* dd = new User(6007, true);
    User* ee = new User(5973, false);
    User* ff = new User(1211, false);
    User* hh = new User(3931, true);
    User* ii = new User(188, false);
    User* jj = new User(2013, false);




    AVLTree<Group> groupTree;
    AVLTree<User> userTree;

    cout << endl << "now adding group a: " << a->getGroupId() << endl;
    groupTree.setRoot(groupTree.insertValue(groupTree.getRoot(), a));

    cout << endl << "now adding group b: " << b->getGroupId() << endl;
    groupTree.setRoot(groupTree.insertValue(groupTree.getRoot(), b));

    cout << endl << "now adding user aa: " << aa->getId() << endl;
    userTree.setRoot(userTree.insertValue(userTree.getRoot(), aa));

    cout << endl << "now adding user aa: " << aa->getId() << " to group a: "<< a->getGroupId() << endl;
    a->getMembers()->setRoot(a->getMembers()->insertValue(a->getMembers()->getRoot(), aa));

    cout << endl << "now adding user bb: " << bb->getId() << endl;
    userTree.setRoot(userTree.insertValue(userTree.getRoot(), bb));

    cout << endl << "now removing user aa: " << aa->getId() << endl;////////////////might be a problem here
    userTree.setRoot(userTree.removeValue(userTree.getRoot(), aa));
    cout << endl << "this is the tree inorder:" << endl;
    userTree.inOrder(cout, userTree.getRoot());
    cout << endl;

    cout << endl << "now adding user gg: " << gg->getId() << endl;
    userTree.setRoot(userTree.insertValue(userTree.getRoot(), gg));

    cout << endl << "now adding user cc: " << cc->getId() << endl;
    userTree.setRoot(userTree.insertValue(userTree.getRoot(), cc));

    cout << endl << "now adding user dd: " << dd->getId() << endl;
    userTree.setRoot(userTree.insertValue(userTree.getRoot(), dd));

    cout << endl << "now adding user ee: " << ee->getId() << endl;
    userTree.setRoot(userTree.insertValue(userTree.getRoot(), ee));

    cout << endl << "now adding user ff: " << ff->getId() << endl;
    userTree.setRoot(userTree.insertValue(userTree.getRoot(), ff));

    cout << endl << "now adding group c: " << c->getGroupId() << endl;
    groupTree.setRoot(groupTree.insertValue(groupTree.getRoot(), c));

    cout << endl << "now adding user ee: " << ee->getId() << " to group c: "<< c->getGroupId() << endl;
    c->getMembers()->setRoot(c->getMembers()->insertValue(c->getMembers()->getRoot(), ee));

    cout << endl << "now adding group d: " << d->getGroupId() << endl;
    groupTree.setRoot(groupTree.insertValue(groupTree.getRoot(), d));

    cout << endl << "now removing user bb: " << bb->getId() << endl;
    userTree.setRoot(userTree.removeValue(userTree.getRoot(), bb));
    cout << endl << "this is the tree inorder:" << endl;
    userTree.inOrder(cout, userTree.getRoot());
    cout << endl;

    cout << endl << "now removing group d: " << d->getGroupId() << endl;
    groupTree.setRoot(groupTree.removeValue(groupTree.getRoot(), d));
    cout << endl << "this is the tree inorder:" << endl;
    groupTree.inOrder(cout, groupTree.getRoot());
    cout << endl;

    cout << endl << "now removing group b: " << b->getGroupId() << endl;
    groupTree.setRoot(groupTree.removeValue(groupTree.getRoot(), b));
    cout << endl << "this is the tree inorder:" << endl;
    groupTree.inOrder(cout, groupTree.getRoot());
    cout << endl;

    cout << endl << "now adding user ff: " << ff->getId() << " to group a: "<< a->getGroupId() << endl;
    a->getMembers()->setRoot(a->getMembers()->insertValue(a->getMembers()->getRoot(), ff));

    cout << endl << "now adding user cc: " << cc->getId() << " to group c: "<< c->getGroupId() << endl;
    c->getMembers()->setRoot(c->getMembers()->insertValue(c->getMembers()->getRoot(), cc));

    try {
        cout << endl << "now adding user ff: " << ff->getId() << " to group a: " << a->getGroupId()
             << endl;//need to check
        userTree.findObject(userTree.getRoot(), ff);
        groupTree.findObject(groupTree.getRoot(), a);
        a->getMembers()->setRoot(a->getMembers()->insertValue(a->getMembers()->getRoot(), ff));
    }
    catch(NodeAlreadyExists& e)
    {
        cout << "user was already in group" << endl;
    }
    cout << endl << "now adding user hh: " << hh->getId() << endl;
    userTree.setRoot(userTree.insertValue(userTree.getRoot(), hh));

    cout << endl << "now adding user ii: " << ii->getId() << endl;
    userTree.setRoot(userTree.insertValue(userTree.getRoot(), ii));

    try { // should fail cause the group isn't here
        cout << endl << "now adding user jj: " << jj->getId() << " to group b: " << b->getGroupId() << endl;
        userTree.findObject(userTree.getRoot(), jj);
        groupTree.findObject(groupTree.getRoot(), b);
        b->getMembers()->setRoot(b->getMembers()->insertValue(b->getMembers()->getRoot(), jj));
    }
    catch(NodeDoesntExist& e)
    {
        cout << "the user or the group dont exist" << endl;
    }

    try {
        cout << endl << "now removing group b: " << b->getGroupId() << endl; // should fail
        groupTree.findObject(groupTree.getRoot(), b);
        groupTree.setRoot(groupTree.removeValue(groupTree.getRoot(), b));
    }
    catch(NodeDoesntExist& e)
    {
        cout << "the group doesnt exist" << endl;
    }

    cout << endl << "this is the tree inorder:" << endl;
    groupTree.inOrder(cout, groupTree.getRoot());
    cout << endl;


    return 0;
}

