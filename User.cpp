
#include "user.h"

User::User(int user_id, bool is_Vip, Group* user_group)
    :m_id(user_id), m_is_vip(is_Vip)
{
    m_user_group = nullptr;
}

User::~User()
{
    free(m_movies_user_watched);
}

User::User(const User& user) = default;

int User::getId() const
{
    return m_id;
}

bool User::getIsVip() const
{
    return m_is_vip;
}

Group* User::getGroup()
{
    return m_user_group;
}

int User::getMoviesUserWatchedInGenre(Genre genre)
{
    
    if(genre != Genre::NONE)
    {
        return m_movies_user_watched[(int)genre];
    }
    
    else
    {
        int value=0;

        for(int i = 0; i <4; i++)
        {
            value += m_movies_user_watched[i];
        }
        return value;
    }
}

void User::setGroup(Group* group)
{
    m_user_group = group;
}

void User::UpdateMoviesUserWatchedInGenre(Genre genre)
{
    if(genre != Genre::NONE)
    {
        m_movies_user_watched[(int) genre] += 1;
    }
}

bool User::operator>(const User &other) const
{
    return (this->getId() > other.getId());
}

bool User::operator<(const User &other) const
{
    return (this->getId() < other.getId());
}

bool operator==(const User &a, const User &b)
{
    return (a.getId() == b.getId());
}

    

