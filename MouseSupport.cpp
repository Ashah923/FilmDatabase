#include "MouseSupport.h"

int MouseSupport::pressButton(sf::FloatRect boundingBox, float Spositionx, float Spositiony, int width, int height, sf::RenderWindow& window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	if (boundingBox.contains(mousePosition.x, mousePosition.y)) 
	{
		HoverLight hoverLight(Spositionx, Spositiony, width, height);
		window.draw(hoverLight);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 1;
		}
	}
	return 0;
}

int MouseSupport::pressBorder(sf::FloatRect boundingBox, sf::RenderWindow& window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	if (boundingBox.contains(mousePosition.x, mousePosition.y))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 1;
		}
	}
	return 0;
}

int MouseSupport::releaseButton(sf::FloatRect boundingBox, sf::RenderWindow& window, sf::Event& event)
{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		if (boundingBox.contains(mousePosition.x, mousePosition.y))
		{
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	        {
			return 1;
		    }
	    }

	return 0;
}
