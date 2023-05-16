#ifndef USER_H_
#define USER_H_

#include "wet1util.h"
#include "Group.h"

class Group;

class User{
    private:
        int m_id;
        bool m_is_vip;
        Group* m_user_group; 
        int m_movies_user_watched[4] = {0};

    public:
        User(int user_id, bool is_Vip, Group* user_group = nullptr);

        ~User();

        User(const User& user);

        int getId() const;

        bool getIsVip() const;

        Group* getGroup();

        int getMoviesUserWatchedInGenre(Genre genre);

        void setGroup(Group* group);

        void UpdateMoviesUserWatchedInGenre(Genre genre);

};

#endif


    

