#include "Movie.h"
#include "StreamingDBa1.h"
using namespace std;


Movie::Movie(int movieID, int views, bool vipOnly, Genre genre, double rating, bool flag):
m_movieId(movieID), m_views(views), m_numOfVoters(0), m_rating(rating), m_vipOnly(vipOnly), m_genre(genre), m_flag(flag)
{}
//arnt checking input here, we'll check it in addMovie in StreamingDBa1

void Movie::addRating(double rating)
{
    if (rating > 0 && rating < 100)
    {
        if(m_numOfVoters == 0){
            m_rating = rating;
        }
        else{
            rating += m_rating * m_numOfVoters;
            m_numOfVoters++;
            m_rating = rating / m_numOfVoters;
        }

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

bool operator<(const Movie &a, const Movie &b)
{
    if(a.getFlag() != b.getFlag())
    {
        cout << "the movie flags are different" << endl;//should never be happen
    }

    if(!a.getFlag()){
        if(a.getMovieId() > b.getMovieId()){
            return true;
        }
        return false;
    }

    else{
        if(a.getRating() > b.getRating()){
            return true;
        }

        if(a.getRating() < b.getRating()){
            return false;
        }

        if(a.getRating() == b.getRating()){
            if(a.getViews() > b.getViews()){
                return true;
            }
            if(a.getViews() < b.getViews()){
                return false;
            }
            if(a.getViews() == b.getViews()){
                if(a.getMovieId() > b.getMovieId()){
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}
    

bool operator>(const Movie &a, const Movie &b)
{
    if(a.getFlag() != b.getFlag())
    {
        std::cout << "the movie flags are different" << std::endl;
    }
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


