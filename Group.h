#ifndef GROUP_H
#define GROUP_H

#include "wet1util.h"
#include "AVLTree.h"
#include "User.h"

class User;

class Group{

    private:
        int m_group_id;
        AVLTree<User> m_members;
        int m_movies_group_watched[4] = {0};
        bool m_isVip;
        int m_group_size;

        friend bool operator==(const Group& a, const Group& b);

        bool operator<(const Group& other) const;

        bool operator>(const Group& other) const;

    public:
        Group(int group_id, bool isVip, int group_size);

        ~Group();

        Group(const Group& group);

        AVLTree<User> getMembers();

        int getGroupId() const;

        int getMoviesGroupWatchedInGenre(Genre genre);

        int getGroupSize() const;

        void UpdateSetMoviesGroupWatchedInGenre(Genre genre);

        void setIsVip(bool isVip);

        void UpdateGroupSize();

        void dismantleGroup(Node<User>* user);

        bool getIsVip() const;

};

#endif