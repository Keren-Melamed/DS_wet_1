#include <iostream>
#include "StreamingDBa1.h"

void get_all_movies_aux(streaming_database *obj, int genre);
void my_query_get_all_movies_aux(streaming_database *obj, Genre genre);


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
/*
    cout<<"57 - get all movies genre 0"<<endl;
    get_all_movies_aux(obj, 1);
    
    cout<<"60 - get all movies count genre 2"<<endl;
    get_all_movies_count_aux(obj, 2);

    cout<<"63 - removing movie 4323 (never added)"<<endl;
    obj->remove_movie(4323);//remove something that doesnt exist

    cout<<"66 - get all movies all genres"<<endl;
    get_all_movies_aux(obj, 4);

    cout<<"69 - removing movie 4637 (never added)"<<endl;
    obj->remove_movie(4637); //remove something that doesnt exist

    cout<<"72 - get all movies count genre 1"<<endl;
    get_all_movies_count_aux(obj, 1);

    cout<<"75 - get all movies count genre 0"<<endl;
    get_all_movies_count_aux(obj, 0);

    cout<<"78 - get all movies genre 1"<<endl;
    get_all_movies_aux(obj, 1);
     
    cout<<"81 - get all movies genre 2"<<endl;
    get_all_movies_aux(obj, 2);

    cout<<"84 - get all movies genre 3"<<endl;
    get_all_movies_aux(obj, 3);

    cout<<"87 - adding movie 1771 to genre 0"<<endl;
    add_movie_aux(obj, 1771, 0, 77, true); //add genre 0

    cout<<"90 - adding movie 4008 to genre 2"<<endl;
    add_movie_aux(obj, 4008, 2, 8, true);//add genre 2

    cout<<"93 - get all movies all genres"<<endl;
    get_all_movies_aux(obj, 4);

    cout<<"96 - get all movies count genre 0"<<endl;
    get_all_movies_count_aux(obj, 0);

    cout<<"99 - get all movies count genre 0"<<endl;
    get_all_movies_count_aux(obj, 2);

    cout<<"102 - removing 4008 from genre 2"<<endl;
    obj->remove_movie(4008); //remove from genre 2

    cout<<"105 - removing 1771 from genre 0"<<endl;
    obj->remove_movie(1771); //remove from genre 0

    cout<<"108 - adding movie 1376 to genre 3"<<endl;
    add_movie_aux(obj, 1376, 3, 8, false); //add genre 3

    cout<<"113 - get all movies count genre 2"<<endl;
    get_all_movies_count_aux(obj, 2);

    cout<<"114 - removing 2038 (never added)"<<endl;
    obj->remove_movie(2038); //remove that doesnt exist

    cout<<"117 - get all movies all genres"<<endl;
    get_all_movies_aux(obj, 4);

    cout<<"123 - get all movies genre 0"<<endl;
    get_all_movies_aux(obj, 0);

    cout<<"126 - get all movies genre 1"<<endl;
    get_all_movies_aux(obj, 1);
    
    cout<<"129 - get all movies genre 2"<<endl;
    get_all_movies_aux(obj, 2);

    cout<<"132 - removing 1376 from genre 3"<<endl;
    obj->remove_movie(1376); //remove genre 3

    cout<<"135 - get all movies genre 1"<<endl;
    get_all_movies_aux(obj, 1);

    cout<<"138 - get all movies all genres"<<endl;
    get_all_movies_aux(obj, 4);

    cout<<"141 - get all movies all genres"<<endl;
    get_all_movies_aux(obj, 4);

    cout<<"144 - removing 6549 (never added)"<<endl;
    obj->remove_movie(6549);
   */
    
    status_aux(obj->add_group(3906));
    status_aux(obj->add_group(3182));
    status_aux(obj->add_user_to_group(6174, 3906));

    status_aux(obj->add_user_to_group(5740, 3906));

    status_aux(obj->group_watch(3182, 5069));
    get_num_views_aux(obj, 5740, 2);
    status_aux(obj->add_group(8180));
    status_aux(obj->add_user_to_group(5973, 8180));

    status_aux(obj->add_group(2254));

    status_aux(obj->remove_group(2254));
    status_aux(obj->remove_group(3182));


    status_aux(obj->add_user_to_group(1211, 3906));
    status_aux(obj->add_user_to_group(3655, 8180));
    status_aux(obj->group_watch(3182, 1376));

    status_aux(obj->add_user_to_group(1211, 3906));
    
    get_group_recommendation_aux(obj, 3906);
   
    status_aux(obj->add_user_to_group(2103, 3182));//user exists but group doesn't, should return failure but crashes

    cout<<"didnt add user 2103 from group 3182"  <<endl;
    //dies here!///////////////////////////////////////////////
    status_aux(obj->remove_group(3182));
 
    status_aux(obj->add_group(6737));
  
   
    status_aux(obj->add_group(8818));
   
    get_group_recommendation_aux(obj, 8180);
  
    
    delete obj;

}


int main() {

    test();
    return 0;
}
