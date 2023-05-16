#ifndef GROUP_H
#define GROUP_H

#include "wet1util.h"
#include "AVLTree.h"
#include "User.h"



class Group{

    private:
        int m_group_id;
        AVLTree<User> m_members;
        int m_movies_group_watched[4];
        bool m_isVip;
        int m_group_size;

    public:
        Group();

        ~Group();

        Group(const Group& group);

        int getGroupId();

        AVLTree<User>* getMembers();

        int getMoviesGroupWatchedInGenre(Genre genre);

        void UpdatesetMoviesGroupWatchedInGenre(Genre genre);

        bool getIsVip() const;

        void setIsVip(bool isVip);

        void UpdateGroupSize();

        int getGroupSize() const;

        void dismantleGroup(Node<User>* user);

};

#endif