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

    public:
        Group(int group_id, AVLTree<User> members, int[4] movies_group_watched);

        ~Group();

        Group(const Group& group);

        int getGroupId();

        AVLTree<User> getMembers();

        int getMoviesGroupWatchedInGenre(Genre genre){
            //same as in user, if ok there then copy
        }


}

#endif