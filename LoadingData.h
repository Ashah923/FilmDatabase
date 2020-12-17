#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <thread>
#include "MovieDataBase.h"
#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "Tag.h"
#include "Genre.h"

class LoadingData
{
public:

	void loadTexturesAndFont(sf::Font& font, sf::Font& textFont, sf::Texture& textureBackground);
	void loadAllMovies(MovieDataBase& movieDataBase);
	void loadRatedMovies(MovieDataBase& movieDataBase, User& user);
	void loadRatedUsers(MovieDataBase& movieDataBase);
	void loadGenre( Genre& genre, Movie &movie, int &genreNumber);
	void loadTag(Tag& tag, Movie &movie, std::vector<int>& tagNumbers);
	void loadData(MovieDataBase& movieDataBase, User& user);
};