#ifndef WET1_MOVIE_H
#define WET1_MOVIE_H

#include "wet1util.h"

class Movie
{
    public:
        Movie(int movieID,int views, bool vipOnly, Genre genre);

        ~Movie() = default;

        void addRating(int rating);
        
        void addViews(int views);

        bool getVipOnly();

        int getViews();

        int getMovieId();

        int getRating();

        Genre getGenre();


    private:
        int m_movieId;
        int m_views;
        int m_numOfVoters;
        double m_rating;
        bool m_vipOnly;
        Genre m_genre;

};
#endif