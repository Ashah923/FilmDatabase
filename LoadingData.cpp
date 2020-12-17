#include "LoadingData.h"

void LoadingData::loadTexturesAndFont(sf::Font& font, sf::Font& textFont, sf::Texture& textureBackground)
{
	if (!textureBackground.loadFromFile("textures/background.png")) { throw "error loading image: textures/background.png"; }
	if (!font.loadFromFile("fonts/Hey Keysha.ttf")) { throw "error loading font: fonts/Hey Keysha.ttf"; }
	if (!textFont.loadFromFile("fonts/PlomPraeng.ttf")) { throw "error loading font: fonts/PlomPraeng.ttf"; }

	return;
}

void LoadingData::loadAllMovies(MovieDataBase& movieDataBase)
{
	std::vector<int> genreVector;
	std::vector<int>::iterator itGenre;
	std::vector<std::vector<int>> tagVector;
	std::vector<std::vector<int>>::iterator itAllTag;
	std::vector<int> tab;
	int i = 0;
	std::fstream file, assessmentFile;
	std::string data;
	Movie movie;

		file.open("Baza/movie/movieNameList.txt", std::ios::in);
		if (!file.good())
			throw "error loading file: Baza/movie/movieNameList.txt";

		while (!file.eof())
		{
			getline(file, data); //title
			if (data == "") { break; }
			movie.setName(data);

			getline(file, data); //year
			movie.setProductionYear(stoi(data));

			getline(file, data); //genre
			genreVector.push_back(stoi(data));

			getline(file, data);  //description
			movie.setDescription(data);

			for (int i = 0; i < 3; i++)
			{
				getline(file, data);  //tag
				tab.push_back(stoi(data));
			}
			tagVector.push_back(tab);
			tab.clear();
			
			for (int i = 0; i < 5; i++)
			{
				getline(file, data);
				movie.getRating().numbersOfRatings[i] = stoi(data);
			}

			movieDataBase.allMovies.push_back(movie);
		}

		for (itGenre = genreVector.begin(); itGenre != genreVector.end(); itGenre++)
		{
			loadGenre(movieDataBase.genre, movieDataBase.allMovies[i], *itGenre); i++;
		}

		i = 0;
		for (itAllTag = tagVector.begin(); itAllTag != tagVector.end(); itAllTag++)
		{
			loadTag(movieDataBase.tag, movieDataBase.allMovies[i], (*itAllTag)); i++;
		}

	file.close();
	return;
}

void LoadingData::loadRatedMovies(MovieDataBase& movieDataBase, User& user)
{
	std::pair<Movie*, int> p;
	std::string data, title, userRating;
	std::vector<Movie>::iterator itAllMovies;
	std::list<std::pair<Movie*, int>>::iterator itRatedMovies;

	std::fstream fileRated("Baza/" + user.getNick() + "/MovieList.txt", std::ios::in);
	if (!fileRated.good())
		throw "error loading file: Baza/"+ user.getNick() + " / MovieList.txt";

	while (!fileRated.eof())
	{
		getline(fileRated, data);
		if (data == "") { break; }
		title = data;
		title.erase(title.size() - 2, 2);
		for (itAllMovies = movieDataBase.allMovies.begin(); itAllMovies != movieDataBase.allMovies.end(); itAllMovies++)
		{
			if (title == (*itAllMovies).getName() + "_" + std::to_string((*itAllMovies).getProductionYear()))
			{
				userRating = data;
				userRating = userRating.erase(0, data.size() - 1);
				p.first = &(*itAllMovies);
				p.second = stoi(userRating);
				user.ratedMovies.push_back(p);

				itRatedMovies = user.ratedMovies.begin();
				(*itAllMovies).tempUserRating = &(*itRatedMovies).second;
			}
		}
	}
	fileRated.close();

	return;
}

void LoadingData::loadRatedUsers(MovieDataBase& movieDataBase)
{
	std::string data, nextTitle;
	std::pair<Movie*, std::vector<std::string>> pair;
	std::vector<Movie>::iterator itAllMovies;
	std::vector<Movie>::iterator itNextTitle = movieDataBase.allMovies.begin();
	std::vector<std::pair<Movie*, std::vector<std::string>>>::iterator itRatedUsers;
	itNextTitle++;

	std::fstream file("Baza/movie/ratedUsers.txt", std::ios::in);
	if (file.good())
	{	
		getline(file, data);
		for (itAllMovies = movieDataBase.allMovies.begin(); itAllMovies != movieDataBase.allMovies.end(); itAllMovies++)
		{
			if (data == (*itAllMovies).getName() + "_" + std::to_string((*itAllMovies).getProductionYear()))
			{
				pair.first = &(*itAllMovies);

				while ((*itNextTitle).getName() + "_" + std::to_string((*itNextTitle).getProductionYear()) != data)
				{
					getline(file, data);
					if ((*itNextTitle).getName() + "_" + std::to_string((*itNextTitle).getProductionYear()) == data) { break; }
					pair.second.push_back(data);
				}
				movieDataBase.ratedUsers.push_back(pair);
				pair.second.clear();

				if (itNextTitle == movieDataBase.allMovies.end()) { break; }
				itNextTitle++;
			}
			if (itNextTitle == movieDataBase.allMovies.end()) { break; }
		}
		itAllMovies++;
		pair.first = &(*itAllMovies);
		while (file.eof())
		{
			getline(file, data);
			if (data != "")
				pair.second.push_back(data);
		}
		movieDataBase.ratedUsers.push_back(pair);
	}
	file.close();

	for (itRatedUsers = movieDataBase.ratedUsers.begin(); itRatedUsers != movieDataBase.ratedUsers.end(); itRatedUsers++)
	{
		(*itRatedUsers).first->ratedUsers = &(*itRatedUsers).second;
	}

	return;
}

void LoadingData::loadGenre(Genre &genre, Movie &movie, int &genreNumber)
{
	std::vector<std::pair<std::vector<Movie*>, int>>::iterator it = genre.movies.begin();

	for (int i = 0; i < genreNumber; i++)
		it++;

	movie.setGenre((*it).second);
	(*it).first.push_back(&movie);

	return;
}

void LoadingData::loadTag(Tag& tag, Movie &movie, std::vector<int>& tagNumbers)
{

	std::vector<std::pair<std::vector<Movie*>, int>>::iterator it;

	for (int i = 0; i < 3; i++)
	{
		it = tag.movies.begin();

		for (int j = 0; j < tagNumbers[i]; j++)
			it++;
		
		movie.setTag((*it).second, i);
		(*it).first.push_back(&movie);
	}

	return;
}

void LoadingData::loadData(MovieDataBase& movieDataBase, User& user)
{
	loadAllMovies(movieDataBase);
	loadRatedMovies(movieDataBase, user);
	loadRatedUsers(movieDataBase);

	std::vector<Movie>::iterator it;
	for (it = movieDataBase.allMovies.begin(); it != movieDataBase.allMovies.end(); it++)
	{
		(*it).getRating()();
	}

	return;
}
