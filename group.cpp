#include "group.h"


Group(int group_id, AVLTree<User> members, int[4] movies_group_watched):m_group_id(group_id), m_members(members){
    for(int i = 0; i <= 4; i++){
        m_movies_group_watched[i] = movies_group_watched[i];
    }
}

~Group(){
    free(m_members);
    free(m_movies_group_watched);
}

Group(const Group& group) = default;

int Group::geGrouptId(){
    return m_group_id;
}

AVLTree<User> getMembers(){
    //idk 
}

int getMoviesGroupWatchedInGenre(Genre genre){
    
}

