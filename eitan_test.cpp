#include <iostream>
#include "StreamingDBa1.h"

void get_all_movies_aux(streaming_database *obj, int genre);
void my_query_get_all_movies_aux(streaming_database *obj, Genre genre);

void get_all_movies_aux(streaming_database *obj, int genre) {
    my_query_get_all_movies_aux(obj, static_cast<Genre>(genre));
}

void add_movie_aux(streaming_database *obj, int movieId, int genre, int views, bool isVip) {
    obj->add_movie(movieId, static_cast<Genre>(genre), views, isVip);
}

void get_num_views_aux(streaming_database *obj, int movieId, int genre) {
    output_t<int> count = obj->get_num_views(movieId, static_cast<Genre>(genre));
    std::cout << count.ans() << std::endl;
}

void get_all_movies_count_aux(streaming_database *obj, int genre) {
    cout<< (obj->get_all_movies_count(static_cast<Genre>(genre))).ans() <<endl;
}


void my_query_get_all_movies_aux(streaming_database *obj, Genre genre)
{
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

    get_all_movies_count_aux(obj, 2);
    obj->rate_movie(1634, 7872, 142);
    obj->add_user_to_group(9305, 453);
    obj->group_watch(7081, 5015);
    obj->add_user(9617, false);
    get_all_movies_count_aux(obj, 4);
    add_movie_aux(obj, 8722, 2, 26, true);
    obj->add_user_to_group(9617, 7367);
    get_num_views_aux(obj, 9617, 3);
    obj->add_group(8812);
    obj->get_group_recommendation(8812);
    obj->get_group_recommendation(8812);
    obj->add_group(2461);
    obj->rate_movie(9617, 8722, 29);
    obj->get_group_recommendation(8812);
    obj->add_group(8812);
    obj->remove_group(8812);
    get_all_movies_aux(obj, 1);
    obj->add_user_to_group(9617, 2461);
    get_num_views_aux(obj, 9617, 4);
    add_movie_aux(obj, 9301, 2, 37, true);
    add_movie_aux(obj, 5077, 3, 27, true);
    add_movie_aux(obj, 8180, 3, 12, true);
    obj->group_watch(2461, 8180);
    get_all_movies_aux(obj, 3);
    obj->group_watch(2461, 8722);
    obj->remove_user(9617);
    get_num_views_aux(obj, 6151, 3);
    obj->add_user(3643, true);
    obj->add_user(6854, true);
    get_all_movies_aux(obj, 1);
    obj->user_watch(3643, 8180);
    obj->user_watch(3643, 8722);
    get_all_movies_aux(obj, 1);
    obj->add_group(2471);
    add_movie_aux(obj, 3826, 2, 41, false);
    add_movie_aux(obj, 1407, 2, 41, true);
    cout<<"removing..."<<endl;
    obj->remove_movie(5077);
    obj->add_user(9314, false);
    add_movie_aux(obj, 6434, 4, 37, false);
    get_all_movies_aux(obj, 1);
    obj->remove_group(2461);
    obj->user_watch(9314, 9301);
    obj->add_user(7091, false);
    obj->rate_movie(6854, 6434, 78);
    add_movie_aux(obj, 8523, 1, 78, false);
    obj->add_group(4359);
    add_movie_aux(obj, 716, 0, 33, false);
    add_movie_aux(obj, 7289, 2, 91, true);
    add_movie_aux(obj, 1575, 4, 61, false);

    cout<<"all movies after remove"<<endl;
    get_all_movies_aux(obj, 4);

    cout<<"movies in 3 after remove"<<endl;
    get_all_movies_aux(obj, 3);

    get_all_movies_count_aux(obj, 3);
    get_all_movies_count_aux(obj, 1);
    get_num_views_aux(obj, 7091, 1);
    obj->remove_movie(8722);
    obj->add_user(7796, true);
    obj->add_user(6289, false);
    get_num_views_aux(obj, 7091, 4);
    obj->add_user(3040, false);
    obj->remove_user(6854);
    obj->rate_movie(3643, 716, 107);
    obj->add_user_to_group(6289, 2471);
    obj->remove_group(2471);
    obj->remove_group(4359);
    obj->add_user(4506, false);
    get_all_movies_aux(obj, 4);
    get_all_movies_aux(obj, 2);
    add_movie_aux(obj, 2829, 4, 20, false);
    obj->get_group_recommendation(4359);
    obj->remove_user(6289);
    obj->add_group(9206);
    obj->add_user(6947, true);
    get_all_movies_aux(obj, 0);
    get_all_movies_aux(obj, 2);
    get_all_movies_aux(obj, 4);
    obj->add_group(1712);
    obj->add_user(9874, false);
    get_num_views_aux(obj, 9314, 1);
    get_all_movies_count_aux(obj, 4);
    get_all_movies_aux(obj, 1);
    get_all_movies_count_aux(obj, 2);
    obj->rate_movie(9314, 2829, 57);
    obj->add_user_to_group(3040, 4359);
    obj->user_watch(7091, 1407);
    obj->user_watch(9314, 1407);
    obj->remove_group(9206);
    get_all_movies_count_aux(obj, 0);
    obj->remove_movie(716);
    obj->add_user(9388, false);
    obj->remove_group(4359);
    obj->remove_user(4506);


   

    delete obj;

}


int main() {

    test();
    return 0;
}
