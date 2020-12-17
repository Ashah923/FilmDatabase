#include "SupportData.h"

void SupportData::saveNewRating(MovieDataBase& movieDataBase, Movie& movie, User& user, int rating)
{
	SaveData saveData;

	user.rateMovie(rating, movie);
	movie.getRating()();
	movieDataBase.addToRatedUsers(user.getNick(), movie);

	saveData.saveRatedUsers(movieDataBase);
	saveData.saveRatedMovies(user);
	saveData.saveDataMovie(movieDataBase);

	return;
}

void SupportData::saveNewGenre(Movie& movie, MovieDataBase& movieDataBase, int newGenre)
{
	SaveData saveData;

	if (movie.getGenre() == newGenre) { return; }

	movieDataBase.genre.removeFromGenre(movie);

	std::vector<std::pair<std::vector<Movie*>, int>>::iterator itNewGenreList;
	itNewGenreList = movieDataBase.genre.movies.begin();
	for (int i = 0; i < newGenre; i++)
		itNewGenreList++;

	movie.setGenre((*itNewGenreList).second);
	(*itNewGenreList).first.push_back(&movie);

	saveData.saveDataMovie(movieDataBase);

	return;
}

void SupportData::saveNewTags(Movie& movie, MovieDataBase& movieDataBase, int newTags[])
{
	SaveData saveData;
	int i;

	movieDataBase.tag.removeFromTags(movie);

	std::vector<std::pair<std::vector<Movie*>, int>>::iterator itNewTagList;
	for (i = 0; i < 3; i++)
	{
		itNewTagList = movieDataBase.tag.movies.begin();
		for (int j = 0; j < newTags[i]; j++)
			itNewTagList++;


		movie.setTag((*itNewTagList).second, i);
		(*itNewTagList).first.push_back(&movie);
	}

	saveData.saveDataMovie(movieDataBase);

	return;
}

void SupportData::deleteFilm(MovieDataBase& movieDataBase, Movie& movie, User& user)
{
	SaveData saveData;

	movieDataBase.genre.removeFromGenre(movie);
	movieDataBase.tag.removeFromTags(movie);

	movieDataBase.deleteMovie(movie, user);

	saveData.saveRatedMovies(user);
	saveData.saveRatedUsers(movieDataBase);
	saveData.saveDataMovie(movieDataBase);
}

std::string SupportData::saveNewFilm(MovieDataBase& movieDataBase, Movie& movie, User& user, int& genreNuber, int tagsNumber[])
{
	SaveData saveData;
	LoadingData loadingData;
	std::pair < Movie*, std::vector<std::string>> pair;

	try { movieDataBase.addMovie(movie); }
	catch (const char* e) { std::cout << "Message: " << e << std::endl; return "Podany film jest juz w bazie."; }

	pair.first = &(movieDataBase.allMovies.back());
	movieDataBase.ratedUsers.push_back(pair); 
	(movieDataBase.ratedUsers.back()).first->ratedUsers = &(movieDataBase.ratedUsers.back()).second;

	movieDataBase.tag.addToTag((movieDataBase.allMovies.back()), tagsNumber);
	movieDataBase.genre.addToGenre((movieDataBase.allMovies.back()), genreNuber);

	update(movieDataBase, user);

	try 
	{
		saveData.saveDataMovie(movieDataBase);
		saveData.saveRatedUsers(movieDataBase);
	}
	catch (const char* e) { std::cout << "Message: " << e << std::endl; return "Wystapil blad. Przepraszamy."; }

	//RatedUsers update
	movieDataBase.ratedUsers.clear();
	loadingData.loadRatedUsers(movieDataBase);

	return "Dodano film do bazy.";

}

void SupportData::update(MovieDataBase& movieDataBase, User& user)
{
	LoadingData loadingData;
	std::vector<Movie>::iterator itAllMovies;
	std::vector<std::pair<std::vector<Movie*>, int>>::iterator itGT;

	//GENRE update

	itGT = movieDataBase.genre.movies.begin();
	for (int i = 0; i < 9; i++)
	{
		(*itGT).first.clear();
		itGT++;
	}

	for (itAllMovies = movieDataBase.allMovies.begin(); itAllMovies != movieDataBase.allMovies.end(); itAllMovies++)
	{
		itGT = movieDataBase.genre.movies.begin();
		for (int i = 0; i < (*itAllMovies).getGenre(); i++)
			itGT++;

		(*itGT).first.push_back(&(*itAllMovies));
	}

	//TAG update

	itGT = movieDataBase.tag.movies.begin();
	for (int i = 0; i < 9; i++)
	{
		(*itGT).first.clear();
		itGT++;
	}

	for (itAllMovies = movieDataBase.allMovies.begin(); itAllMovies != movieDataBase.allMovies.end(); itAllMovies++)
	{
		itGT = movieDataBase.tag.movies.begin();
		for (int i = 0; i < (*itAllMovies).getGenre(); i++)
			itGT++;

		(*itGT).first.push_back(&(*itAllMovies));
	}

    //RatedMovies update
	user.ratedMovies.clear();
	loadingData.loadRatedMovies(movieDataBase, user);

	return;
}