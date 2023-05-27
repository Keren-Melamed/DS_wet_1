#include "Movie.h"
using namespace std;

/*Movie::Movie():
m_movieId(1), m_views(0), m_numOfVoters(0),m_rating(0), m_vipOnly(false), m_genre(Genre::NONE), m_flag(false)
{}*/

Movie::Movie(int movieID, int views, bool vipOnly, Genre genre, double rating, int numOfVoters, bool flag):
m_movieId(movieID), m_views(views), m_numOfVoters(numOfVoters), m_rating(rating), m_vipOnly(vipOnly), m_genre(genre), m_flag(flag)
{}


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

int Movie::getNumOfVoters() const
{
    return m_numOfVoters;
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

bool operator<(const Movie &a, const Movie &b)
{

    if(!a.getFlag())//the flag dictates we compare by movie ID
    {
        //cout << "the flags were false" << endl;
        if(a.getMovieId() > b.getMovieId())//opposite on purpose because the lower id values higher
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if(a.getRating() <= b.getRating())//the flag dictates we compare by rating
    {
        //cout << "the flags were true" << endl;
        if(a.getRating() == b.getRating())
        {
            if(a.getViews() <= b.getViews())
            {
                if(a.getViews() == b.getViews())
                {
                    return (a.getMovieId() > b.getMovieId());//under the assumption no 2 movies have the same id
                }
                return true;
            }
            return false;
        }
        return true;
    }
    //cout << "neither if was entered" << endl;
    return false;
}

bool operator>(const Movie &a, const Movie &b)
{
    if(a == b)
    {
        return false;
    }
    bool tmp = (a < b);
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

void Movie::print(std::ostream &os) const
{
    os << m_movieId << " ";
}




