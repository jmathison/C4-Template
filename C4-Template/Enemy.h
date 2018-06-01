#pragma once
#include "Character.h"

class Enemy :
	public Character
{
public:

	Actor* followTarget = NULL;

	Enemy(sf::Vector2f pos, sf::Vector2f size);

	virtual void update(float dt) override;
	

};

