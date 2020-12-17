#include "SaveData.h"


void SaveData::saveDataMovie(MovieDataBase& movieDataBase)
{
	std::fstream file;
	std::vector<Movie>::iterator itDataMovies;

	file.open("Baza/movie/movieNameList.txt", std::ios::out);
	if (!file.good())
		throw "error loading file: Baza/moviemovieNameList.txt";

	for (itDataMovies = movieDataBase.allMovies.begin(); itDataMovies != movieDataBase.allMovies.end(); itDataMovies++)
	{
		file << (*itDataMovies).getName() << std::endl;
		file << (*itDataMovies).getProductionYear() << std::endl;
		file << (*itDataMovies).getGenre() << std::endl;
		file << (*itDataMovies).getDescription() << std::endl;

		for(int i = 0; i<3; i++)
		file << (*itDataMovies).getTag(i) << std::endl;

		for (int i = 0; i < 5; i++)
			file << (*itDataMovies).getRating().numbersOfRatings[i] << std::endl;
	}

	file.close();

	return;
}

void SaveData::saveRatedMovies(User& user)
{
	std::fstream file;
	std::list<std::pair<Movie*, int>>::iterator it;

	file.open("Baza/" + user.getNick() + "/MovieList.txt", std::ios::out);
	if (!file.good())
		throw "error loading file: Baza/" + user.getNick() + "/MovieList.txt";


	for ( it = user.ratedMovies.begin(); it != user.ratedMovies.end();  it++)
	{
		file << (*it).first->getName() + "_" + std::to_string((*it).first->getProductionYear()) + " " + std::to_string(*(*it).first->tempUserRating) << std::endl;
	}
	file.close();

	return;
}


void SaveData::saveRatedUsers(MovieDataBase& movieDataBase)
{
	std::fstream file;
	std::vector<Movie>::iterator itAllMoviesData;
	std::vector<std::string>::iterator itRatedUsers;

	file.open(("Baza/movie/ratedUsers.txt"), std::ios::out);
	if (!file.good())
		throw "error loading file: Baza/movie/ratedUsers.txt";

	for (itAllMoviesData = movieDataBase.allMovies.begin(); itAllMoviesData != movieDataBase.allMovies.end(); itAllMoviesData++)
	{
		file << (*itAllMoviesData).getName() + "_" + std::to_string((*itAllMoviesData).getProductionYear()) << std::endl;
		if (!(*itAllMoviesData).ratedUsers->empty()) 
		{
			for (itRatedUsers = (*itAllMoviesData).ratedUsers->begin(); itRatedUsers != (*itAllMoviesData).ratedUsers->end(); itRatedUsers++)
			{
				file << (*itRatedUsers) << std::endl;
			}
		}
	}
	
	file.close();

	return;
}

