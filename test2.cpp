#include "StreamingDBa1.h"

using namespace std;

int main()
{
    StatusType tmp = StatusType::FAILURE;
    streaming_database* database = new streaming_database();
    /*
    tmp = database->add_group(100);
    if(tmp == StatusType::SUCCESS)
    {
        cout << "add group was a success" << endl;
    }
    else
    {
        cout << "add group was a failure" << endl;
    }
    */

    tmp = database->add_user(200, false);
    if(tmp == StatusType::SUCCESS)
    {
        cout << "add user was a success" << endl;
    }
    else
    {
        cout << "add user was a failure" << endl;
    }


    tmp = database->add_movie(300, Genre::FANTASY, 0, false);
    if(tmp == StatusType::SUCCESS)
    {
        cout << "add movie was a success" << endl;
    }
    else
    {
        cout << "add movie was a failure" << endl;
    }

    tmp = database->add_movie(301, Genre::FANTASY, 0, false);
    if(tmp == StatusType::SUCCESS)
    {
        cout << "add movie was a success" << endl;
    }
    else
    {
        cout << "add movie was a failure" << endl;
    }

    tmp = database->add_movie(302, Genre::DRAMA, 0, false);
    if(tmp == StatusType::SUCCESS)
    {
        cout << "add movie was a success" << endl;
    }
    else
    {
        cout << "add movie was a failure" << endl;
    }



    /*
    output_t<int> out = database->get_all_movies_count(Genre::FANTASY);
    cout << "this is the number of fantasy movies added: " << out.ans() << endl;

    output_t<int> out2 = database->get_all_movies_count(Genre::DRAMA);
    cout << "this is the number of drama movies added: " << out2.ans() << endl;

    output_t<int> out3 = database->get_all_movies_count(Genre::NONE);
    cout << "this is the number of movies added: " << out3.ans() << endl;

    tmp = database->remove_movie(305);
    if(tmp == StatusType::SUCCESS)
    {
        cout << "remove movie was a success" << endl;
    }
    else
    {
        cout << "remove movie was a failure" << endl;
    }

    output_t<int> out4 = database->get_all_movies_count(Genre::FANTASY);
    cout << "this is the number of fantasy movies after removal: " << out4.ans() << endl;

    output_t<int> out5 = database->get_all_movies_count(Genre::DRAMA);
    cout << "this is the number of drama movies after removal: " << out5.ans() << endl;

    output_t<int> out6 = database->get_all_movies_count(Genre::NONE);
    cout << "this is the number of movies after removal: " << out6.ans() << endl;

     */
    /*
    tmp = database->rate_movie(200, 300, 70);
    if(tmp == StatusType::SUCCESS)
    {
        cout << "rate movie was a success" << endl;
    }
    else
    {
        cout << "rate movie was a failure" << endl;
    }
    */


    int* output = new int[3];

    for(int index = 0; index < 3; ++index)
    {
        output[index] = -1;
    }

    tmp = database->get_all_movies(Genre::NONE, output);
    if(tmp == StatusType::SUCCESS)
    {
        cout << "get all movies was a success" << endl;
    }
    else
    {
        cout << "get all movies was a failure" << endl;
    }

    cout << "this is the roots id: " << database->m_movies.getRoot()->getValue()->getMovieId();
    cout << " and this is its rating: " << database->m_movies.getRoot()->getValue()->getRating() << endl;

    cout << "this is the roots' right nodes' id: " << database->m_movies.getRoot()->getRightNode()->getValue()->getMovieId();
    cout << " and this is its rating: " << database->m_movies.getRoot()->getRightNode()->getValue()->getRating() << endl;

    cout << "this is the roots' left nodes' id: " << database->m_movies.getRoot()->getLeftNode()->getValue()->getMovieId();
    cout << " and this is its rating: " << database->m_movies.getRoot()->getLeftNode()->getValue()->getRating() << endl;

    database->m_movies.getRoot()->getValue()->setFlag(true);
    database->m_movies.getRoot()->getRightNode()->getValue()->setFlag(true);

    Movie* movie300 =  database->m_movies.getRoot()->getRightNode()->getValue();
    Movie* movie301 =  database->m_movies.getRoot()->getValue();

    bool bigger = *movie300 > *movie301;
    cout << "the movie 300 is bigger than 301: " << bigger << endl;

    cout << endl << "these are the movies: " << endl;
    for(int index = 0; index < 3; ++index)
    {
        cout << output[index] << " " << endl;
    }
    delete[] output;


    /*
    tmp = database->add_user(2494, false);
    if(tmp == StatusType::SUCCESS)
    {
        cout << "add user was a success" << endl;
    }
    else
    {
        cout << "add user was a failure" << endl;
    }

    cout <<"now removing user 2494" << endl;
    tmp = database->remove_user(2494);
    if(tmp == StatusType::SUCCESS)
    {
        cout << "remove user was a success" << endl;
    }
    else
    {
        cout << "remove user was a failure" << endl;
    }*/


    cout << endl << "ended" << endl;

    return 0;
}

