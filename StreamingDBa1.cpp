#include "StreamingDBa1.h"
#include<memory>




streaming_database::streaming_database() = default;

streaming_database::~streaming_database()
{
    m_movies.setAllToNullptr(m_movies.getRoot());
    m_movies_ranked.setAllToNullptr(m_movies_ranked.getRoot());
}

void streaming_database::addMovieToGenreTree(Genre genre, Movie* movie)
{
    cout<<"adding movie "<<movie->getMovieId()<<" to genre tree "<<(int) genre<<endl;
    try
    {
        m_movies_by_genre[(int) genre]->insertValue(movie);
    }
    catch(BadAllocation& e)
    {
        throw BadAllocation();
    }
}

void streaming_database::addMovieToGenreTreeRanked(Genre genre, Movie* movieWithFlag)
{
    cout<<"adding movie "<<movieWithFlag->getMovieId()<<" from genre tree ranked "<<(int) genre<<endl;
    try
    {
        m_movies_by_genre_by_rank[(int) genre]->insertValue(movieWithFlag);
    }
    catch (BadAllocation &e)
    {
        throw BadAllocation();
    }
}

void streaming_database::removeMovieFromGenreTree(Genre genre, Movie* movie)
{
    cout<<"removing movie "<<movie->getMovieId()<<" to genre tree "<<(int) genre<<endl;

    Node<Movie>* movieNode = m_movies_by_genre[(int) genre]->findObject(
            m_movies_by_genre[(int) genre]->getRoot(), movie);
    if(movieNode == nullptr)
    {
        return;
    }

    m_movies_by_genre[(int) genre]->removeValue(movieNode->getValue());
}

void streaming_database::removeMovieFromGenreTreeRanked(Genre genre, Movie* movieWithFlag)
{
    cout<<"removing movie "<<movieWithFlag->getMovieId()<<" from genre tree ranked "<<(int) genre<<endl;

    Node<Movie>* movieNodeWithFlag = m_movies_by_genre_by_rank[(int) genre]->findObject(
            m_movies_by_genre_by_rank[(int) genre]->getRoot(), movieWithFlag);
    if(movieNodeWithFlag == nullptr)
    {
        return;
    }

    m_movies_by_genre_by_rank[(int) genre]->removeValue(movieNodeWithFlag->getValue());
}

StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)//insert by object
{
    cout<<"add_movie: adding movie "<<movieId<<"  to genre "<<(int) genre<<endl;
    if((movieId <= 0) || (views < 0) || (genre == Genre::NONE)){
        return StatusType::INVALID_INPUT;
    }
    Movie* movie = new Movie(movieId, views, vipOnly, genre, 0, 0, false);
    Node<Movie>* tmp = m_movies.findObject(m_movies.getRoot(), movie);

    if (tmp != nullptr)
    {
        delete movie;
        return StatusType::FAILURE;
    }


    Movie* movieWithFlag = new Movie(movieId, views, vipOnly, genre, 0, 0, true);
    Node<Movie>* tmpWithFlag = m_movies_ranked.findObject(m_movies_ranked.getRoot(), movieWithFlag);

    if (tmpWithFlag != nullptr)
    {
        delete movie;
        delete movieWithFlag;
        return StatusType::FAILURE;
    }
    else
    {
        try
        {
            m_movies.insertValue(movie);
            m_movies_ranked.insertValue(movieWithFlag);
            addMovieToGenreTree(genre, movie);
            addMovieToGenreTreeRanked(genre, movieWithFlag);

            m_movies_in_genre[(int) genre] += 1;
            //delete movie; causes tests to fail
        }
        catch (BadAllocation &e)
        {
            return StatusType::ALLOCATION_ERROR;
        }
    }


    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)//insert by object
{
    cout<<"remove_movie: removing movie "<<movieId <<endl;

    if(movieId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }


    Movie* tmp = new Movie(movieId, 0, false, Genre::NONE, 0, 0, false);
    Node<Movie>* movieNode = m_movies.findObject(m_movies.getRoot(), tmp);

    if(movieNode == nullptr)
    {
        delete tmp;
        return StatusType::FAILURE;
    }

    Movie* tmpRegular = new Movie(movieId, movieNode->getValue()->getViews(), movieNode->getValue()->getVipOnly(),
                                   movieNode->getValue()->getGenre(),movieNode->getValue()->getRating(),
                                   movieNode->getValue()->getNumOfVoters(), false);

    Movie* tmpWithFlag = new Movie(movieId, movieNode->getValue()->getViews(), movieNode->getValue()->getVipOnly(),
                                   movieNode->getValue()->getGenre(),movieNode->getValue()->getRating(),
                                   movieNode->getValue()->getNumOfVoters(), true);
    Node<Movie>* movieNodeWithFlag = m_movies_ranked.findObject(m_movies_ranked.getRoot(), tmpWithFlag);

    if(movieNodeWithFlag == nullptr)
    {
        delete tmp;
        delete tmpWithFlag;
        return StatusType::FAILURE;
    }
    else
    {
        Genre temp_genre = movieNode->getValue()->getGenre();

        m_movies.removeValue(movieNode->getValue());
        m_movies_ranked.removeValue(movieNodeWithFlag->getValue());
        removeMovieFromGenreTree(temp_genre, tmpRegular);
        removeMovieFromGenreTreeRanked(temp_genre, tmpWithFlag);

        m_movies_in_genre[(int) temp_genre] -= 1;
        delete tmp;
        delete tmpRegular;
        delete tmpWithFlag;
        //delete movieNode->getValue();
        return StatusType::SUCCESS;
    }
}

