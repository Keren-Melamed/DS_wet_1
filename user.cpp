#ifndef USER_H_
#define USER_H_

#include "user.h"

User::User(int user_id, bool is_Vip, Group* user_group, int[4] movies_watched)
    :m_user_id(user_id), m_is_vip(is_vip), m_user_group(user_group){

    for(int i = 0; i <= 4; i++){
        m_movies_user_watched[i] = movies_user_watched[i];
    }
}

User::~User(){
    free(m_movies_user_watched);
}

User::User(const User& user) = default;

int User::getId(){
    return m_id;
}

bool User::getIsVip(){
    return m_is_vip;
}

Group* User::getGroup(){
    return m_user_group;
}

int User::getMoviesUserWatchedInGenre(Genre genre){
    
    if(genre != NONE){
        return m_movies_watched[genre];
    }
    
    else{
        int value=0;

        for(int i = 0; i <=4; i++;){
            value += m_movies_watched[i];
        }
        return value;
    }
}


void User::setGroup(Group* group){
    m_user_group = group;
}

void User::UpdateMoviesUserWatchedInGenre(Genre genre){
    if(genre != NONE){
        m_movies_user_watched[genre] += 1;
    }
}

    

