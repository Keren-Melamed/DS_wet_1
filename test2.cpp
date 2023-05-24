#include "StreamingDBa1.h"

using namespace std;

int main()
{
    StatusType tmp = StatusType::FAILURE;
    streaming_database* database = new streaming_database();
    tmp = database->add_group(100);
    if(tmp == StatusType::SUCCESS)
    {
        cout << "add group was a success" << endl;
    }
    else
    {
        cout << "add group was a failure" << endl;
    }

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

    int* output = new int[3];
    cout << "output was allocated" << endl;

    for(int index = 0; index < 3; ++index)
    {
        output[index] = -1;
    }
    cout << "output was initialized to -1" << endl;

    database->get_all_movies(Genre::NONE, output);
    cout << "get all movies has finished" << endl;

    for(int index = 0; index < 3; ++index)
    {
        cout << output[index] << " ";
    }
    cout << endl << "ended" << endl;
    return 0;
}
