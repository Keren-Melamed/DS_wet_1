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

    public:

        friend bool operator==(const Group& a, const Group& b);
        bool operator<(const Group& other) const;
        bool operator>(const Group& other) const;

        void print(ostream &os) const;

        Group() = delete;

        Group(int group_id, bool isVip, int group_size);

        ~Group();

        Group(const Group& group) = default; //might need to be const group&

        AVLTree<User>* getMembers();

        int getGroupId() const;

        int getMoviesGroupWatchedInGenre(Genre genre);

        int getGroupSize() const;

        void updateMoviesGroupWatchedInGenre(Genre genre, int views);

        void setIsVip(bool isVip);

        void updateGroupSize();

        void dismantleGroup(Node<User>* user);

        void addViewToMembers(Node<User>* Node, Genre genre);

        bool getIsVip() const;

};

#endif