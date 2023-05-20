#include "StreamingDBa1.h"

streaming_database::streaming_database()
{
    // TODO: Your code goes here
}

streaming_database::~streaming_database()
{
    // TODO: Your code goes here
}

void streaming_database::movieTreeToArray(Node<Movie>* node, int *const output)
{
    static int pos = 0;
    if(node == NULL){
        return;
    }

    TreetoArray(node->getLeftNode(), output);
    output[pos++] = node->getValue()->getMovieId();
    TreetoArray(node->getRightNode, output);

}

void streaming_database::MoviesInGenre(Node<Movie>* node, Genre genre, Node<Movie>* movies_in_genre)
{
    if(node == NULL){
        return;
    }

    MoviesInGenre(node->getLeftNode, genre, movies_in_genre);
    if(node->getGenre() == genre){
        InsertValue(movies_in_genre, node);
    }
    MoviesInGenre(node->getRightNode, genre, movies_in_genre);
}

StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if((movieId <= 0) || (views < 0) || (genre == NONE)){
        return StatusType::INVALID_INPUT;
    }
    try{
        movie = new Movie(movieId, genre, views, vipOnly);

        m_movies.insertValue(m_movies.getRoot(), movie);

        m_movies_in_genre[genre] += 1;
    }

    catch(BadAllocation& e){
        return StatusType::ALLOCATION_ERROR;
    }
    catch(NodeAlreadyExists& e){
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
    if(movieId <= 0){
        return StatusType::INVALID_INPUT;
    }

    try{
        m_movies.removeValue(m_movies.getRoot(), movieId);
    }

    catch(NodeDoesntExist& e){
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
    if(userId <= 0){
        return StatusType::INVALID_INPUT;
    }
    try{
        user = new User(userId,isVip);

        m_users.insertValue(m_users.getRoot(), user);
    }

    catch(BadAllocation& e){
        return StatusType::ALLOCATION_ERROR;
    }
    catch(NodeAlreadyExists& e){
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
    if(userId <= 0){
        return StatusType::INVALID_INPUT;
    }

    try{
        m_users.removeValue(m_users.getRoot(), userId);
    }

    catch(NodeDoesntExist& e){
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
    if(groupId <= 0){
        return StatusType::INVALID_INPUT;
    }
    try{
        group = new Group(groupId);

        m_groups.insertValue(m_groups.getRoot(), group);
    }

    catch(BadAllocation& e){
        return StatusType::ALLOCATION_ERROR;
    }
    catch(NodeAlreadyExists& e){
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)//alloc error catch
{
    if(groupId <= 0){
        return StatusType::INVALID_INPUT;
    }

    try{
        m_groups.removeValue(m_groups.getRoot(), groupId);
        group = m_groups.FindObject(m_groups.getRoot(), groupId);
        group.dismantleGroup(group.getRoot());
    }

    catch(NodeDoesntExist& e){
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    if((groupId <= 0) || (userId <= 0)){
        return StatusType::INVALID_INPUT;
    }

    User user = m_users.FindObject(m_users.getRoot(), userId);
    Group group = m_groups.FindObject(m_groups.getRoot(), groupId);

    if((user == nullptr) || (group == nullptr)){
        return StatusType::FAILURE;
    }

    if(user->getGroup() != nullptr){
        return StatusType::FAILURE;
    }

    try{
        m_group.insertValue(m_group.getRoot(), user);
        user.setGroup(group);
        if(group.getIsVip() == false){
            if(user.getIsVip() == true){
                group.setIsVip(true);
            }
        }

        for(int i = 0; i <= 4; i++){
            group.setMoviesGroupWatchedInGenre(i, group.getMoviesGroupWatchedInGenre(i) + user.getMoviesUserWatchedInGenre(i));
        }

        group.UpdateGroupSize();
    }

    catch(BadAllocation& e){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    if((userId <= 0) || (movieId <= 0)){
        return StatusType::INVALID_INPUT;
    }

    User user = m_users.FindObject(m_users.getRoot(), userId);
    Movie movie = m_movies.FindObject(m_movies.getRoot(), movieId);

    if((user == nullptr) || (movie == nullptr)){
        return StatusType::FAILURE;
    }

    if(user.getIsVip() == false) && (movie.getVipOnly() == true){
        return StatusType::FAILURE;
    }

    user.UpdateMoviesUserWatchedInGenre(movie.getGenre());
    movie.addViews(1);

    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    if((groupId <= 0) || (movieId <= 0)){
        return StatusType::INVALID_INPUT;
    }

    Group group = m_groups.FindObject(m_groups.getRoot(), groupId);
    Movie movie = m_movies.FindObject(m_movies.getRoot(), movieId);

    if(group.getRoot() == nullptr){
        return StatusType::FAILURE;
    }

    if(group.getIsVip() == false) && (movie.getVipOnly() == true){
        return StatusType::FAILURE;
    }

    group.UpdateMoviesGroupWatchedInGenre(movie.getGenre());

    movie.addviews(group.getGroupSize());

    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    if(genre != NONE){
        out = new output_t<int>(m_movies_in_genre[genre]);
    }
    else{
        int ret_movies = 0;
        for(int i = 0; i <= 4; i++){
            ret_movies += m_movies_in_genre[i];
        }
        out = new output_t<int>(ret_movies);
    }
    return out;
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    if(output == NULL){
        return StatusType::INVALID_INPUT;
    }

    if(genre == NONE)
    {
        if(m_movies.getRoot() == NULL){
            return StatusType::FAILURE;
        }

        else{
            MovieTreeToArray(m_movies.getRoot(), output);
            return StatusType:SUCCESS;
        }
    }

    else{
        if(m_movies_in_genre[genre] == 0){
            return StatusType:FALIURE;
        }

        else{
            AVLTree<Movie> curr_movies = new AVLTree<Movie>;
            MoviesInGenre(m_movies.getRoot(), genre, curr_movies);
            MovieTreeToArray(curr_movies.getRoot(), output);
        }
    }

}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    if(userId <= 0)
    {
        output_t<int> output(StatusType::INVALID_INPUT);
        return output;
    }
    User tmp(userId, false);
    Node<User>* node = m_users.findObject(m_users.getRoot(), tmp);
    if (node == nullptr)
    {
        output_t<int> output(StatusType::FAILURE);
        return output;
    }
    User user = node->getValue();
    int num = user.getMoviesUserWatchedInGenre(genre);
    output_t<int> output(num);
    return output;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    if (userId <= 0 || movieId <=0 || rating < 0 || rating > 100)
    {
        return StatusType::INVALID_INPUT;
    }

    User tmpUser(userId, false);
    Movie tmpMovie(movieId, 0 , false, Genre::COMEDY);
    try
    {
        Node<User>* userNode = m_users.findObject(m_users.getRoot(), tmpUser);
        Node<Movie>* movieNode = m_movies.findObject(m_movies.getRoot(), tmpMovie);
        if(movieNode->getValue().getVipOnly() != userNode->getValue().getIsVip())
        {
            return StatusType::FAILURE;
        }
        movieNode->getValue().addRating(rating);
        return StatusType::SUCCESS;
    }
    catch(NodeDoesntExists& e)
    {
        return StatusType::FAILURE;
    }
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

