#include "StreamingDBa1.h"
#include <iostream>
 using namespace std;

int main()
{
    /*
    User* num = new User(9405, true);
    User* a = new User(4417, true);
    User* b = new User(876, true);
    User* c = new User(1359, true);
    User* d = new User(6203, true);
    User* e = new User(3366, true);
    User* f = new User(2653, false);
    User* g = new User(1083, false);
    User* h = new User(4491, false);
    User* i = new User(1083, false);
    User* j = new User(4493, true);
    User* k = new User(3442, false);
     */
    User* aa = new User(8287, true);
    /*
    User* bb = new User(3325, true);
    User* cc = new User(2224, false);
    User* dd = new User(9839, true);
    User* ee = new User(6235, true);
    User* ff = new User(9324, true);
    User* gg = new User(8272, false);*/

    Movie* a = new Movie(5077, 27, true, Genre::ACTION);
    Movie* b = new Movie(8180, 12, false, Genre::ACTION);


    streaming_database* database = new streaming_database();

    cout << "now adding user aa: " << aa->getId() << endl;
    StatusType tmpStatus = database->add_user(aa->getId(), aa->getIsVip());
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "add user was a success" << endl;
    }
    else
    {
        cout << "add user was a failure" << endl;
    }

    cout <<endl <<  "now adding movie: " << a->getMovieId() << endl;
    tmpStatus = database->add_movie(a->getMovieId(), a->getGenre(), a->getViews(), a->getVipOnly());
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "the movie: " << a->getMovieId() << " was added successfully" << endl;
    }
    else
    {
        cout << "the movie: " << a->getMovieId() << " wasn't added" << endl;
    }

    cout <<endl <<  "now adding movie: " << b->getMovieId() << endl;
    tmpStatus = database->add_movie(b->getMovieId(), b->getGenre(), b->getViews(), b->getVipOnly());
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "the movie: " << b->getMovieId() << " was added successfully" << endl;
    }
    else
    {
        cout << "the movie: " << b->getMovieId() << " wasn't added" << endl;
    }

    cout << "now getting all movies count by genre action" << endl;
    output_t<int> tmpOutput = database->get_all_movies_count(Genre::ACTION);
    if(tmpOutput.status() == StatusType::SUCCESS)
    {
        cout << "the movie count is: " << tmpOutput.ans() << endl;
    }
    else
    {
        cout << "get movies count was a failure" << endl;
    }

    /*tmpStatus = database->rate_movie(aa->getId(), a->getMovieId(), 136);
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "rate movie was a success" << endl;
    }
    else
    {
        cout << "rate movie was a failure" << endl;
    }


    cout << "this is the movies roots' id: " << database->m_movies.getRoot()->getValue()->getMovieId() << endl;
    cout << "this is the roots' right' id: " << database->m_movies.getRoot()->getRightNode()->getValue()->getMovieId() << endl;

    cout <<endl <<  "now remove movie: " << a->getMovieId() << endl;
    tmpStatus = database->remove_movie(a->getMovieId());
    if(tmpStatus == StatusType::SUCCESS)
    {
        cout << "the movie: " << a->getMovieId() << " was remove successfully" << endl;
    }
    else
    {
        cout << "the movie: " << a->getMovieId() << " wasn't removed" << endl;
    }

    cout << "this is the movies roots' id: " << database->m_movies.getRoot()->getValue()->getMovieId() << endl;
    //cout << "this is the roots' left' id: " << database->m_movies.getRoot()->getRightNode()->getValue()->getMovieId() << endl;
    */
    cout << endl << "ended" << endl;
    return 0;
}