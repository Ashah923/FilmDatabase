#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <thread>
#include "Movie.h"
#include "User.h"
#include "SaveData.h"
#include "LoadingData.h"
#include "Rating.h"


class SupportData
{
public:
	void saveNewRating(MovieDataBase& movieDataBase, Movie& movie, User& user, int rating);
	void saveNewGenre(Movie& movie, MovieDataBase& movieDataBase, int newGenre);
	void saveNewTags(Movie& movie, MovieDataBase& movieDataBase, int newTags[]);
	void deleteFilm(MovieDataBase& movieDataBase, Movie& movie, User& user);
	std::string saveNewFilm(MovieDataBase& movieDataBase, Movie& movie, User& user, int& genreNuber, int tagsNumber[]);
	void update(MovieDataBase& movieDataBase, User& user);
};

