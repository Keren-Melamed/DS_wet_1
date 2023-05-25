#include "StreamingDBa1.h"

using namespace std;

int main()
{
    User* a = new User(1000, false);

    Movie* aa = new Movie(2000, 0, false, Genre::ACTION);
    Movie* bb = new Movie(2001, 27, true, Genre::ACTION);
    Movie* cc = new Movie(2002, 12, false, Genre::COMEDY);
    Movie* dd = new Movie(2003, 42, true, Genre::COMEDY);
    Movie* ee = new Movie(2004, 17, false, Genre::COMEDY);
    Movie* ff = new Movie(2005, 22, false, Genre::COMEDY);
    Movie* gg = new Movie(2006, 81, true, Genre::DRAMA);




    Group* aaa = new Group(3000, false, 0);


    StatusType tmpStatus = StatusType::FAILURE;
    streaming_database* database = new streaming_database();

    cout << endl << "now adding user a: " << a->getId() << endl;
    tmpStatus = database->add_user(a->getId(), a->getIsVip());
    if (tmpStatus == StatusType::SUCCESS)
    {
        cout << "user a: " <<a->getId() << " was successfully added" << endl;
    }
    else
    {
        cout << "user a: " << a->getId() << " wasn't added" << endl;
    }

    cout <<endl <<  "now adding movie aa: " << aa->getMovieId() << endl;
    tmpStatus = database->add_movie(aa->getMovieId(), aa->getGenre(), aa->getViews(), aa->getVipOnly());
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "the movie: " << aa->getMovieId() << " was added successfully" << endl;
    }
    else
    {
        cout << "the movie: " << aa->getMovieId() << " wasn't added" << endl;
    }

    cout <<endl <<  "now adding movie bb: " << bb->getMovieId() << endl;
    tmpStatus = database->add_movie(bb->getMovieId(), bb->getGenre(), bb->getViews(), bb->getVipOnly());
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "the movie: " << bb->getMovieId() << " was added successfully" << endl;
    }
    else
    {
        cout << "the movie: " << bb->getMovieId() << " wasn't added" << endl;
    }

    cout <<endl <<  "now adding movie cc: " << cc->getMovieId() << endl;
    tmpStatus = database->add_movie(cc->getMovieId(), cc->getGenre(), cc->getViews(), cc->getVipOnly());
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "the movie: " << cc->getMovieId() << " was added successfully" << endl;
    }
    else
    {
        cout << "the movie: " << cc->getMovieId() << " wasn't added" << endl;
    }

    cout <<endl <<  "now adding movie dd: " << dd->getMovieId() << endl;
    tmpStatus = database->add_movie(dd->getMovieId(), dd->getGenre(), dd->getViews(), dd->getVipOnly());
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "the movie: " << dd->getMovieId() << " was added successfully" << endl;
    }
    else
    {
        cout << "the movie: " << dd->getMovieId() << " wasn't added" << endl;
    }

    cout <<endl <<  "now adding movie ee: " << ee->getMovieId() << endl;
    tmpStatus = database->add_movie(ee->getMovieId(), ee->getGenre(), ee->getViews(), ee->getVipOnly());
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "the movie: " << ee->getMovieId() << " was added successfully" << endl;
    }
    else
    {
        cout << "the movie: " << ee->getMovieId() << " wasn't added" << endl;
    }

    cout <<endl <<  "now adding movie ff: " << ff->getMovieId() << endl;
    tmpStatus = database->add_movie(ff->getMovieId(), ff->getGenre(), ff->getViews(), ff->getVipOnly());
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "the movie: " << ff->getMovieId() << " was added successfully" << endl;
    }
    else
    {
        cout << "the movie: " << ff->getMovieId() << " wasn't added" << endl;
    }

    cout <<endl <<  "now adding movie gg: " << gg->getMovieId() << endl;
    tmpStatus = database->add_movie(gg->getMovieId(), gg->getGenre(), gg->getViews(), gg->getVipOnly());
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "the movie: " << gg->getMovieId() << " was added successfully" << endl;
    }
    else
    {
        cout << "the movie: " << gg->getMovieId() << " wasn't added" << endl;
    }

    cout << endl << "now adding group aaa: " << aaa->getGroupId() << endl;
    tmpStatus = database->add_group(aaa->getGroupId());
    if (tmpStatus == StatusType::SUCCESS)
    {
        cout << "group aaa: " << aaa->getGroupId() << " was successfully added" << endl;
    }
    else
    {
        cout << "group aaa: " << aaa->getGroupId() << " wasn't added" << endl;
    }

    cout << endl << "now adding user a: " << a->getId() << " to group aaa: "<< aaa->getGroupId() << endl;
    tmpStatus = database->add_user_to_group(a->getId(), aaa->getGroupId());
    if (tmpStatus == StatusType::SUCCESS)
    {
        cout << "user a: " << a->getId() << " was successfully added to group aaa: " <<aaa->getGroupId() << endl;
    }
    else
    {
        cout << "user a: " << a->getId() << " wasn't added to group aaa: " << aaa->getGroupId() << endl;
    }

    cout << endl <<"now rating movie aa: " << aa->getMovieId() << endl;
    tmpStatus = database->rate_movie(a->getId(), aa->getMovieId(), 80);
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "movie aa: " << aa->getMovieId() << " was rated successfully" << endl;
    }
    else
    {
        cout << "movie aa: " << aa->getMovieId() << " was not rated" << endl;
    }

    cout << endl << "user a: " << a->getId() << " is now watching movie aa: " << aa->getMovieId() << endl;
    tmpStatus = database->user_watch(a->getId(), aa->getMovieId());
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "movie aa: " << aa->getMovieId() << " was successfully watched by user a: " << a->getId() << endl;
    }
    else
    {
        cout << "movie aa: " << aa->getMovieId() << " was not watched by user a: " << a->getId() << endl;
    }

    cout << endl <<"group aaa: " << aaa->getGroupId() << " is now watching movie aa: " << aa->getMovieId() << endl;
    tmpStatus = database->group_watch(aaa->getGroupId(), aa->getMovieId());
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "movie aa: " << aa->getMovieId() << " was successfully watched by group aaa: " << aaa->getGroupId() << endl;
    }
    else
    {
        cout << "movie aa: " << aa->getMovieId() << " was not watched by group aaa: " << aaa->getGroupId() << endl;
    }

    cout << endl << "getting num of views in all movies for a: "<< a->getId() << endl;
    output_t<int> tmpOut = database->get_num_views(a->getId(), Genre::NONE);
    if(tmpOut.status() == StatusType::SUCCESS)
    {
        cout << "num of views was received and its: " << tmpOut.ans() << endl;
    }
    else
    {
        cout << "num of views was not received..." << endl;
    }

    cout << endl << "getting all comedy movies count = Genre comedy" << endl;
    output_t<int> tmpOut0 = database->get_all_movies_count(Genre::COMEDY);
    if(tmpOut0.status() == StatusType::SUCCESS)
    {
        cout << "num of all comedy movies was received and its: " << tmpOut0.ans() << endl;
    }
    else
    {
        cout << "num of comedy movies was not received..." << endl;
    }

    cout << endl << "getting all drama movie count = Genre drama" << endl;
    output_t<int> tmpOut1 = database->get_all_movies_count(Genre::DRAMA);
    if(tmpOut1.status() == StatusType::SUCCESS)
    {
        cout << "num of all drama movies was received and its: " << tmpOut1.ans() << endl;
    }
    else
    {
        cout << "num of all drama movies was not received..." << endl;
    }

    cout << endl << "getting all action movie count = Genre action" << endl;
    output_t<int> tmpOut2 = database->get_all_movies_count(Genre::ACTION);
    if(tmpOut2.status() == StatusType::SUCCESS)
    {
        cout << "num of all action movies was received and its: " << tmpOut2.ans() << endl;
    }
    else
    {
        cout << "num of all action was not received..." << endl;
    }

    cout << endl << "getting all fantasy count = Genre fantasy" << endl;
    output_t<int> tmpOut3 = database->get_all_movies_count(Genre::FANTASY);
    if(tmpOut3.status() == StatusType::SUCCESS)
    {
        cout << "num of all fantasy movies was received and its: " << tmpOut3.ans() << endl;
    }
    else
    {
        cout << "num of all fantasy movies was not received..." << endl;
    }

    cout << endl << "getting ALL movie count = Genre NONE" << endl;
    output_t<int> tmpOut4 = database->get_all_movies_count(Genre::NONE);
    if(tmpOut4.status() == StatusType::SUCCESS)
    {
        cout << "num of ALL movies was received and its: " << tmpOut4.ans() << endl;
    }
    else
    {
        cout << "num of ALL movies was not received..." << endl;
    }

    cout << endl << "this is the movie tree inorder:" << endl;
    database->m_movies.preOrder(cout, database->m_movies.getRoot());

    cout << endl << "this is the comedy movie tree inorder:" << endl;
    database->m_comedy_movies.preOrder(cout, database->m_movies.getRoot());

    cout << endl << "this is the movie tree inorder:" << endl;
    database->m_action_movies.preOrder(cout, database->m_movies.getRoot());

    cout << endl << "this is the movie tree inorder:" << endl;
    database->m_movies.preOrder(cout, database->m_movies.getRoot());

    cout << endl << "this is the movie tree inorder:" << endl;
    database->m_movies.preOrder(cout, database->m_movies.getRoot());




    delete a;

    delete aa;
    delete bb;
    delete cc;
    delete dd;
    delete ee;
    delete ff;
    delete gg;

    delete aaa;
    delete database;
    cout << endl << "ended" << endl;
    return 0;
}

