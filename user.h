#include "wet1util.h"
#include "group.h"

#ifndef USER_H_
#define USER_H_

class User{
    private:
        int m_id;
        bool m_is_vip;
        Group* m_user_group; 
        int[4] m_movies_user_watched;

    public:
        User(int user_id, bool is_Vip, Group* user_group, int[4] movies_watched);

        ~User();

        User(const User& user);

        int getId();

        bool getIsVip();

        Group* getGroup();

        int getMoviesUserWatchedInGenre(Genre genre);

        

}

#endif


    

