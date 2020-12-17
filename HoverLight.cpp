#include "HoverLight.h"

HoverLight::HoverLight(float Spositionx, float Spositiony, int width, int height)
{
	HoverLight::rectangle.setFillColor(sf::Color(192, 192, 192));
	HoverLight::rectangle.setSize(sf::Vector2f(width, height));
	HoverLight::rectangle.setPosition(Spositionx, Spositiony);

}

void HoverLight::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(this->rectangle);
}