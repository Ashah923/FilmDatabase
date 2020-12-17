#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "HoverLight.h"
#include "Border.h"


class MouseSupport
{
public:
	int pressButton(sf::FloatRect boundingBox, float Spositionx, float Spositiony, int width, int height, sf::RenderWindow& window);
	int pressBorder(sf::FloatRect boundingBox, sf::RenderWindow& window);
	int releaseButton(sf::FloatRect boundingBox, sf::RenderWindow& window, sf::Event& event);

};

