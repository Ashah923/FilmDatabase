#include "EventSupport.h"

sf::Text EventSupport::enterWord(sf::Event& event, int& numberOfLetters, sf::RenderWindow& window, sf::Text& text, sf::Font& font, float Tpositionx, float Tpositiony, Border& border, int limit)
{
	TextSupport textSupport;
	border.setColor(sf::Color(230, 230, 250));
	if (event.key.code == sf::Keyboard::Backspace && numberOfLetters > 0)
	{
		text = textSupport.deleteLetter(text, numberOfLetters);
		numberOfLetters--;
		return text;
	}
	if (event.type == sf::Event::TextEntered && numberOfLetters < limit)
	{
		text = textSupport.typing(font, 35, Tpositionx, Tpositiony, sf::Color::Black, text, event, window);
		numberOfLetters++;
		return text;
	}
	return text;
}

sf::Text EventSupport::enterYear(sf::Event& event, int& numberOfLetters, sf::RenderWindow& window, sf::Text& text, sf::Font& font, float Tpositionx, float Tpositiony, Border& border, int limit)
{
	TextSupport textSupport;
	border.setColor(sf::Color(230, 230, 250));
	if (event.key.code == sf::Keyboard::Backspace && numberOfLetters > 0)
	{
		text = textSupport.deleteLetter(text, numberOfLetters);
		numberOfLetters--;
		return text;
	}
	if (event.type == sf::Event::TextEntered && numberOfLetters < limit)
	{
		text = textSupport.typingYear(font, 35, Tpositionx, Tpositiony, sf::Color::Black, text, event, window);
		numberOfLetters++;
		return text;
	}
	return text;
}