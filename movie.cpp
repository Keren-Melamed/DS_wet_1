#include "movie.h"

Movie::Movie(int movieID, int views, bool vipOnly, Genre genre):
m_movieId(movieID), m_views(views), m_numOfVoters(0), m_rating(0), m_vipOnly(vipOnly), m_genre(genre)
{}//arnt chekcing input here, we'll check it in addMovie in StreamingDBa1

void Movie::addRating(int rating)
{
    if (rating > 0 && rating < 100)
    {
        rating += m_rating * m_numOfVoters;
        m_numOfVoters++;
        m_rating = rating / m_numOfVoters;
    }
}

void Movie::addViews(int views)
{
    m_views += views;
}

bool Movie::getVipOnly()
{
    return m_vipOnly;
}

int Movie::getMovieId()
{
    return m_movieId;
}

int Movie::getRating()
{
    return m_rating;
}

int Movie::getViews()
{
    return m_views;
}

Genre Movie::getGenre()
{
    return m_genre;
}