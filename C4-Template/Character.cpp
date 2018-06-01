#include "Character.h"



Character::Character(sf::Vector2f pos, sf::Vector2f size) : Actor(pos, size)
{
	playershape = sf::CircleShape(size.x / 2);
	playershape.setPosition(pos);
	playershape.setFillColor(sf::Color::Blue);
}

void Character::update(float dt)
{
	auto current_pos = position;
	position += (movementInput * speed * dt);
	bool collide = false;
	
	// Test tile collision
	if (mapref) {
		collide = mapref->checkTileCollision(*this);
	
		// Test out of bounds
		/*auto mapbounds = sf::FloatRect(sf::Vector2f(0, 0), mapref->getPixelPos(mapref->mapWidth, mapref->mapHeight));
		auto actorbounds = sf::FloatRect(position, size);

		mapbounds.*/

	}

	if (collide) {
		// Don't move if we hit something.
		position = current_pos;
	}
	
}

void Character::draw(sf::RenderWindow & window)
{
	playershape.setPosition(position);
	window.draw(playershape);

}
