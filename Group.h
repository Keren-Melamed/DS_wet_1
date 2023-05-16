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
        int m_movies_group_watched[4] = {0};//not sure if = {0} is allowed but clion seems to like it
        bool m_isVip;
        int m_group_size;

    public:
        Group(int group_id, bool isVip, int group_size);

        ~Group();

        Group(const Group& group);

        int getGroupId() const;

        AVLTree<User> getMembers();

        int getMoviesGroupWatchedInGenre(Genre genre);

        void UpdateSetMoviesGroupWatchedInGenre(Genre genre);

        bool getIsVip() const;

        void setIsVip(bool isVip);

        void UpdateGroupSize();

        int getGroupSize() const;

        void dismantleGroup(Node<User>* user);

};

#endif