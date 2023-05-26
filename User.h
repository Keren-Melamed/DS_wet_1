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

        friend bool operator==(const User& a, const User& b);
        bool operator<(const User& other) const;
        bool operator>(const User& other) const;

        User() = delete;

        User(int user_id, bool is_Vip, Group* user_group = nullptr);

        ~User() = default;

        User(const User& user);

        int getId() const;

        bool getIsVip() const;

        Group* getGroup();

        int getMoviesUserWatchedInGenre(Genre genre);

        void setGroup(Group* group);

        void UpdateMoviesUserWatchedInGenre(Genre genre);

        void print(std::ostream& os) const;

};

#endif


    

