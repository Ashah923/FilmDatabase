#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextSupport.h"
#include "Border.h"


class EventSupport
{

public:
	sf::Text enterWord(sf::Event& event, int& numberOfLetters, sf::RenderWindow& window, sf::Text& text, sf::Font& font, float Tpositionx, float Tpositiony, Border& border, int limit);
	sf::Text enterYear(sf::Event& event, int& numberOfLetters, sf::RenderWindow& window, sf::Text& text, sf::Font& font, float Tpositionx, float Tpositiony, Border& border, int limit);
};

