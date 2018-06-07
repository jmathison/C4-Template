#pragma once
#include "Character.h"
class Projectile :
	public Character
{
public:

	bool destroy = false;

	virtual void update(float dt) override;


	Projectile(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f direction);

};

