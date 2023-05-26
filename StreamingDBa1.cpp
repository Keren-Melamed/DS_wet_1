#include "StreamingDBa1.h"
#include<memory>

/*
 * when do we need to use the flag in movie? do we ever use it even?
 */


streaming_database::streaming_database() = default;

streaming_database::~streaming_database()
{
    m_movies.setAllToNullptr(m_movies.getRoot());
}

void streaming_database::createTreeWithOppositeFlags(AVLTree<Movie>* newTree, Node<Movie>* node, Genre treeGenre, bool flag)////// no rating
{
    if(node == nullptr)
    {
        return;
    }
    createTreeWithOppositeFlags(newTree, node->getRightNode(),treeGenre, flag);

    int id = node->getValue()->getMovieId(), views = node->getValue()->getViews();
    Genre genre = node->getValue()->getGenre();
    bool vip = node->getValue()->getVipOnly();

    Movie* tmpMovie = new Movie(id, views, vip, genre, 0, false);
    Node<Movie>* movieNode = m_movies_by_genre[(int) genre]->findObject(
            m_movies_by_genre[(int) treeGenre]->getRoot(), tmpMovie);
    // searching for the movie to get its rating in the regular tree;
    delete tmpMovie;

    //we were adding in movies without the rating to the newTree(which is sorted by rating) hence why it wasn't working

    id = movieNode->getValue()->getMovieId();
    views = movieNode->getValue()->getViews();
    genre = movieNode->getValue()->getGenre();
    vip = movieNode->getValue()->getVipOnly();
    double rating = movieNode->getValue()->getRating();

    Movie* movieToAdd = new Movie(id, views, vip, genre, rating, true);
    try
    {
        newTree->insertValue(movieToAdd);
    }
    catch(BadAllocation& e)
    {
        throw BadAllocation();
    }
    createTreeWithOppositeFlags(newTree, node->getLeftNode(), treeGenre, flag);
}

void streaming_database::movieTreeToArray(Genre genre, int *const output, int* counter)
{
    output_t<int> tmp = this->get_all_movies_count(genre);
    int sizeOfArray = tmp.ans();

    AVLTree<Movie>* newTree = new AVLTree<Movie>;
    try
    {
        createTreeWithOppositeFlags(newTree, m_movies_by_genre[(int) genre]->getRoot(), genre, true);
    }
    catch(BadAllocation& e)
    {
        throw BadAllocation();
    }

    cout << "this is the new tree in movieTreeToArray: " << endl;
    newTree->inOrder(cout, newTree->getRoot());
    cout << endl;

    Movie** movieArray = new Movie*[sizeOfArray];
    newTree->treeToArrayInOrderRight(newTree->getRoot(), movieArray, sizeOfArray, counter);

    for (int i = 0; i < sizeOfArray; ++i)
    {
        output[i] = movieArray[i]->getMovieId();
    }

    delete[] movieArray;
    delete newTree;
}

void streaming_database::addMovieToGenreTree(Genre genre, Movie* movie)
{
    try
    {
        m_movies_by_genre[(int) genre]->insertValue(movie);
    }
    catch(BadAllocation& e)
    {
        throw BadAllocation();
    }
}

void streaming_database::removeMovieFromGenreTree(Genre genre, Movie* movie)
{
    Node<Movie>* movieNode = m_movies_by_genre[(int) genre]->findObject(m_movies_by_genre[(int) genre]->getRoot(), movie);
    if(movieNode == nullptr)
    {
        return;
    }
    
    m_movies_by_genre[(int) genre]->removeValue(movieNode->getValue());
    return;
   

}

StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)//insert by object
{
    if((movieId <= 0) || (views < 0) || (genre == Genre::NONE)){
        return StatusType::INVALID_INPUT;
    }
    Movie* movie = new Movie(movieId, views, vipOnly, genre, 0, false);
    Node<Movie>* tmp = m_movies.findObject(m_movies.getRoot(), movie);
    if(tmp == nullptr)
    {
        try
        {
            m_movies.insertValue(movie);
            addMovieToGenreTree(genre, movie);

            m_movies_in_genre[(int) genre] += 1;
            //delete move; causes tests to fail
        }
        catch (BadAllocation &e)
        {
            return StatusType::ALLOCATION_ERROR;
        }
    }
    else
    {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)//insert by object
{
    
    if(movieId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }


    Movie* temp = new Movie(movieId, 0, false, Genre::NONE, 0, false);
    Node<Movie>* movieNode = m_movies.findObject(m_movies.getRoot(), temp);

    if(movieNode == nullptr){
        delete temp;
        return StatusType::FAILURE;
    }

    else
    {   
        Genre temp_genre = movieNode->getValue()->getGenre();
        m_movies.removeValue(movieNode->getValue());
        
        removeMovieFromGenreTree(temp_genre, temp);
        m_movies_in_genre[(int) temp_genre] -= 1;
        delete temp;
        return StatusType::SUCCESS;
    }
}

StatusType streaming_database::add_user(int userId, bool isVip)//insert by object
{
    if(userId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    User* user = new User(userId, isVip);
    Node<User>* tmp = m_users.findObject(m_users.getRoot(), user);
    if(tmp == nullptr)
    {
        try
        {
            m_users.insertValue(user);
            //delete user; causes tests to fail
        }
        catch(BadAllocation& e)
        {
            return StatusType::ALLOCATION_ERROR;
        }
    }
    else
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)//find by object
{
    if(userId <= 0){
        return StatusType::INVALID_INPUT;
    }

    User* temp = new User(userId, false);
    Node<User>* userNode = m_users.findObject(m_users.getRoot(), temp);

    if(userNode != nullptr)
    {
        if(userNode->getValue()->getGroup() != nullptr)
        {
            AVLTree<User> *membersTree = (userNode->getValue()->getGroup()->getMembers());
            membersTree->removeValue(userNode->getValue());
            //delete membersTree; causes tests to fail
        }
        m_users.removeValue(userNode->getValue());
        delete temp;
    }
    else
    {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)//insert by object
{
    if(groupId <= 0){
        return StatusType::INVALID_INPUT;
    }

    Group* group = new Group(groupId, false, 0);
    Node<Group>* temp = m_groups.findObject(m_groups.getRoot(), group);

    if(temp != nullptr){
        return StatusType::FAILURE;
    }

    try{
        m_groups.insertValue(group);
        //delete group; causes tests to fail
    }

    catch(BadAllocation& e){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)//remove by object
{
    if(groupId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    Group* temp = new Group(groupId, false, 0);
    Node<Group>* groupNode = m_groups.findObject(m_groups.getRoot(), temp);

    if(groupNode == nullptr){
        return StatusType::FAILURE;
    }

    m_groups.removeValue(groupNode->getValue());
    groupNode->getValue()->dismantleGroup(groupNode->getValue()->getMembers()->getRoot());
    delete temp;

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
    Node<User>* userNode = m_users.findObject(m_users.getRoot(), temp_user);
    Node<Group>* groupNode = m_groups.findObject(m_groups.getRoot(), temp_group);

    if(userNode == nullptr || groupNode == nullptr)
    {
        if(userNode == nullptr)
        {
            //cout << "the userNode was null" << endl;
        }
        if(groupNode == nullptr)
        {
            //cout << "the groupNode was null" << endl;
        }
        delete temp_user;
        delete temp_group;
        return StatusType::FAILURE;
    }

    if(userNode->getValue()->getGroup() != nullptr)
    {
        delete temp_user;
        delete temp_group;
        return StatusType::FAILURE;
    }

    //add find to check if user is already in group
    Node<User>* temp = groupNode->getValue()->getMembers()->findObject(groupNode->getValue()->getMembers()->getRoot(),
                                                                       userNode->getValue());

    if(temp != nullptr)
    {
        delete temp_user;
        delete temp_group;
        return StatusType::FAILURE;
    }

    try{
        groupNode->getValue()->getMembers()->insertValue(userNode->getValue());
    }

    catch(BadAllocation& e)
    {
        delete temp_user;
        delete temp_group;
        return StatusType::ALLOCATION_ERROR;
    }

    Group *pointerGroup = (groupNode->getValue());
    userNode->getValue()->setGroup(pointerGroup);
    if(groupNode->getValue()->getIsVip() == false){
        if(userNode->getValue()->getIsVip() == true){
            groupNode->getValue()->setIsVip(true);
        }
    }
    for(int i = 0; i < 4; i++)
    {
        Genre genre = static_cast<Genre>(i);
        int viewsToAdd = userNode->getValue()->getMoviesUserWatchedInGenre(genre);
        groupNode->getValue()->updateMoviesGroupWatchedInGenre(genre, viewsToAdd);
    }
    groupNode->getValue()->updateGroupSize();

    delete temp_group;
    delete temp_user;

    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    if((userId <= 0) || (movieId <= 0)){
        return StatusType::INVALID_INPUT;
    }

    User* tempUser = new User(userId, false);
    Movie* tempMovie = new Movie(movieId, 0, false, Genre::NONE, 0, false);
    Node<User>* userNode = m_users.findObject(m_users.getRoot(), tempUser);
    Node<Movie>* movieNode = m_movies.findObject(m_movies.getRoot(), tempMovie);

    if(userNode == nullptr || movieNode == nullptr){
        delete tempMovie;
        delete tempUser;
        return StatusType::FAILURE;
    }

    if((userNode->getValue()->getIsVip() == false) && (movieNode->getValue()->getVipOnly() == true))
    {
        return StatusType::FAILURE;
    }

    userNode->getValue()->UpdateMoviesUserWatchedInGenre(movieNode->getValue()->getGenre());
    movieNode->getValue()->addViews(1);

    Group* user_group = userNode->getValue()->getGroup();
    if(user_group != nullptr)
    {
        user_group->updateMoviesGroupWatchedInGenre(movieNode->getValue()->getGenre(), 1);
    }

    delete tempMovie;
    delete tempUser;

    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    if((groupId <= 0) || (movieId <= 0))
    {
        return StatusType::INVALID_INPUT;
    }

    Group* tempGroup = new Group(groupId, false ,0);
    Movie* tempMovie = new Movie(movieId, 0, false, Genre::NONE, 0, false);
    Node<Group>* groupNode = m_groups.findObject(m_groups.getRoot(), tempGroup);
    Node<Movie>* movieNode = m_movies.findObject(m_movies.getRoot(), tempMovie);

    if(groupNode == nullptr || movieNode == nullptr)
    {
        delete tempMovie;
        delete tempGroup;
        return StatusType::FAILURE;
    }

    if(groupNode->getValue()->getMembers()->getRoot() == nullptr){
        return StatusType::FAILURE;
    }

    if((groupNode->getValue()->getIsVip() == false) && (movieNode->getValue()->getVipOnly() == true))
    {
        return StatusType::FAILURE;
    }
    groupNode->getValue()->addViewToMembers(groupNode->getValue()->getMembers()->getRoot() ,movieNode->getValue()->getGenre());
    groupNode->getValue()->updateMoviesGroupWatchedInGenre(movieNode->getValue()->getGenre(),
                                                           groupNode->getValue()->getGroupSize());
   
    movieNode->getValue()->addViews(groupNode->getValue()->getGroupSize());

    delete tempMovie;
    delete tempGroup;

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

    else
    {
        if(m_movies.getRoot() == nullptr)
        {
            return StatusType::FAILURE;
        }
        if(genre != Genre::NONE && m_movies_in_genre[(int)genre] == 0)
        {
            return StatusType::FAILURE;
        }

        else{
            int* counter = new int(0);
            movieTreeToArray(genre, output, counter);
            delete counter;
        }
        return StatusType::SUCCESS;
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
    Node<User>* node = m_users.findObject(m_users.getRoot(), tmp);

    if(node == nullptr){
        output_t<int> output(StatusType::FAILURE);
        delete tmp;
        return output;
    }

    User* user = node->getValue();
    int num = user->getMoviesUserWatchedInGenre(genre);
    output_t<int> output(num);
    delete tmp;
    return output;


}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    if (userId <= 0 || movieId <=0 || rating < 0 || rating > 100)
    {
        return StatusType::INVALID_INPUT;
    }

    User* tmpUser = new User(userId, false);
    Movie* tmpMovie = new Movie(movieId, 0, false, Genre::NONE, 0, false);// views is 0 !!!!!!!!!!!!!!
    Node<User>* userNode = m_users.findObject(m_users.getRoot(), tmpUser);
    Node<Movie>* movieNode = m_movies.findObject(m_movies.getRoot(), tmpMovie);
   
    if(userNode == nullptr || movieNode == nullptr)
    {
        delete tmpMovie;
        delete tmpUser;
        return StatusType::FAILURE;
    }

    delete tmpMovie;
    delete tmpUser;

    if(movieNode->getValue()->getVipOnly() == true && userNode->getValue()->getIsVip() == false)
    {
        return StatusType::FAILURE;
    }
    movieNode->getValue()->addRating(rating);
    return StatusType::SUCCESS;


}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
    if(groupId <= 0)
    {
        output_t<int> out(StatusType::INVALID_INPUT);
        return out;
    }

    Group* tempGroup = new Group(groupId, false ,0);
    Node<Group> *groupNode = m_groups.findObject(m_groups.getRoot(), tempGroup);
    
    if(groupNode == nullptr)
    {
        output_t<int> out(StatusType::FAILURE);
        return out;
    }

    delete tempGroup;

    if (groupNode->getValue()->getMembers()->getRoot() == nullptr) {
        output_t<int> out(StatusType::FAILURE);
        return out;
    }

    int max_views = 0;
    Genre fav_genre = Genre::NONE;
    for (int i = 3; i >= 0; i--) {
        Genre genre = static_cast<Genre>(i);
        if (groupNode->getValue()->getMoviesGroupWatchedInGenre(genre) > max_views) {
            max_views = groupNode->getValue()->getMoviesGroupWatchedInGenre(genre);
            fav_genre = genre;
        }
    }

    delete groupNode;

    if (m_movies_in_genre[(int) fav_genre] == 0) {
        output_t<int> out(StatusType::FAILURE);
        return out;
    }

    else if(m_movies_by_genre[(int) fav_genre]->getRoot() == nullptr)
    {
        output_t<int> out(StatusType::FAILURE);
        return out;
    }
    else
    {
        output_t<int> out(m_movies_by_genre[(int) fav_genre]->getRoot()->getValue()->getMovieId());
        return out;
    }

}


