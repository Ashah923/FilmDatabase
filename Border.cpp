#include "Border.h"

Border::Border(float Spositionx, float Spositiony, int width, int height)
{
	Border::rectangle.setFillColor(sf::Color::White);
	Border::rectangle.setSize(sf::Vector2f(width-10, height-10));
	Border::rectangle.setPosition(Spositionx+5, Spositiony+5);
	Border::rectangleBorder.setFillColor(sf::Color(128, 128, 128));
	Border::rectangleBorder.setSize(sf::Vector2f(width, height));
	Border::rectangleBorder.setPosition(Spositionx, Spositiony);
}

void Border::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(this->rectangleBorder);
	target.draw(this->rectangle);
}