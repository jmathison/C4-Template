#include "Projectile.h"



void Projectile::update(float dt)
{

	// Normalize vector
	float mag = std::sqrt(std::pow(movementInput.x, 2) + std::pow(movementInput.y, 2));
	movementInput /= mag;

	position += (movementInput * speed * dt);
	bool collide = false;

	// Test tile collision
	if (mapref) {
		collide = mapref->checkTileCollision(*this);

	}

	if (collide) {
		destroy = true;
	}

}

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f direction) : Character(pos, size)
{
	movementInput = direction;

}

