#include "StreamingDBa1.h"


using namespace std;


int main()
{
    Group* a = new Group(7703, false, 0);
    Group* b = new Group(6727, false, 0);
    Group* c = new Group(9143, false, 0);
    Group* d = new Group(2254, false, 0);

    Group* e = new Group(6567, false, 0);


    User* aa = new User(2494, false);
    User* bb = new User(1001, false);
    User* cc = new User(5369, false);
    User* dd = new User(5813, false);
    User* ee = new User(1706, false);
    User* ff = new User(2673, false);
    User* gg = new User(1912, false);
    User* hh = new User(6667, false);
    User* ii = new User(7624, false);
    User* jj = new User(1001, false);

    User* kk = new User(9744, false);


    streaming_database* database = new streaming_database();
    StatusType tmp;

    /*
    cout << endl << "now adding group e: " << e->getGroupId() << endl;
    tmp = database->add_group(e->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "group e: " << e->getGroupId() << " was successfully added" << endl;
    }
    else
    {
        cout << "group e: " << e->getGroupId() << " wasn't added" << endl;
    }
    cout << "this is the roots' id " << database->m_groups.getRoot()->getValue()->getGroupId() << endl;
    */

    /*
    cout << endl << "now adding user kk: " << kk->getId() << endl;
    tmp = database->add_user(kk->getId(), kk->getIsVip());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user kk: " << kk->getId() << " was successfully added" << endl;
    }
    else
    {
        cout << "user kk: " << kk->getId() << " wasn't added" << endl;
    }*/

    /*
    cout << endl << "now adding user kk: " << kk->getId() << " to group e: "<< e->getGroupId() << endl;
    tmp = database->add_user_to_group(kk->getId(), e->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user kk: " << kk->getId() << " was successfully added to group e: " <<e->getGroupId() << endl;
    }
    else
    {
        cout << "user kk: " << kk->getId() << " wasn't added to group e: " << e->getGroupId() << endl;
    }



    cout << endl << "now adding group a: " << a->getGroupId() << endl;
    
    tmp = database->add_group(a->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "group a: " << a->getGroupId() << " was successfully added" << endl;
    }
    else
    {
        cout << "group a: " << a->getGroupId() << " wasn't added" << endl;
    }
    cout << "this is the roots' id " << database->m_groups.getRoot()->getValue()->getGroupId()
    << " and this is its height: " << database->m_groups.getRoot()->getHeight() << endl;
    cout << "this is the roots' rights'  id " << database->m_groups.getRoot()->getRightNode()->getValue()->getGroupId()
    << " and this is its height: " << database->m_groups.getRoot()->getRightNode()->getHeight() << endl;

    cout << endl << "now adding group b: " << b->getGroupId() << endl;
    tmp = database->add_group(b->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "group b: " << b->getGroupId() << " was successfully added" << endl;
    }
    else
    {
        cout << "group b: " << b->getGroupId() << " wasn't added" << endl;
    }
    cout << endl << "this is the roots' id " << database->m_groups.getRoot()->getValue()->getGroupId()
            << " and this is its height: " << database->m_groups.getRoot()->getHeight()
            << " and this is its bf: " << database->m_groups.balanceFactor(database->m_groups.getRoot()) << endl;

    //cout << "this is the roots' rights'  id " << database->m_groups.getRoot()->getRightNode()->getValue()->getGroupId() << endl;
    cout << "this is the roots' lefts' id: " << database->m_groups.getRoot()->getLeftNode()->getValue()->getGroupId()
            << " and this is its height: " << database->m_groups.getRoot()->getLeftNode()->getHeight() << endl;
    cout << "this is the roots' right' id: " << database->m_groups.getRoot()->getRightNode()->getValue()->getGroupId()
         << " and this is its height: " << database->m_groups.getRoot()->getRightNode()->getHeight() << endl;
    //cout << "this is the roots' lefts' rights' id: " << database->m_groups.getRoot()->getLeftNode()->getRightNode()->getValue()->getGroupId()
           // <<" and this is its height: " << database->m_groups.getRoot()->getLeftNode()->getRightNode()->getHeight() << endl;


    */

    cout << endl << "now adding user aa: " << aa->getId() << endl;
    tmp = database->add_user(aa->getId(), aa->getIsVip());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user aa: " << aa->getId() << " was successfully added" << endl;
    }
    else
    {
        cout << "user aa: " << aa->getId() << " wasn't added" << endl;
    }

    cout << endl << "now removing user aa: " << aa->getId() << endl;////////////////might be a problem here
    tmp = database->remove_user(aa->getId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user aa: " << aa->getId() << " was successfully removed" << endl;
    }
    else
    {
        cout << "user aa: " << aa->getId() << " didnt exist or wasn't removed" << endl;
    }
    cout << endl << "this is the tree inorder:" << endl;
    database->m_users.inOrder(cout, database->m_users.getRoot());
    cout << endl;


    /*
    cout << endl << "now adding group c: " << c->getGroupId() << endl;
    tmp = database->add_group(c->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "group c: " << c->getGroupId() << " was successfully added" << endl;
    }
    else
    {
        cout << "group c: " << c->getGroupId() << " wasn't added" << endl;
    }
    //cout << "this is the roots' id " << database->m_groups.getRoot()->getValue()->getGroupId() << endl;
    //cout << "this is the roots' rights'  id " << database->m_groups.getRoot()->getRightNode()->getValue()->getGroupId() << endl;

    /*
    cout << endl << "now adding user aa: " << aa->getId() << " to group a: "<< a->getGroupId() << endl;
    tmp = database->add_user_to_group(aa->getId(), a->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user aa: " << aa->getId() << " was successfully added to group a: " <<a->getGroupId() << endl;
    }
    else
    {
        cout << "user aa: " << aa->getId() << " wasn't added to group a: " << a->getGroupId() << endl;
    }
    */
    cout << endl << "now adding user bb: " << bb->getId() << endl;
    tmp = database->add_user(bb->getId(), bb->getIsVip());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user bb: " << bb->getId() << " was successfully added" << endl;
    }
    else 
    {
        cout << "user bb: " << bb->getId() << " wasn't added" << endl;
    }

    cout << endl << "now adding user cc: " << cc->getId() << endl;
    tmp = database->add_user(cc->getId(), cc->getIsVip());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user cc: " << cc->getId() << " was successfully added" << endl;
    }
    else
    {
        cout << "user cc: " << cc->getId() << " wasn't added" << endl;
    }

    cout << endl << "now adding user dd: " << dd->getId() << endl;
    tmp = database->add_user(dd->getId(), dd->getIsVip());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user dd: " << dd->getId() << " was successfully added" << endl;
    }
    else
    {
        cout << "user dd: " << dd->getId() << " wasn't added" << endl;
    }


    cout << endl << "now adding user ee: " << ee->getId() << endl;
    tmp = database->add_user(ee->getId(), ee->getIsVip());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user ee: " << ee->getId() << " was successfully added" << endl;
    }
    else
    {
        cout << "user ee: " << ee->getId() << " wasn't added" << endl;
    }

    cout << endl << "now removing user dd: " << dd->getId() << endl;////////////////might be a problem here
    tmp = database->remove_user(dd->getId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user dd: " << dd->getId() << " was successfully removed" << endl;
    }
    else
    {
        cout << "user dd: " << dd->getId() << " didnt exist or wasn't removed" << endl;
    }
    cout << endl << "this is the tree inorder:" << endl;
    database->m_users.inOrder(cout, database->m_users.getRoot());
    cout << endl;

    cout << endl << "now adding user ff: " << ff->getId() << endl;
    tmp = database->add_user(ff->getId(), ff->getIsVip());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user ff: " << ff->getId() << " was successfully added" << endl;
    }
    else
    {
        cout << "user ff: " << ff->getId() << " wasn't added" << endl;
    }

    cout << endl << "now adding user gg: " << gg->getId() << endl;
    tmp = database->add_user(gg->getId(), gg->getIsVip());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user gg: " << gg->getId() << " was successfully added" << endl;
    }
    else
    {
        cout << "user gg: " << gg->getId() << " wasn't added" << endl;
    }
    /*
    cout << endl << "now adding user ee: " << ee->getId() << " to group c: "<< c->getGroupId() << endl;
    tmp = database->add_user_to_group(ee->getId(), c->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user ee: " << ee->getId() << " was successfully added to group c: " <<c->getGroupId() << endl;
    }
    else
    {
        cout << "user ee: " << ee->getId() << " wasn't added to group c: " << c->getGroupId() << endl;
    }

    cout << endl << "now adding group d: " << d->getGroupId() << endl;
    tmp = database->add_group(d->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "group d: " << d->getGroupId() << " was successfully added" << endl;
    }
    else
    {
        cout << "group d: " << d->getGroupId() << " wasn't added" << endl;
    }

    cout << endl << "now removing user bb: " << bb->getId() << endl;
    tmp = database->remove_user(bb->getId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user bb: " << bb->getId() << " was successfully removed" << endl;
    }
    else
    {
        cout << "user bb: " << bb->getId() << " didnt exist or wasn't removed" << endl;
    }
    cout << endl << "this is the tree inorder:" << endl;
    database->m_users.inOrder(cout, database->m_users.getRoot());
    cout << endl;

    cout << endl << "now removing group d: " << d->getGroupId() << endl;
    tmp = database->remove_group(d->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "group d: " << d->getGroupId() << " was successfully removed" << endl;
    }
    else
    {
        cout << "group d: " << d->getGroupId() << " didnt exist or wasn't removed" << endl;
    }
    cout << endl << "this is the tree inorder:" << endl;
    database->m_groups.inOrder(cout, database->m_groups.getRoot());
    cout << endl;

    cout << endl << "now removing group b: " << b->getGroupId() << endl;
    tmp = database->remove_group(b->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "group b: " << b->getGroupId() << " was successfully removed" << endl;
    }
    else
    {
        cout << "group b: " << b->getGroupId() << " didnt exist or wasn't removed" << endl;
    }
    cout << endl << "this is the tree inorder:" << endl;
    database->m_groups.inOrder(cout, database->m_groups.getRoot());
    cout << endl;

    cout << endl << "now adding user ff: " << ff->getId() << " to group a: "<< a->getGroupId() << endl;
    tmp = database->add_user_to_group(ff->getId(), a->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user ee: " << ff->getId() << " was successfully added to group a: " <<a->getGroupId() << endl;
    }
    else
    {
        cout << "user ee: " << ff->getId() << " wasn't added to group a: " << a->getGroupId() << endl;
    }

    cout << endl << "now adding user cc: " << cc->getId() << " to group c: "<< c->getGroupId() << endl;
    tmp = database->add_user_to_group(cc->getId(), c->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user cc: " << cc->getId() << " was successfully added to group c: " <<c->getGroupId() << endl;
    }
    else
    {
        cout << "user cc: " << cc->getId() << " wasn't added to group c: " << c->getGroupId() << endl;
    }

    cout << endl << "now adding user ff: " << ff->getId() << " to group a: " << a->getGroupId();
    tmp = database->add_user_to_group(ff->getId(), a->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user ff: " << ff->getId() << " was successfully added to group a: " <<a->getGroupId() << endl;
    }
    else
    {
        cout << "user ff: " << ff->getId() << " wasn't added to group a: " << a->getGroupId() << endl;
    }
    */
    cout << endl << "now adding user hh: " << hh->getId() << endl;
    tmp = database->add_user(hh->getId(), hh->getIsVip());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user hh: " << hh->getId() << " was successfully added" << endl;
    }
    else
    {
        cout << "user hh: " << hh->getId() << " wasn't added" << endl;
    }

    cout << endl << "now adding user ii: " << ii->getId() << endl;
    tmp = database->add_user(ii->getId(), ii->getIsVip());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user ii: " << ii->getId() << " was successfully added" << endl;
    }
    else
    {
        cout << "user ii: " << ii->getId() << " wasn't added" << endl;
    }

    cout << endl << "now adding user jj: " << jj->getId() << endl;
    tmp = database->add_user(jj->getId(), jj->getIsVip());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user jj: " << jj->getId() << " was successfully added" << endl;
    }
    else
    {
        cout << "user jj: " << jj->getId() << " wasn't added" << endl;
    }

    // should fail cause the group isn't here
    /*
    cout << endl << "now adding user jj: " << jj->getId() << " to group b: " << b->getGroupId() << endl;
    tmp = database->add_user_to_group(jj->getId(), b->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "user jj: " << jj->getId() << " was successfully added to group b: " <<b->getGroupId() << endl;
    }
    else
    {
        cout << "user jj: " << jj->getId() << " wasn't added to group b: " << b->getGroupId() << endl;
    }

    cout << endl << "now removing group b: " << b->getGroupId() << endl; // should fail
    tmp = database->remove_group(b->getGroupId());
    if (tmp == StatusType::SUCCESS)
    {
        cout << "group b: " << b->getGroupId() << " was successfully removed" << endl;
    }
    else
    {
        cout << "group b: " << b->getGroupId() << " didnt exist or wasn't removed" << endl;
    }
    cout << endl << "this is the tree inorder:" << endl;
    database->m_groups.inOrder(cout, database->m_groups.getRoot());
    cout << endl;
    */


    cout << endl << "test ended" << endl;
    return 0;
}

//at line 43 remove_group 3182