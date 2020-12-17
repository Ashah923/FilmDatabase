#include "TextSupport.h"

sf::Text TextSupport::typing(sf::Font& font, int characterSize, float Tpositionx, float Tpositiony, sf::Color color, sf::Text text, sf::Event event, sf::RenderWindow& window)
{
	if (event.text.unicode != 8 && event.text.unicode != 13)
	{
		sf::Uint32 unicode = 0;
		if (event.text.unicode < 128)
			unicode += event.text.unicode;
		if (unicode)
		{
			sf::String str = text.getString();
			str += unicode;
			text.setString(str);
			text.setFillColor(color);
			text.setPosition(Tpositionx, Tpositiony);
		}
	}
	return text;
}

sf::Text TextSupport::typingYear(sf::Font& font, int characterSize, float Tpositionx, float Tpositiony, sf::Color color, sf::Text text, sf::Event event, sf::RenderWindow& window)
{
	if (event.text.unicode != 8 && event.text.unicode != 13)
	{
		sf::Uint32 unicode = 0;
		if (event.text.unicode < 128)
			unicode += event.text.unicode;
		if (unicode)
		{
			sf::String str = text.getString();
			str += unicode;
			text.setString(str);
			text.setFillColor(color);
			text.setPosition(Tpositionx, Tpositiony);
		}
	}
		return text;	
}

void TextSupport::printText(std::string _text, sf::Font& font, int characterSize, float Tpositionx, float Tpositiony, sf::Color color, sf::RenderWindow& window)
{
	sf::Text text;
	text.setFont(font);
	text.setString(_text);
	text.setCharacterSize(characterSize);
	text.setFillColor(sf::Color::White);
	text.setPosition(Tpositionx, Tpositiony);
	text.setFillColor(color);
	window.draw(text);
}


sf::Text TextSupport::deleteLetter(sf::Text text, int position)
{
	sf::String str = text.getString();
	str.erase(position - 1, 1);
	text.setString(str);
	return text;
}

int TextSupport::printDescription(std::string _text, sf::Font& font, sf::Color color, sf::RenderWindow& window)
{
	std::string description;
	int i = 0; int k = 0;
	while ((i + 1) < _text.length())
	{
		while (_text[i]!='.' && _text[i] != '?' && _text[i] != '!')
		{
			if (i + 1 == _text.length())
				break;
			description = description + _text[i];
			i++;
		}
		description = description + _text[i];
		i=i+2;
		printText(description, font, 25, 40.f, (250.f+(k*30.f)), sf::Color::Black, window);
		description = "";
		k++;
	}
	return 250.f + ((k-1)*30.f);
}

