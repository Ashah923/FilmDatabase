#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class HoverLight : public sf::Drawable
{
	
	sf::RectangleShape rectangle;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	sf::RectangleShape& getRectangle() { return rectangle; }
	HoverLight() = delete;
	HoverLight(float Spositionx, float Spositiony, int width, int height);
};

