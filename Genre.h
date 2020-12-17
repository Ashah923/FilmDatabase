#pragma once
#include "Movie.h"

class Movie;

class Genre
{
	enum  GENRE
	{
		fantasy = 0,
		romans = 1,
		familijny = 2,
		scifi = 3,
		dramat = 4,
		horror = 5,
		akcja = 6,
		kryminal = 7,
		thriller = 8
	};

public:
	std::vector<std::pair<std::vector<Movie*>, int>> movies;

	Genre();
	void removeFromGenre(Movie& movie);
	void addToGenre(Movie& movie, int genreNuber);
	std::string toString(int genreNumber);
};

