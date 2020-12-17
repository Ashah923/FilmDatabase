#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include "TextSupport.h"
#include "Movie.h"
#include "Genre.h"
#include "Tag.h"

class Movie;
class Genre;
class Tag;


class User
{
	std::string nick, password;

public:

	std::list<std::pair<Movie*, int>> ratedMovies;

	void setNick(const std::string& nick) { this->nick = nick; }
	std::string& getNick() { return nick; }
	void setPassword(const std::string& password) { this->password = password; }
	std::string& getPassword() { return password; }

	User();
	~User();
	void showRecentlyRated(sf::Font textFont, sf::RenderWindow& window);
	void showRecommended(sf::Font textFont, sf::RenderWindow& window, Genre& genre, Tag& tag);
	void rateMovie(int _rating, Movie& movie);
};

