#include "Actor.h"


Actor::Actor(sf::Vector2f pos, sf::Vector2f size)
{
	this->position = pos;
	this->size = size;

	init();

}
