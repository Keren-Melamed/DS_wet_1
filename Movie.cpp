#include "movie.h"

Movie::Movie(int movieID, int views, bool vipOnly, Genre genre):
m_movieId(movieID), m_views(views), m_numOfVoters(0), m_rating(0), m_vipOnly(vipOnly), m_genre(genre)
{}//arnt checking input here, we'll check it in addMovie in StreamingDBa1

void Movie::addRating(double rating)
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

bool Movie::getVipOnly() const
{
    return m_vipOnly;
}

int Movie::getMovieId() const
{
    return m_movieId;
}

double Movie::getRating() const
{
    return m_rating;
}

const int Movie::getViews() const
{
    return m_views;
}

Genre Movie::getGenre() const
{
    return m_genre;
}

bool operator==(const Movie& a, const Movie& b)
{
    if (a.getMovieId() == b.getMovieId())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Movie::operator<(const Movie& other) const
{
    if(this->getMovieId() < other.getMovieId())
    {
        return true;
    }
    else
    {
        return false;
    }
}

//opposite of above function
bool Movie::operator>(const Movie& other) const
{
    if(this->getMovieId() < other.getMovieId())
    {
        return false;
    }
    else
    {
        return true;
    }
}
