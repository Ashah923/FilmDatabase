#include "Button.h"

Button::Button(std::string text, sf::Font& font, int characterSize, float Tpositionx, float Tpositiony, float Spositionx, float Spositiony, int width, int height)
{
	Button::text.setString(text);
	Button::text.setFont(font);
	Button::text.setCharacterSize(characterSize);
	Button::text.setPosition(Tpositionx, Tpositiony);
	Button::text.setFillColor(sf::Color::White);
	Button::rectangle.setFillColor(sf::Color::Black);
	Button::rectangle.setSize(sf::Vector2f(width, height));
	Button::rectangle.setPosition(Spositionx, Spositiony);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{	
	target.draw(this->rectangle);
	target.draw(this->text);
}