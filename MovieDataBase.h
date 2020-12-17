#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include "Movie.h"


class MovieDataBase
{
public:
	std::vector<Movie> allMovies; 
	std::vector<std::pair<Movie*, std::vector<std::string>>> ratedUsers;
	Genre genre;
	Tag tag;

	void addMovie(Movie& movie); 
	void deleteMovie(Movie& movie, User& user); 
	void addToRatedUsers(std::string& userNick, Movie& movie);
};

