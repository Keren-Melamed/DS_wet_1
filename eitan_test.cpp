#include <iostream>
#include "StreamingDBa1.h"

void get_all_movies_aux(streaming_database *obj, int genre);
void my_query_get_all_movies_aux(streaming_database *obj, Genre genre);

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

void get_all_movies_aux(streaming_database *obj, int genre) {
    //cout<<"get all movies genre "<< genre << endl;
    my_query_get_all_movies_aux(obj, static_cast<Genre>(genre));
}

void add_movie_aux(streaming_database *obj, int movieId, int genre, int views, bool isVip) {
    //cout<<"add movie "<<movieId<<" to genre "<< genre << endl;
    status_aux(obj->add_movie(movieId, static_cast<Genre>(genre), views, isVip));
}

void get_num_views_aux(streaming_database *obj, int movieId, int genre) {
    //cout<<"get num views "<<movieId << endl;
    output_t<int> count = obj->get_num_views(movieId, static_cast<Genre>(genre));
    status_aux(count.status());
    std::cout << count.ans() << std::endl;   
    
    
}

void get_all_movies_count_aux(streaming_database *obj, int genre) {
    //cout<<"get all movies count of genre "<< genre <<" " << endl;
    cout<< (obj->get_all_movies_count(static_cast<Genre>(genre))).ans() <<endl;
}

void get_group_recommendation_aux(streaming_database *obj, int groupId) {
    //cout<<"get group reccomandation to group "<< groupId <<" " << endl;
    output_t<int> res = obj->get_group_recommendation(groupId);
    if(res.ans() == 0){
        status_aux(res.status());
    }
    else{
        std::cout << res.ans() << std::endl;   
    }
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
    else{
        status_aux(status);
    }
    delete[] out_mem;
}


