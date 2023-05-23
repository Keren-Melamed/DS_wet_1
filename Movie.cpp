#include "Movie.h"

Movie::Movie():
m_movieId(1), m_views(0), m_numOfVoters(0),m_rating(0), m_vipOnly(false), m_genre(Genre::NONE), m_flag(false)
{}

Movie::Movie(int movieID, int views, bool vipOnly, Genre genre, bool flag):
m_movieId(movieID), m_views(views), m_numOfVoters(0), m_rating(0), m_vipOnly(vipOnly), m_genre(genre), m_flag(flag)
{}
//arnt checking input here, we'll check it in addMovie in StreamingDBa1

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

int Movie::getViews() const
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
    if(this->getFlag() != other.getFlag())
    {
        std::cout << "the movie flags are different" << std::endl;//should never be happen
    }
    if(!this->getFlag())//the flag dictates we compare by movie ID
    {
        if(this->getMovieId() > other.getMovieId())//opposite on purpose because the lower id values higher
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if(this->getRating() <= other.getRating())//the flag dictates we compare by rating
    {
        if(this->getRating() == other.getRating())
        {
            if(this->getViews() <= other.getViews())
            {
                if(this->getViews() == other.getViews())
                {
                    return (this->getMovieId() > other.getMovieId());//under the assumption no 2 movies have the same id
                }
                return true;
            }
            return false;
        }
        return true;
    }

    return false;
}
//under the assumption no 2 movies have the same id

//opposite of above function
bool Movie::operator>(const Movie& other) const
{
    if(this->getFlag() != other.getFlag())
    {
        std::cout << "the movie flags are different" << std::endl;
    }
    bool tmp = (*this < other);
    return (!tmp);//I feel like this should work
}

void Movie::setFlag(bool flag)
{
    m_flag = flag;
}

bool Movie::getFlag() const
{
    return m_flag;
}


