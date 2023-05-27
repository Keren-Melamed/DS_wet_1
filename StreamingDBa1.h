// 
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef STREAMINGDBA1_H_
#define STREAMINGDBA1_H_

#include "wet1util.h"
#include "Movie.h"
#include "User.h"
#include "Group.h"
#include "AVLTree.h"
#include "exception.h"

class streaming_database {
private:

    int m_movies_in_genre[4] = {0};

    AVLTree<User> m_users;
    AVLTree<Movie> m_movies;
    AVLTree<Group> m_groups;
    AVLTree<Movie> m_fantasy_movies;
    AVLTree<Movie> m_comedy_movies;
    AVLTree<Movie> m_action_movies;
    AVLTree<Movie> m_drama_movies;
    AVLTree<Movie> m_movies_ranked;
    AVLTree<Movie> m_fantasy_movies_by_rating;
    AVLTree<Movie> m_comedy_movies_by_rating;
    AVLTree<Movie> m_action_movies_by_rating;
    AVLTree<Movie> m_drama_movies_by_rating;

    void addMovieToGenreTree(Genre genre, Movie *movie);
    void addMovieToGenreTreeRanked(Genre genre, Movie* movieWithFlag);

    void removeMovieFromGenreTree(Genre genre, Movie* movie);
    void removeMovieFromGenreTreeRanked(Genre genre, Movie* movieWithFlag);

    StatusType rateRemoveAndAddMovie(Node<Movie>* movieNode, double rating);
    StatusType viewRemoveAndAddMovie(Node<Movie>* movieNode, int views);



    AVLTree<Movie>* m_movies_by_genre[5] = {&m_comedy_movies, &m_drama_movies, &m_action_movies,
                                            &m_fantasy_movies, &m_movies};

    AVLTree<Movie>* m_movies_by_genre_by_rank[5] = {&m_comedy_movies_by_rating, &m_drama_movies_by_rating,
                                                    &m_action_movies_by_rating,
                                            &m_fantasy_movies_by_rating, &m_movies_ranked};

public:



    // <DO-NOT-MODIFY> {

    streaming_database();

    virtual ~streaming_database();

    StatusType add_movie(int movieId, Genre genre, int views, bool vipOnly);

    StatusType remove_movie(int movieId);

    StatusType add_user(int userId, bool isVip);

    StatusType remove_user(int userId);

    StatusType add_group(int groupId);

    StatusType remove_group(int groupId);

    StatusType add_user_to_group(int userId, int groupId);

    StatusType user_watch(int userId, int movieId);

    StatusType group_watch(int groupId,int movieId);

    output_t<int> get_all_movies_count(Genre genre);

    StatusType get_all_movies(Genre genre, int *const output);

    output_t<int> get_num_views(int userId, Genre genre);

    StatusType rate_movie(int userId, int movieId, int rating);

    output_t<int> get_group_recommendation(int groupId);

    // } </DO-NOT-MODIFY>
};

#endif // STREAMINGDBA1_H_