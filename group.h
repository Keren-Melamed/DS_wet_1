#include "wet1util.h"
#include "AVLTree.h"
#include "user.h"

#ifndef GROUP_H_
#define GROUP_H_


class Group{

    private:
        int m_group_id;
        AVLTree<User> m_members;
        int[4] m_movies_group_watched;
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

        bool getIsVip();

        void setIsVip(bool isVip);

        void UpdateGroupSize();

        int getGroupSize();

        void dismantleGroup(Node<T>* user);

}

#endif