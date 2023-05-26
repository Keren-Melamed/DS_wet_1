#include <iostream>
#include "StreamingDBa1.h"

void get_all_movies_aux(streaming_database *obj, int genre);
void my_query_get_all_movies_aux(streaming_database *obj, Genre genre);

void get_all_movies_aux(streaming_database *obj, int genre) {
    //cout<<"get all movies genre "<< genre << endl;
    my_query_get_all_movies_aux(obj, static_cast<Genre>(genre));
}

void add_movie_aux(streaming_database *obj, int movieId, int genre, int views, bool isVip) {
    //cout<<"add movie "<<movieId<<" to genre "<< genre << endl;
    obj->add_movie(movieId, static_cast<Genre>(genre), views, isVip);
}

void get_num_views_aux(streaming_database *obj, int movieId, int genre) {
    //cout<<"get num views "<<movieId << endl;
    output_t<int> count = obj->get_num_views(movieId, static_cast<Genre>(genre));
    std::cout << count.ans() << std::endl;
}

void get_all_movies_count_aux(streaming_database *obj, int genre) {
    //cout<<"get all movies count of genre "<< genre <<" " << endl;
    cout<< (obj->get_all_movies_count(static_cast<Genre>(genre))).ans() <<endl;
}

void get_group_recommendation_aux(streaming_database *obj, int groupId) {
    //cout<<"get group reccomandation to group "<< groupId <<" " << endl;
    cout<< (obj->get_group_recommendation(groupId)).ans() <<endl;
}

void status_aux(StatusType status) {
        switch (status)
    {
        case StatusType::SUCCESS:
            cout<<"SUCCESS"<<endl;
            break;
        case StatusType::FAILURE:
            cout<<"FAILURE"<<endl;
            break;
        case StatusType::ALLOCATION_ERROR:
            cout<<"ALLOCATION_ERROR"<<endl;
            break;
        case StatusType::INVALID_INPUT:
            cout<<"INVALID_INPUT"<<endl;
            break;
    }

}

void my_query_get_all_movies_aux(streaming_database *obj, Genre genre)
{
    cout<<"get all movies aux "<< endl;
    output_t<int> count = obj->get_all_movies_count(genre);
    int to_alloc = count.ans();
    if (to_alloc == 0)
    {
        //if there are no movies we will allocate 1 so that we will get failure instead of invalid input
        ++to_alloc;
    }
    // Allocate if okay
    int *out_mem = nullptr;
    if (count.status() == StatusType::SUCCESS)
    {
        out_mem = new int[to_alloc];
        for (int i = 0; i < to_alloc; ++i) out_mem[i] = -1;
    }
    // Call function
    StatusType status = obj->get_all_movies(genre, out_mem);
//    print(cmd, status);
    if (status == StatusType::SUCCESS) {
        for (int i = 0; i < to_alloc; ++i)
        {
            std::cout << out_mem[i] << std::endl;
        }
    }
    delete[] out_mem;
}


void test() {
    streaming_database *obj = new streaming_database();

    status_aux(obj->add_group(3906));
    status_aux(obj->add_group(3182));
    status_aux(obj->add_user_to_group(6174, 3906));
    get_all_movies_aux(obj, 1);
    status_aux(obj->add_user(5740, false));
    get_all_movies_count_aux(obj, 2);
    status_aux(obj->add_user_to_group(5740, 3906));
    status_aux(obj->rate_movie(5740, 3637, 47));
    status_aux(obj->add_user(5046, true));
    status_aux(obj->user_watch(5046, 7603));
    status_aux(obj->group_watch(3182, 5069));
    get_num_views_aux(obj, 5740, 2);
    status_aux(obj->remove_movie(4323));
    get_all_movies_aux(obj, 4);
    status_aux(obj->remove_user(5740));
    status_aux(obj->user_watch(5046, 4834));
    status_aux(obj->remove_movie(4637));
    status_aux(obj->add_user(5450, true));
    status_aux(obj->add_user(3655, true));
    get_all_movies_count_aux(obj, 1);
    status_aux(obj->add_user(6007, true));
    status_aux(obj->user_watch(3655, 7517));
    get_all_movies_count_aux(obj, 0);
    get_all_movies_aux(obj, 1);
    status_aux(obj->add_user(5973, false));
    get_all_movies_aux(obj, 2);
    get_all_movies_aux(obj, 3);
    add_movie_aux(obj, 1771, 0, 77, true);
    status_aux(obj->add_user(1211, false));
    status_aux(obj->user_watch(5740, 1771));
    add_movie_aux(obj, 4008, 2, 8, true);
    get_all_movies_aux(obj, 4);
    get_all_movies_count_aux(obj, 0);
    get_all_movies_count_aux(obj, 2);
    status_aux(obj->user_watch(3655, 4008));
    status_aux(obj->user_watch(5740, 4008));
    status_aux(obj->add_group(8180));
    status_aux(obj->add_user_to_group(5973, 8180));
    status_aux(obj->remove_user(8643));
    status_aux(obj->add_group(2254));
    status_aux(obj->remove_user(5046));
    status_aux(obj->remove_group(2254));
    status_aux(obj->remove_group(3182));
    status_aux(obj->remove_movie(4008));
    status_aux(obj->remove_movie(1771));
    add_movie_aux(obj, 1376, 3, 8, false);
    status_aux(obj->add_user_to_group(1211, 3906));
    status_aux(obj->add_user_to_group(3655, 8180));
    status_aux(obj->group_watch(3182, 1376));
    get_all_movies_count_aux(obj, 2);
    status_aux(obj->user_watch(1211, 1376));
    status_aux(obj->add_user_to_group(1211, 3906));
    add_movie_aux(obj, 6549, 2, 58, false);
    status_aux(obj->remove_movie(2038));
    get_all_movies_aux(obj, 4);
    get_group_recommendation_aux(obj, 3906);
    status_aux(obj->rate_movie(1211, 6549, 14));
    status_aux(obj->rate_movie(5450, 6549, 48));
    status_aux(obj->add_user(3931, true));
    get_all_movies_aux(obj, 0);
    get_all_movies_aux(obj, 1);
    get_num_views_aux(obj, 1211, 1);
    get_all_movies_aux(obj, 2);
    status_aux(obj->remove_movie(1376));
    get_all_movies_aux(obj, 1);
    status_aux(obj->user_watch(6007, 6549));
    status_aux(obj->add_user(188, false));
    status_aux(obj->add_user(2103, true));
    status_aux(obj->add_user_to_group(2103, 3182));//user exists but group doesn't, should return failure but crashes

    cout<<"didnt add user 2103 from group 3182"  <<endl;
    //dies here!///////////////////////////////////////////////
    status_aux(obj->remove_group(3182));
    status_aux(obj->rate_movie(3655, 6549, 78));
    status_aux(obj->add_group(6737));
    get_all_movies_aux(obj, 4);
    get_all_movies_aux(obj, 4);
    status_aux(obj->add_user(7092, true));
    status_aux(obj->add_group(8818));
    status_aux(obj->remove_movie(6549));
    status_aux(obj->rate_movie(1744, 6549, 17));
    get_group_recommendation_aux(obj, 8180);
    status_aux(obj->remove_user(2103));

    delete obj;

}


int main() {

    test();
    return 0;
}
