#include "MovieDataBase.h"


void MovieDataBase::addMovie(Movie& movie)
{
	std::vector<Movie>::iterator it;
	for (it = allMovies.begin(); it != allMovies.end(); it++)
	{
		if ((*it).getName() == movie.getName() && (*it).getProductionYear() == movie.getProductionYear())
			throw "Movie in database";
	}

	allMovies.resize(allMovies.size() + 1);

	int number = allMovies.size() - 1;
	allMovies[number] = movie;

	for (int i = 0; i < 3; i++)
		allMovies[number].getRating().numbersOfRatings[i] = 0;

	allMovies[number].getRating().setAvgRating(0);
	allMovies[number].tempUserRating = nullptr;

	return;
}


void MovieDataBase::deleteMovie(Movie& movie, User& user)
{
	std::list<std::pair<Movie*, int>>::iterator itRatedMovies;
	std::vector<std::string>::iterator itRatedUsers;
	std::vector<Movie>::iterator itAllMovies;

	std::list<std::string> movies;
	std::string data;
	std::fstream file;


	for (itRatedMovies = user.ratedMovies.begin(); itRatedMovies != user.ratedMovies.end(); itRatedMovies++)
	{
		if (movie.getName() == (*itRatedMovies).first->getName() && movie.getProductionYear() == (*itRatedMovies).first->getProductionYear())
		{
			user.ratedMovies.erase(itRatedMovies);
			break;
		}
	}


	if (!ratedUsers.empty())
	{
		for (itRatedUsers = movie.ratedUsers->begin(); itRatedUsers != movie.ratedUsers->end(); itRatedUsers++)
		{
			file.open("Baza/" + *itRatedUsers + "/MovieList.txt", std::ios::in);
			if (file.good())
			{
				while (!file.eof())
				{
					getline(file, data);
					if (movie.getName() + "_" + std::to_string(movie.getProductionYear()) != data)
					{
						movies.push_back(data);
					}
				}
				movies.pop_back();
				file.close();
				file.open("Baza/" + *itRatedUsers + "/MovieList.txt", std::ios::out);
				std::list<std::string>::iterator itMovies;
				for (itMovies = movies.begin(); itMovies != movies.end(); itMovies++)
				{
					file << *itMovies << std::endl;
				}
			}
			movies.erase(movies.begin(), movies.end());
			file.close();
		}
	}

	for (itAllMovies = allMovies.begin(); itAllMovies != allMovies.end(); itAllMovies++)
	{
		if (movie.getName() == (*itAllMovies).getName() && movie.getProductionYear() == (*itAllMovies).getProductionYear())
		{
			allMovies.erase(itAllMovies);
			break;
		}
	}

	return;
}

void MovieDataBase::addToRatedUsers(std::string& userNick, Movie& movie)
{
	std::vector<std::string>::iterator itRatedUsers;

	if(!movie.ratedUsers->empty())
		for (itRatedUsers = movie.ratedUsers->begin(); itRatedUsers != movie.ratedUsers->end(); itRatedUsers++)
		{
			if ((*itRatedUsers) == userNick) { return; }
		}

	movie.ratedUsers->push_back(userNick);

	return;
}