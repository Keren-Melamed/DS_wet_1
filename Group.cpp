#include "group.h"

Group::Group(int group_id, bool isVip, int group_size):
    m_group_id(group_id), m_isVip(isVip), m_group_size(group_size)
{
    m_members.setRoot(nullptr);
}

Group::~Group(){
    //free(m_members); the tree should delete automatically with the d'tor
    free(m_movies_group_watched);
}

Group::Group(const Group& group) = default;

int Group::getGroupId() const
{
    return m_group_id;
}

AVLTree<User> Group::getMembers()
{
    return m_members;
}

int Group::getMoviesGroupWatchedInGenre(Genre genre)
{
    if(genre != Genre::NONE)
    {
        return m_movies_group_watched[(int)genre];
    }
    
    else
    {
        int value = 0;

        for(int i = 0; i <= 4; i++)
        {
            value += m_movies_group_watched[i];
        }
        return value;
    }
    return m_movies_group_watched[(int)genre];// redundant?
}

bool Group::getIsVip() const
{
    return m_isVip;
}

void Group::setIsVip(bool isVip)
{
    m_isVip = isVip;
}

void Group::UpdateGroupSize()
{
    m_group_size += 1;
}

int Group::getGroupSize() const
{
    return m_group_size;
}

void Group::dismantleGroup(Node<User>* user)
{
    if(user != nullptr)
    {
        user->getValue().setGroup(nullptr);
        dismantleGroup(user->getLeftNode());
        dismantleGroup(user->getRightNode());
    }
}

void Group::UpdateSetMoviesGroupWatchedInGenre(Genre genre)
{
    if(genre != Genre::NONE)
    {
        m_movies_group_watched[(int) genre] += 1;
    }
}
