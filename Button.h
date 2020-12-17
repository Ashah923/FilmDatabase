#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Button : public sf::Drawable, public sf::Transformable
{

	sf::Text text;
	sf::RectangleShape rectangle;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:

	sf::RectangleShape& getRectangle() { return rectangle; }
	Button() = delete;
	Button(std::string text, sf::Font& font, int characterSize, float Tpositionx, float Tpositiony, float Spositionx, float Spositiony, int width, int height);
};


