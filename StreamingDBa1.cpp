#include "StreamingDBa1.h"

streaming_database::streaming_database()
{
	// TODO: Your code goes here
}

streaming_database::~streaming_database()
{
	// TODO: Your code goes here
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

StatusType streaming_database::remove_user(int userId){
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
    // TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
	// TODO: Your code goes here
	return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}


