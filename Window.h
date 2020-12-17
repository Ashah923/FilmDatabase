#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <vector>
#include <regex>
#include "Button.h"
#include "HoverLight.h"
#include "Border.h"
#include "LogIn.h"
#include "User.h"
#include "MouseSupport.h"
#include "EventSupport.h"
#include "TextSupport.h"
#include "MovieDataBase.h"
#include "Movie.h"
#include "SaveData.h"
#include "LoadingData.h"
#include "SupportData.h"
#include "Tag.h"
#include "Genre.h"

class Window
{
	enum  windows
	{
		FIRST = 0,
		LOGIN = 1,
		SIGNUP = 2,
		USER = 3,
		EXIT = 4,
	};

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
	int firstWindow(sf::RenderWindow& window, sf::Sprite &spriteBackground, sf::Font &font);
	int logInWindow(MovieDataBase& movieDataBase, sf::RenderWindow& window, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	int signUpWindow(sf::RenderWindow& window, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	int userWindow(MovieDataBase& movieDataBase, sf::RenderWindow& window, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	int statement(sf::RenderWindow& window, sf::String text1, sf::String text2, int toWindow, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	int enterTitle(sf::RenderWindow& window, MovieDataBase& movieDataBase, std::string _text, int ret, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	int film(sf::RenderWindow& window, MovieDataBase& movieDataBase, std::string movieName, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	Movie* filmYear(sf::RenderWindow& window, std::vector<Movie*>& movies, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void rateMovieWindow(sf::RenderWindow& window, MovieDataBase& movieDataBase, Movie& movie, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void fotoWindow(sf::RenderWindow& window, sf::String filmName, sf::Font& font);
	void editMovieWindow(sf::RenderWindow& window, MovieDataBase& movieDataBase, Movie& movie, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void enterEditGenreWindow(sf::RenderWindow& window, Movie& movie, MovieDataBase& movieDataBase, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void enterEditTagsWindow(sf::RenderWindow& window, MovieDataBase& movieDataBase, Movie& movie, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void enterEditDescriptionWindow(sf::RenderWindow& window, MovieDataBase& movieDataBase, Movie& movie, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void showAllMovis(sf::RenderWindow& window, MovieDataBase& movieDataBase, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void showMovisFormGenre(sf::RenderWindow& window, int eGenre, Genre& gerne, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void showMovisFormTag(sf::RenderWindow& window, int eTag, Tag& tag, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void enterSearchGenre(sf::RenderWindow& window, User& user, Genre& genre, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void enterSearchTag(sf::RenderWindow& window, User& user, Tag& tag, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void newFilmTitle(sf::RenderWindow& window, User& user, MovieDataBase& movieDataBase, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void newFilmYear(sf::RenderWindow& window, User& user, MovieDataBase& movieDataBase, Movie& movie, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void newFilmGenre(sf::RenderWindow& window, Movie& movie, MovieDataBase& movieDataBase, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void newFilmDesc(sf::RenderWindow& window, Movie& movie, MovieDataBase& movieDataBase, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont, int genreNuber);
	void NewFilmTags(sf::RenderWindow& window, Movie& movie, MovieDataBase& movieDataBase, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont, int genreNuber);
	

};

