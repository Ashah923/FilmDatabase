#include "Genre.h"

Genre::Genre()
{
	std::pair<std::vector<Movie*>, int> genre;

	for (int i = 0; i < 9; i++)
	{
		genre.second = i;
		movies.push_back(genre);
	}
}

void Genre::removeFromGenre(Movie& movie)
{
	std::vector<std::pair<std::vector<Movie*>, int>>::iterator itGenreList;
	itGenreList = movies.begin();
	for (int i = 0; i < movie.getGenre(); i++)
		itGenreList++;

	std::vector<Movie*>::iterator itMovies;
	for (itMovies = (*itGenreList).first.begin(); itMovies != (*itGenreList).first.end(); itMovies++)
	{
		if ((*itMovies)->getName() == movie.getName() && (*itMovies)->getProductionYear() == movie.getProductionYear())
		{
			(*itGenreList).first.erase(itMovies);
			break;
		}
	}

	movie.setTempGenre(nullptr);
}

void Genre::addToGenre(Movie& movie, int genreNuber)
{
	std::vector<std::pair<std::vector<Movie*>, int>>::iterator itGenreList;
	itGenreList = movies.begin();

	for (int i = 0; i < genreNuber; i++)
		itGenreList++;

	movie.setGenre((*itGenreList).second);
	(*itGenreList).first.push_back(&movie);
}

std::string Genre::toString(int genreNumber)
{
	switch (genreNumber)
	{
	case fantasy:
		return "fantasy";
	case romans:
		return "romans";
	case familijny:
		return "familijny";
	case scifi:
		return "sci-fi";
	case dramat:
		return "dramat";
	case horror:
		return "horror";
	case akcja:
		return "akcja";
	case kryminal:
		return "kryminal";
	case thriller:
		return "thriller";
	}
	return "";
}