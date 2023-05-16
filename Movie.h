#ifndef WET1_MOVIE_H
#define WET1_MOVIE_H

#include "wet1util.h"

class Movie
{
    public:
        Movie(int movieID, int views, bool vipOnly, Genre genre);

        ~Movie() = default;

        void addRating(double rating);
        
        void addViews(int views);

        bool getVipOnly() const;

        const int getViews() const;

        int getMovieId() const;

        double getRating() const;

        Genre getGenre() const;


    private:

        friend bool operator==(const Movie& a, const Movie& b);
        bool operator<(const Movie& other) const;
        bool operator>(const Movie& other) const;



        int m_movieId;
        int m_views;
        int m_numOfVoters;
        double m_rating;
        bool m_vipOnly;
        Genre m_genre;

};
#endif