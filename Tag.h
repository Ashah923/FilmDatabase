#pragma once
#include "Movie.h"
#include <vector>

class Movie;

class Tag
{
	enum  TAG
	{
		animacja = 0,
		dla_dzieci = 1,
		wzruszajacy = 2,
		emocjonujacy = 3,
		zabawny = 4,
		straszny = 5,
		przygodowy = 6,
		zwariowany = 7,
		pogodny = 8
	};

public:
	std::vector<std::pair<std::vector<Movie*>, int>> movies;

	Tag();
	void removeFromTags(Movie& movie);
	void addToTag(Movie& movie, int tagsNumber[]);
	std::string toString(int genreNumber);
};

