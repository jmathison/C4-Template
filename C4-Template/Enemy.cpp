#include "Enemy.h"



Enemy::Enemy(sf::Vector2f pos, sf::Vector2f size) : Character(pos, size)
{
	playershape.setFillColor(sf::Color::Red);
	speed = 240;
}

void Enemy::update(float dt)
{
	// AI code to set up movement input vector
	movementInput.x = 0;
	movementInput.y = 0;

	if (followTarget != NULL) {
		auto dir = followTarget->position - position;

		movementInput = dir;
	}
	
	// Normalize vector
	float mag = std::sqrt(std::pow(movementInput.x, 2) + std::pow(movementInput.y, 2));
	movementInput /= mag;

	// Character update applies movement input and checks collisions
	Character::update(dt);
}
