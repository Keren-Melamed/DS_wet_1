#include "group.h"


Group::Group(){
    m_group_id = 0;
    m_members = NULL;
    m_movies_group_watched = {0,0,0,0};
    m_isVip = false;
    m_group_size = 0;
}

Group::~Group(){
    free(m_members);
    free(m_movies_group_watched);
}

Group::Group(const Group& group) = default;

int Group::geGrouptId(){
    return m_group_id;
}

AVLTree<User>* Group::getMembers(){
    return m_members.getRoot();
}

int Group::getMoviesGroupWatchedInGenre(Genre genre){
    if(genre != NONE){
        return m_movies_group_watched[genre];
    }
    
    else{
        int value=0;

        for(int i = 0; i <=4; i++;){
            value += m_movies_group_watched[i];
        }
        return value;
    }
    return m_movies_group_watched[genre];
}

bool Group::getIsVip(){
    return _isVip;
}

void Group::setIsVip(bool isVip){ 
    m_isVip = isVip;
}

void Group::UpdateMoviesGroupWatchedInGenre(Genre genre){
    if(genre != NONE){
        m_movies_group_watched[genre] += 1;
    }
}

void Group::UpdateGroupSize(){
    m_group_size += 1;
}

int Group::getGroupSize(){
    return m_group_size;
}

void Group::dismantleGroup(Node<T>* user){
    if(user != nullptr){
        user.setGroup(nullptr;)
        dismantleGroup(user->getLeftNode());
        dismantleGroup(user->getRightNode());
    }
}