StatusType streaming_database::add_user(int userId, bool isVip)//insert by object
{
    cout<<"add_user: adding user "<< userId<<endl;
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
        delete user;
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)//find by object
{
    cout<<"remove_user: removing user "<< userId<<endl;
    if(userId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    User* temp = new User(userId, false);
    Node<User>* userNode = m_users.findObject(m_users.getRoot(), temp);
    delete temp;

    if(userNode != nullptr)
    {
        if(userNode->getValue()->getGroup() != nullptr)
        {
            AVLTree<User> *membersTree = (userNode->getValue()->getGroup()->getMembers());
            membersTree->removeValue(userNode->getValue());
            for(int i = 0; i < 4; ++i)
            {
                Genre genre = static_cast<Genre>(i);
                int viewsToRemove = userNode->getValue()->getMoviesUserWatchedInGenre(genre);
                userNode->getValue()->getGroup()->updateMoviesGroupWatchedInGenre(genre, viewsToRemove);
            }
            //delete membersTree; causes tests to fail
        }
        m_users.removeValue(userNode->getValue());
    }
    else
    {
        return StatusType::FAILURE;
    }

    //delete userNode->getValue();
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)//insert by object
{
    cout<<"add_group: adding group "<< groupId<<endl;
    if(groupId <= 0){
        return StatusType::INVALID_INPUT;
    }

    Group* group = new Group(groupId, false, 0);
    Node<Group>* temp = m_groups.findObject(m_groups.getRoot(), group);

    if(temp != nullptr)
    {
        delete group;
        return StatusType::FAILURE;
    }

    try
    {
        m_groups.insertValue(group);
        //delete group; causes tests to fail
    }

    catch(BadAllocation& e)
    {
        delete group;
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)//remove by object
{
    cout<<"remove_group: removing group "<< groupId<<endl;
    if(groupId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    Group* temp = new Group(groupId, false, 0);
    Node<Group>* groupNode = m_groups.findObject(m_groups.getRoot(), temp);
    delete temp;

    if(groupNode == nullptr)
    {
        return StatusType::FAILURE;
    }

    m_groups.removeValue(groupNode->getValue());
    groupNode->getValue()->dismantleGroup(groupNode->getValue()->getMembers()->getRoot());


    //delete groupNode->getValue();

    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)//find and insert by object
{
    cout<<"add_user_to_group: adding user "<< userId<<" to group "<<groupId<<endl;
    if((groupId <= 0) || (userId <= 0))
    {
        return StatusType::INVALID_INPUT;
    }

    User* temp_user = new User(userId, false);
    Group* temp_group = new Group(groupId, false ,0);
    Node<User>* userNode = m_users.findObject(m_users.getRoot(), temp_user);
    Node<Group>* groupNode = m_groups.findObject(m_groups.getRoot(), temp_group);
    delete temp_user;
    delete temp_group;

    if(userNode == nullptr || groupNode == nullptr)
    {
        return StatusType::FAILURE;
    }

    if(userNode->getValue()->getGroup() != nullptr)
    {

        return StatusType::FAILURE;
    }


    Node<User>* temp = groupNode->getValue()->getMembers()->findObject(
                                        groupNode->getValue()->getMembers()->getRoot(),userNode->getValue());

    if(temp != nullptr)
    {
        return StatusType::FAILURE;
    }

    try
    {
        groupNode->getValue()->getMembers()->insertValue(userNode->getValue());
    }
    catch(BadAllocation& e)
    {

        return StatusType::ALLOCATION_ERROR;
    }

    userNode->getValue()->setGroup(groupNode->getValue());
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

    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    cout<<"user_watch: user "<< userId<<" watched movie "<<movieId<<endl;
    //need to possibly rebalance(remove the movie and add it back) the tree by rank after a movie has been watched cause its "size" changed
    if((userId <= 0) || (movieId <= 0)){
        return StatusType::INVALID_INPUT;
    }

    User* tmpUser = new User(userId, false);
    Movie* tmpMovie = new Movie(movieId, 0, false, Genre::NONE, 0, 0, false);

    Node<User>* userNode = m_users.findObject(m_users.getRoot(), tmpUser);
    Node<Movie>* movieNode = m_movies.findObject(m_movies.getRoot(), tmpMovie);

    delete tmpMovie;
    delete tmpUser;

    if(userNode == nullptr || movieNode == nullptr)
    {
        return StatusType::FAILURE;
    }

    if((userNode->getValue()->getIsVip() == false) && (movieNode->getValue()->getVipOnly() == true))
    {
        return StatusType::FAILURE;
    }

    Movie* tmpMovieWithFlag = new Movie(movieId, movieNode->getValue()->getViews(), movieNode->getValue()->getVipOnly(),
                                       movieNode->getValue()->getGenre(),movieNode->getValue()->getRating(),
                                       movieNode->getValue()->getNumOfVoters(), true);
    Node<Movie>* movieNodeWithFlag = m_movies_ranked.findObject(m_movies_ranked.getRoot(), tmpMovieWithFlag);

    if(movieNodeWithFlag == nullptr)
    {
        return StatusType::FAILURE;
    }

    movieNode->getValue()->addViews(1);
    userNode->getValue()->UpdateMoviesUserWatchedInGenre(movieNode->getValue()->getGenre());

    if(userNode->getValue()->getGroup() != nullptr)
    {
        userNode->getValue()->getGroup()->updateMoviesGroupWatchedInGenre(movieNode->getValue()->getGenre(), 1);
    }

    Genre genre = movieNode->getValue()->getGenre();
    m_movies_ranked.removeValue(movieNodeWithFlag->getValue());//maybe tmpMovieWithFlag?
    m_movies_by_genre_by_rank[(int) genre]->removeValue(movieNodeWithFlag->getValue());//here too; // there's a func for this
    tmpMovieWithFlag->addViews(1);
    try
    {
        m_movies_ranked.insertValue(tmpMovieWithFlag);
        m_movies_by_genre_by_rank[(int) genre]->insertValue(tmpMovieWithFlag);
    }
    catch(BadAllocation& e)
    {
        delete tmpMovieWithFlag;
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    cout<<"group_watch: group "<< groupId<<" watched movie "<<movieId<<endl;
    //need to possibly rebalance(remove the movie and add it back) the tree by rank after a movie has been watched cause its "size" changed
    if((groupId <= 0) || (movieId <= 0))
    {
        return StatusType::INVALID_INPUT;
    }

    Group* tmpGroup = new Group(groupId, false ,0);
    Movie* tmpMovie = new Movie(movieId, 0, false, Genre::NONE, 0, 0, false);
    Node<Group>* groupNode = m_groups.findObject(m_groups.getRoot(), tmpGroup);
    Node<Movie>* movieNode = m_movies.findObject(m_movies.getRoot(), tmpMovie);
    delete tmpMovie;
    delete tmpGroup;

    if(groupNode == nullptr || movieNode == nullptr)
    {
        return StatusType::FAILURE;
    }

    Movie* tmpMovieWithFlag = new Movie(movieId, movieNode->getValue()->getViews(), movieNode->getValue()->getVipOnly(),
                                       movieNode->getValue()->getGenre(),movieNode->getValue()->getRating(),
                                       movieNode->getValue()->getNumOfVoters(),true);
    Node<Movie>* movieNodeWithFlag = m_movies_ranked.findObject(m_movies_ranked.getRoot(), tmpMovieWithFlag);

    if(movieNodeWithFlag == nullptr)
    {
        return StatusType::FAILURE;
    }

    if(groupNode->getValue()->getMembers()->getRoot() == nullptr)
    {
        return StatusType::FAILURE;
    }

    if((groupNode->getValue()->getIsVip() == false) && (movieNode->getValue()->getVipOnly() == true))
    {
        return StatusType::FAILURE;
    }

    Genre genre = movieNode->getValue()->getGenre();
    movieNode->getValue()->addViews(groupNode->getValue()->getGroupSize());
    groupNode->getValue()->updateMoviesGroupWatchedInGenre(genre, groupNode->getValue()->getGroupSize());
    groupNode->getValue()->addViewToMembers(groupNode->getValue()->getMembers()->getRoot(), genre);

    m_movies_ranked.removeValue(movieNodeWithFlag->getValue());//replaced movieNodeWithFlag with tmpMovieWithFlag
    m_movies_by_genre_by_rank[(int) genre]->removeValue(movieNodeWithFlag->getValue());
    tmpMovieWithFlag->addViews(groupNode->getValue()->getGroupSize());
    try
    {
        m_movies_ranked.insertValue(tmpMovieWithFlag);
        m_movies_by_genre_by_rank[(int) genre]->insertValue(tmpMovieWithFlag);
    }
    catch(BadAllocation& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    cout<<"get_all_movies_count: genre "<<(int)genre<<endl;
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
    cout<<"get_all_movies: genre "<<(int)genre<<endl;
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
            output_t<int> tmp = this->get_all_movies_count(genre);
            int sizeOfArray = tmp.ans();
            Movie** movieArray = new Movie*[sizeOfArray];

            m_movies_by_genre_by_rank[(int) genre]->treeToArrayInOrderRight(
                    m_movies_by_genre_by_rank[(int) genre]->getRoot(), movieArray, sizeOfArray, counter);
            for(int i = 0; i < sizeOfArray; ++i)
            {
                output[i] = movieArray[i]->getMovieId();
            }
            delete counter;
        }
        return StatusType::SUCCESS;
    }
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    cout<<"get_num_views: user "<<userId<<" genre "<<(int)genre<<endl;
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
    cout<<"rate_movie: user "<<userId<<" movie "<<movieId<<" rating "<<rating<<endl;
    if (userId <= 0 || movieId <=0 || rating < 0 || rating > 100)
    {
        return StatusType::INVALID_INPUT;
    }

    User* tmpUser = new User(userId, false);
    Movie* tmpMovie = new Movie(movieId, 0, false, Genre::NONE, 0, 0, false);
    Node<User>* userNode = m_users.findObject(m_users.getRoot(), tmpUser);
    Node<Movie>* movieNode = m_movies.findObject(m_movies.getRoot(), tmpMovie);
    delete tmpMovie;
    delete tmpUser;

    if(userNode == nullptr || movieNode == nullptr)
    {
        return StatusType::FAILURE;
    }

    if(movieNode->getValue()->getVipOnly() == true && userNode->getValue()->getIsVip() == false)
    {
        return StatusType::FAILURE;
    }

    Movie* tmpMovieWithFlag = new Movie(movieId, movieNode->getValue()->getViews(), movieNode->getValue()->getVipOnly(),
                                      movieNode->getValue()->getGenre(), movieNode->getValue()->getRating(),
                                      movieNode->getValue()->getNumOfVoters(), true);
    Node<Movie>* movieNodeWithFlag = m_movies_ranked.findObject(m_movies_ranked.getRoot(), tmpMovieWithFlag);

    if(movieNodeWithFlag == nullptr)
    {
        return StatusType::FAILURE;
    }

    movieNode->getValue()->addRating(rating);

    Genre genre = movieNode->getValue()->getGenre();
    m_movies_ranked.removeValue(movieNodeWithFlag->getValue());
    m_movies_by_genre_by_rank[(int) genre]->removeValue(movieNodeWithFlag->getValue());
    tmpMovieWithFlag->addRating(rating);
    try
    {
        m_movies_ranked.insertValue(tmpMovieWithFlag);
        m_movies_by_genre_by_rank[(int) genre]->insertValue(tmpMovieWithFlag);
    }
    catch(BadAllocation& e)
    {
        delete tmpMovieWithFlag;
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
    cout<<"get_group_recommendation: group "<<groupId<<endl;
    if(groupId <= 0)
    {
        output_t<int> out(StatusType::INVALID_INPUT);
        return out;
    }

    Group* tempGroup = new Group(groupId, false ,0);
    Node<Group> *groupNode = m_groups.findObject(m_groups.getRoot(), tempGroup);
    delete tempGroup;

    if(groupNode == nullptr)
    {
        output_t<int> out(StatusType::FAILURE);
        return out;
    }

    if (groupNode->getValue()->getMembers()->getRoot() == nullptr)
    {
        output_t<int> out(StatusType::FAILURE);
        return out;
    }

    int max_views = 0;
    Genre fav_genre = Genre::NONE;
    for (int i = 3; i >= 0; i--) {
        Genre genre = static_cast<Genre>(i);
        if (groupNode->getValue()->getMoviesGroupWatchedInGenre(genre) >= max_views)
        {
            max_views = groupNode->getValue()->getMoviesGroupWatchedInGenre(genre);
            fav_genre = genre;
        }
    }

    if (m_movies_in_genre[(int) fav_genre] == 0)
    {
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
        output_t<int> out(m_movies_by_genre[(int) fav_genre]->getMaximumValue()->getValue()->getMovieId());
        return out;
    }
}

