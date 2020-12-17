#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Border : public sf::Drawable
{
	sf::RectangleShape rectangle, rectangleBorder;;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	sf::RectangleShape& getRectangle() { return rectangle; }
	void setColor(const sf::Color& color) { rectangle.setFillColor(color);}
	Border() {};
	Border(float Spositionx, float Spositiony, int width, int height);
};

