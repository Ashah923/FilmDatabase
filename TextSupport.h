#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Border.h"


class TextSupport
{
public:
	sf::Text typing(sf::Font& font, int characterSize, float Tpositionx, float Tpositiony, sf::Color color, sf::Text text, sf::Event event, sf::RenderWindow& window);
	sf::Text typingYear(sf::Font& font, int characterSize, float Tpositionx, float Tpositiony, sf::Color color, sf::Text text, sf::Event event, sf::RenderWindow& window);
	void printText(std::string _text, sf::Font& font, int characterSize, float Tpositionx, float Tpositiony, sf::Color color, sf::RenderWindow& window);
	int printDescription(std::string _text, sf::Font& font, sf::Color color, sf::RenderWindow& window);
	sf::Text deleteLetter(sf::Text text, int position);
};

