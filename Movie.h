#ifndef WET1_MOVIE_H
#define WET1_MOVIE_H

#include "wet1util.h"
#include <iostream>

class Movie
{
    public:
        Movie(int movieID, int views, bool vipOnly, Genre genre, bool flag = false);

        ~Movie() = default;

        void addRating(double rating);
        
        void addViews(int views = 1);

        void setFlag(bool flag);

        bool getFlag() const;

        bool getVipOnly() const;

        int getViews() const;

        int getMovieId() const;

        double getRating() const;

        Genre getGenre() const;

        friend bool operator==(const Movie& a, const Movie& b);
        bool operator<(const Movie& other) const;
        bool operator>(const Movie& other) const;

    private:

        int m_movieId;
        int m_views;
        int m_numOfVoters;
        double m_rating;
        bool m_vipOnly;
        Genre m_genre;
        bool m_flag;// false = movie id first **** true = rating first

};
#endif