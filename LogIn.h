#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <direct.h>
#include "User.h"
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "MovieDataBase.h"

class LogIn
{
public:
	LogIn();
	~LogIn();
	int logIn(MovieDataBase& movieDataBase, std::string nick, std::string password, User& user, sf::RenderWindow& window, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	int signUp(std::string nick, std::string password, sf::RenderWindow& window, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont);
	void logOut(MovieDataBase& movieDataBase, User& user);
};

