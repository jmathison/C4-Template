#pragma once

#include<SFML/Graphics.hpp>


class Actor
{
public:
	Actor(sf::Vector2f pos=sf::Vector2f(0,0), sf::Vector2f size = sf::Vector2f(0,0));

	sf::Vector2f position;
	sf::Vector2f size;

	virtual void init() {}

	virtual void draw(sf::RenderWindow& window) {}
	
	virtual void update(float dt) {}

	virtual bool checkCollision(const Actor& other) {
		sf::FloatRect rect(position, size);
		sf::FloatRect rect_other(other.position, other.size);

		return rect.intersects(rect_other);
	}

};

