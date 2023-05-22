#include "StreamingDBa1.h"

streaming_database::streaming_database() = default;

/*streaming_database::streaming_database()
{
    AVLTree<Movie> m_movies;
    AVLTree<User> m_users;
    AVLTree<Group> m_groups;
    AVLTree<Movie> m_fantasy_movies;
    AVLTree<Movie> m_comedy_movies;
    AVLTree<Movie> m_action_movies;
    AVLTree<Movie> m_drama_movies;
}*/

streaming_database::~streaming_database() = default;

void streaming_database::movieTreeToArray(Node<Movie>* node, int *const output)
{
    static int pos = 0;
    if(node == nullptr){
        return;
    }

    movieTreeToArray(node->getLeftNode(), output);
    output[pos++] = node->getValue()->getMovieId();
    movieTreeToArray(node->getRightNode(), output);

}

AVLTree<Movie> streaming_database::getGenreTree(Genre genre)
{
    switch(genre){
        case Genre::FANTASY:
            return m_fantasy_movies;

        case Genre::COMEDY:
            return m_comedy_movies;

        case Genre::ACTION:
            return m_action_movies;

        case Genre::DRAMA:
            return m_drama_movies;

        default:
            AVLTree<Movie> tmpTree;
            return tmpTree;
    }
}

StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)//insert by object
{
    if((movieId <= 0) || (views < 0) || (genre == Genre::NONE)){
        return StatusType::INVALID_INPUT;
    }
    try{
        Movie* movie = new Movie(movieId, views, vipOnly, genre);

        m_movies.setRoot(m_movies.insertValue(m_movies.getRoot(), movie));

        getGenreTree(genre).setRoot(getGenreTree(genre).insertValue(getGenreTree(genre).getRoot(), movie));
        //isn't adding it to the actual tree in the database but creating a new one and adding it to there,
        //just to delete it when exiting the function
        

        m_movies_in_genre[(int)genre] += 1;
    }

    catch(BadAllocation& e){
        return StatusType::ALLOCATION_ERROR;
    }
    catch(NodeAlreadyExists& e){
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)//insert by object
{
    if(movieId <= 0){
        return StatusType::INVALID_INPUT;
    }

    try{
        Movie* temp = new Movie(movieId, 0, false, Genre::NONE);
        Node<Movie>* movieNode = m_movies.findObject(m_movies.getRoot(), temp);
        m_movies.setRoot(m_movies.removeValue(m_movies.getRoot(), movieNode->getValue()));

        getGenreTree(movieNode->getValue()->getGenre()).setRoot( //line was too long
                getGenreTree(movieNode->getValue()->getGenre()).removeValue(//line was still too long...
                getGenreTree(movieNode->getValue()->getGenre()).getRoot(), movieNode->getValue()));
    }

    catch(NodeDoesntExist& e){
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)//insert by object
{
    if(userId <= 0){
        return StatusType::INVALID_INPUT;
    }
    try{
        User* user = new User(userId, isVip);

        m_users.setRoot(m_users.insertValue(m_users.getRoot(), user));
    }

    catch(BadAllocation& e){
        return StatusType::ALLOCATION_ERROR;
    }
    catch(NodeAlreadyExists& e){
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)//find by object
{
    if(userId <= 0){
        return StatusType::INVALID_INPUT;
    }

    try{
        User* temp = new User(userId, false);
        Node<User>* userNode = m_users.findObject(m_users.getRoot(), temp);
        m_users.setRoot(m_users.removeValue(m_users.getRoot(), userNode->getValue()));
    }

    catch(NodeDoesntExist& e){
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)//insert by object
{
    if(groupId <= 0){
        return StatusType::INVALID_INPUT;
    }
    try{
        Group* group = new Group(groupId, false, 0);
        m_groups.setRoot(m_groups.insertValue(m_groups.getRoot(), group));
    }

    catch(BadAllocation& e){
        return StatusType::ALLOCATION_ERROR;
    }
    catch(NodeAlreadyExists& e){
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)//remove by object
{
    if(groupId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    try
    {
        Group* temp = new Group(groupId, false, 0);
        Node<Group>* groupNode = m_groups.findObject(m_groups.getRoot(), temp);
        m_groups.setRoot(m_groups.removeValue(m_groups.getRoot(), groupNode->getValue()));
        groupNode->getValue()->dismantleGroup(groupNode->getValue()->getMembers().getRoot());
    }

    catch(NodeDoesntExist& e)
    {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)//find and insert by object
{
    if((groupId <= 0) || (userId <= 0))
    {
        return StatusType::INVALID_INPUT;
    }

    User* temp_user = new User(userId, false);
    Group* temp_group = new Group(groupId, false ,0);

    try
    {
        Node<User>* userNode = m_users.findObject(m_users.getRoot(), temp_user);
        Node<Group>* groupNode = m_groups.findObject(m_groups.getRoot(), temp_group);

        if(userNode->getValue()->getGroup() != nullptr)
        {
            return StatusType::FAILURE;
        }
        try
        {
            groupNode->getValue()->getMembers().setRoot(groupNode->getValue()->getMembers().insertValue(//line was too long...
                    groupNode->getValue()->getMembers().getRoot(),userNode->getValue()));

            Group *pointerGroup = (groupNode->getValue());
            userNode->getValue()->setGroup(pointerGroup);
            if(groupNode->getValue()->getIsVip() == true){
                if(userNode->getValue()->getIsVip() == false){
                    groupNode->getValue()->setIsVip(false);
                }
            }

            for(int i = 0; i < 4; i++)
            {
                Genre genre = static_cast<Genre>(i);
                int viewsToAdd = userNode->getValue()->getMoviesUserWatchedInGenre(genre);
                groupNode->getValue()->updateMoviesGroupWatchedInGenre(genre, viewsToAdd);
            }
            groupNode->getValue()->updateGroupSize();
        }
        catch(BadAllocation& e){
            return StatusType::ALLOCATION_ERROR;
        }
    }
    catch(NodeDoesntExist& e)
    {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    if((userId <= 0) || (movieId <= 0)){
        return StatusType::INVALID_INPUT;
    }

    User* tempUser = new User(userId, false);
    Movie* tempMovie = new Movie(movieId, 0, false, Genre::NONE);
    try
    {
        Node<User>* userNode = m_users.findObject(m_users.getRoot(), tempUser);
        Node<Movie>* movieNode = m_movies.findObject(m_movies.getRoot(), tempMovie);

        if((userNode->getValue()->getIsVip() == false) && (movieNode->getValue()->getVipOnly() == true))
        {
            return StatusType::FAILURE;
        }

        userNode->getValue()->UpdateMoviesUserWatchedInGenre(movieNode->getValue()->getGenre());
        movieNode->getValue()->addViews(1);

        Group* user_group = userNode->getValue()->getGroup();
        if(user_group != nullptr)
        {
            user_group->updateMoviesGroupWatchedInGenre(movieNode->getValue()->getGenre());
        }
    }
    catch(NodeDoesntExist& e)
    {
        return StatusType::FAILURE;
    }


    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    if((groupId <= 0) || (movieId <= 0))
    {
        return StatusType::INVALID_INPUT;
    }

    Group* tempGroup = new Group(groupId, false ,0);
    Movie* tempMovie = new Movie(movieId, 0, false, Genre::NONE);

    try
    {
        Node<Group>* groupNode = m_groups.findObject(m_groups.getRoot(), tempGroup);
        Node<Movie>* movieNode = m_movies.findObject(m_movies.getRoot(), tempMovie);

        if(groupNode->getValue()->getMembers().getRoot() == nullptr){
            return StatusType::FAILURE;
        }

        if((groupNode->getValue()->getIsVip() == false) && (movieNode->getValue()->getVipOnly() == true))
        {
            return StatusType::FAILURE;
        }

        groupNode->getValue()->updateMoviesGroupWatchedInGenre(movieNode->getValue()->getGenre());
        movieNode->getValue()->addViews(groupNode->getValue()->getGroupSize());
    }
    catch(NodeDoesntExist& e)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;

}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    if(genre != Genre::NONE)
    {
        output_t<int> out(m_movies_in_genre[(int)genre]);
        return out;
    }
    else
    {
        int ret_movies = 0;
        for(int i = 0; i < 4; i++){
            ret_movies += m_movies_in_genre[i];
        }
        output_t<int> out(ret_movies);
        return out;
    }
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    if(output == nullptr){
        return StatusType::INVALID_INPUT;
    }

    if(genre == Genre::NONE)
    {
        if(m_movies.getRoot() == nullptr){
            return StatusType::FAILURE;
        }

        else{
            movieTreeToArray(m_movies.getRoot(), output);
            return StatusType::SUCCESS;
        }
    }

    else{
        if(m_movies_in_genre[(int)genre] == 0){
            return StatusType::FAILURE;
        }

        else{
            AVLTree<Movie> genre_tree = getGenreTree(genre);
            movieTreeToArray(genre_tree.getRoot(), output);
            return StatusType::SUCCESS;
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
    User* tmp = new User(userId, false);
    try
    {
        Node<User>* node = m_users.findObject(m_users.getRoot(), tmp);
        User* user = node->getValue();
        int num = user->getMoviesUserWatchedInGenre(genre);
        output_t<int> output(num);
        return output;
    }
    catch(NodeDoesntExist& e)
    {
        output_t<int> output(StatusType::FAILURE);
        return output;
    }

}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    if (userId <= 0 || movieId <=0 || rating < 0 || rating > 100)
    {
        return StatusType::INVALID_INPUT;
    }

    User* tmpUser = new User(userId, false);
    Movie* tmpMovie = new Movie(movieId, 0 , false, Genre::COMEDY);
    try
    {
        Node<User>* userNode = m_users.findObject(m_users.getRoot(), tmpUser);
        Node<Movie>* movieNode = m_movies.findObject(m_movies.getRoot(), tmpMovie);
        if(movieNode->getValue()->getVipOnly() != userNode->getValue()->getIsVip())
        {
            return StatusType::FAILURE;
        }
        movieNode->getValue()->addRating(rating);
        return StatusType::SUCCESS;
    }
    catch(NodeDoesntExist& e)
    {
        return StatusType::FAILURE;
    }
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
    if(groupId <= 0)
    {
        output_t<int> out(StatusType::INVALID_INPUT);
        return out;
    }

    Group* tempGroup = new Group(groupId, false ,0);
    try
    {
        Node<Group>* groupNode = m_groups.findObject(m_groups.getRoot(), tempGroup);

        if(groupNode->getValue()->getMembers().getRoot() == nullptr)
        {
            output_t<int> out(StatusType::FAILURE);
            return out;
        }

        int max_views = 0;
        Genre fav_genre = Genre::NONE;
        for(int i = 3; i >= 0; i--)
        {
            Genre genre = static_cast<Genre>(i);
            if(groupNode->getValue()->getMoviesGroupWatchedInGenre(genre) > max_views){
                max_views = groupNode->getValue()->getMoviesGroupWatchedInGenre(genre);
                fav_genre = genre;
            }
        }

        if(m_movies_in_genre[(int)fav_genre] == 0)
        {
            output_t<int> out(StatusType::FAILURE);
            return out;
        }

        AVLTree<Movie> movies_in_genre = getGenreTree(fav_genre);

        if(movies_in_genre.getRoot() == nullptr)
        {
            output_t<int> out(StatusType::FAILURE);
            return out;
        }
        else
        {
            output_t<int> out(movies_in_genre.getRoot()->getValue()->getMovieId());
            return out;
        }
    }
    catch(NodeDoesntExist& e)
    {
        output_t<int> out(StatusType::FAILURE);
        return out;
    }
}



/*
 add_group 6567
 add_user 9744 False
 add_user_to_group 9744 6567

 */