void test() {
    streaming_database *obj = new streaming_database();

    status_aux(obj->add_group(3243));
    get_num_views_aux(obj, 6140, 2);
    
    status_aux(obj->add_group(5315));
    status_aux(obj->add_user(659, false));
    status_aux(obj->remove_user(659));
    status_aux(obj->add_group(44));
    add_movie_aux(obj, 3475, 2, -1, false);
    status_aux(obj->remove_user(659));
    status_aux(obj->add_user(4866, false));
    get_all_movies_aux(obj, 0);
    status_aux(obj->add_group(7487));
    add_movie_aux(obj, 8591, 1, 70, true);
    get_all_movies_aux(obj, 3);
    status_aux(obj->add_user(4986, true));
    status_aux(obj->group_watch(3243, 8591)); //FAILURE

    status_aux(obj->user_watch(659, 3475));//FAILURE

    status_aux(obj->add_user(9251, true));
    get_group_recommendation_aux(obj,3243);
    get_all_movies_aux(obj, 3);
    get_all_movies_aux(obj, 0);
    status_aux(obj->add_group(7899));
    status_aux(obj->user_watch(4866, 3475));//FAILURE

    get_all_movies_aux(obj, 4);
    add_movie_aux(obj, 3851, 4, 27, true);
    status_aux(obj->add_group(8580));
    add_movie_aux(obj, 7130, 4, 82, true);
    status_aux(obj->remove_user(4986));
    status_aux(obj->add_group(610));
    add_movie_aux(obj, 1379, 3, 65, false);
    status_aux(obj->add_user(5512, true));
    status_aux(obj->add_user(3666, true));
    
    status_aux(obj->add_group(3153));
    get_group_recommendation_aux(obj, 3153);
    
    status_aux(obj->add_group(391));
    get_num_views_aux(obj, 5512, 3);
    status_aux(obj->add_user(233, true));
    status_aux(obj->add_group(3908));
    get_all_movies_count_aux(obj, 2);
    status_aux(obj->remove_group(610));
    get_all_movies_aux(obj, 1);
    status_aux(obj->add_group(3243));
    get_group_recommendation_aux(obj,44);
    get_all_movies_count_aux(obj, 0);
    status_aux(obj->add_user(7951, true));
    get_all_movies_count_aux(obj, 4);
    status_aux(obj->group_watch(391, 7130));//FAILURE

    status_aux(obj->rate_movie(7951, 8591, 11));//SUCCESS

    status_aux(obj->add_user(1008, true));
    get_num_views_aux(obj, 659, 3);
    get_all_movies_count_aux(obj, 0);
    status_aux(obj->group_watch(7487, 3475)); //FAILURE

    status_aux(obj->add_group(7075));
    get_all_movies_aux(obj, 1);
    status_aux(obj->add_user(9961, true));
    status_aux(obj->add_user(1963, false));
    status_aux(obj->group_watch(8580, 3851));//FAILURE

    get_all_movies_aux(obj, 0);
    status_aux(obj->remove_movie(8591));
    get_all_movies_aux(obj, 2);
    status_aux(obj->remove_user(1963));
    status_aux(obj->add_user(64, true));
    get_all_movies_aux(obj, 0);
    status_aux(obj->remove_user(5512));
    get_num_views_aux(obj, 3666, 0);
    add_movie_aux(obj, 2990, 2, 18, false);
    status_aux(obj->remove_user(659));
    status_aux(obj->group_watch(7356, 3475));//FAILURE

    status_aux(obj->remove_movie(1379));
    get_num_views_aux(obj, 9251, 0);
    add_movie_aux(obj, 1788, 1, 59, true);
    status_aux(obj->add_user(7071, false));
    status_aux(obj->remove_user(9961));
    get_num_views_aux(obj, 233, 0);
    
    add_movie_aux(obj, 9379, 0, 56, true);/////////////////////////////////
    
    add_movie_aux(obj, 8539, 2, 76, true);
    status_aux(obj->add_group(3351));
    status_aux(obj->user_watch(659, 8539));//FAILURE

    get_all_movies_aux(obj, 3);
    status_aux(obj->add_user(4284, true));
    get_all_movies_aux(obj, 1);
    status_aux(obj->user_watch(4866, 9379));//FAILURE

    status_aux(obj->add_user(9775, true));
    status_aux(obj->remove_group(3243));
    status_aux(obj->add_group(9786));
    get_all_movies_aux(obj, 3);
    get_all_movies_aux(obj, 4);














    add_movie_aux(obj, 5496, 1, 22, false);
    status_aux(obj->remove_movie(4403));
    status_aux(obj->add_user(2323, true));
    status_aux(obj->add_user_to_group(9775, 391));
    get_all_movies_aux(obj, 4);
    status_aux(obj->add_group(3245));
    status_aux(obj->user_watch(9775, 8539));//SUCCESS

    status_aux(obj->user_watch(4866, 1788));//FAILURE

    status_aux(obj->add_user(5128, true));
    status_aux(obj->add_group(9164));
    status_aux(obj->remove_user(2323));
    status_aux(obj->rate_movie(7951, 9379, 21));//SUCCESS

    status_aux(obj->add_group(3682));
    status_aux(obj->group_watch(7487, 5496));//FAILURE

    status_aux(obj->remove_movie(3475));
    status_aux(obj->group_watch(391, 7130));//FAILURE

    status_aux(obj->remove_group(44));
    status_aux(obj->rate_movie(7951, 5496, 29));//SUCCESS

    get_all_movies_aux(obj, 4);
    status_aux(obj->add_user(6250, true));
    status_aux(obj->remove_movie(7130));
    status_aux(obj->add_user_to_group(3666, 3908));
    status_aux(obj->remove_user(659));
    add_movie_aux(obj, 5394, 4, 51, true);
    status_aux(obj->add_user(7574, true));
    status_aux(obj->user_watch(9251, 8539));//SUCCESS


    status_aux(obj->remove_user(5128));
    status_aux(obj->group_watch(3153, 9379));//FAILURE
    
    get_group_recommendation_aux(obj,3682);
    status_aux(obj->rate_movie(3666, 8539, 9));//SUCCESS

    get_all_movies_aux(obj, 1);
    add_movie_aux(obj, 3949, 4, 39, false);
    add_movie_aux(obj, 9145, 4, 41, true);
    status_aux(obj->add_user(2858, true));
    
    add_movie_aux(obj, 6495, 0, 32, false);/////////////////////////////////
    get_num_views_aux(obj, 7951, 4);
    status_aux(obj->add_user(679, true));
    status_aux(obj->remove_group(7075));
    get_all_movies_count_aux(obj, 0);
    status_aux(obj->add_user_to_group(4284, 9786));
    status_aux(obj->rate_movie(679, 2990, 93));//SUCCESS
;
    get_num_views_aux(obj, 2858, 4);
    status_aux(obj->remove_movie(9379));/////////////////////////////////REMOVE 9379
    status_aux(obj->remove_user(4284));
    status_aux(obj->remove_movie(1788));
    status_aux(obj->add_user_to_group(8894, 391));
    get_all_movies_aux(obj, 0);

        cout<<"///////////////////////////////////////////////////////////"<<endl;
    
    status_aux(obj->add_group(2858));
    status_aux(obj->rate_movie(4866, 8539, 84));//FAILURE

    get_num_views_aux(obj, 7951, 0);
    get_all_movies_count_aux(obj, 2);
    status_aux(obj->add_group(7217));
    status_aux(obj->remove_user(7574));
    get_all_movies_count_aux(obj, 2);
    status_aux(obj->remove_user(233));
    status_aux(obj->remove_user(9775));
    status_aux(obj->remove_user(7071));
    status_aux(obj->add_group(8400));
    status_aux(obj->add_user(9677, false));
    status_aux(obj->remove_movie(1852));
    status_aux(obj->user_watch(9677, 2990));//SUCCCESS

    status_aux(obj->add_user(5022, false));
    get_all_movies_count_aux(obj, 1);
    status_aux(obj->rate_movie(9251, 3949, 145));//INVALID

    status_aux(obj->remove_movie(9379));
    add_movie_aux(obj, 5777, 2, 72, false);
    add_movie_aux(obj, 288, 4, 3, false);
    status_aux(obj->rate_movie(6250, 8539, 67));
    status_aux(obj->add_group(9227));
    get_group_recommendation_aux(obj,9227);
    status_aux(obj->add_group(2767));
    get_all_movies_aux(obj, 4);
    status_aux(obj->remove_group(3153));
    status_aux(obj->add_user(3533, true));
    add_movie_aux(obj, 6672, 0, 4, false);////////////////////
    status_aux(obj->add_group(4775));
    add_movie_aux(obj, 4459, 4, 100, false);
    status_aux(obj->remove_user(9677));
    status_aux(obj->add_user(4869, true));
    status_aux(obj->user_watch(4869, 2990));

    status_aux(obj->user_watch(3533, 5777));

    status_aux(obj->remove_group(4775));
    status_aux(obj->add_user(1284, false));
    status_aux(obj->rate_movie(1284, 1156, 37));

    status_aux(obj->add_user(7176, false));
    get_all_movies_count_aux(obj, 4);
    status_aux(obj->remove_movie(6672));
    status_aux(obj->group_watch(7487, 3949));//FAILURE

    status_aux(obj->add_group(4362));
    status_aux(obj->remove_user(6250));
    get_all_movies_aux(obj, 2);
    get_group_recommendation_aux(obj,3682);
    status_aux(obj->add_group(3174));
    status_aux(obj->remove_user(3666));


    delete obj;

}


int main() {

    test();
    return 0;
}
