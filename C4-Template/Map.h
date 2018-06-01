#pragma once

#include<vector>
#include<map>

#include<SFML/Graphics.hpp>
#include"Actor.h"

enum TileType {
	ground,
	wall
};

typedef std::pair<unsigned int, unsigned int> gridcoord;

typedef struct {

	gridcoord coords;
	std::vector<gridcoord> adjacent;
	
} vertex;

class NavGraph
{
	
	std::map<gridcoord, vertex> vertices;

	bool getVertex(int x, int y, vertex& vert){
		auto found = vertices.find(std::make_pair(x, y));
		if (found != vertices.end()) {
			vert = found->second;
			return true;
		}
		
		return false;
	}
	
public:
	void addVertex( unsigned int x, unsigned int y, vertex v) {
		vertices.insert(std::make_pair(std::make_pair(x, y), v));
	}
};


class GameMap
{
public:

	std::vector<TileType> tiles;

	NavGraph nav;

	int mapWidth;
	int mapHeight;

	float tileSize;

	void calcNeighbors(vertex& v);

	sf::RectangleShape ground;
	sf::RectangleShape wall;

	GameMap(sf::RenderWindow& window, int width=100,int height=100);

	TileType getTile(int x, int y);

	sf::Vector2f getPixelPos(int tileX, int tileY) {
		return sf::Vector2f(tileX * tileSize, tileY * tileSize);
	}

	sf::Vector2i getTilePos(int pixelX, int pixelY) {
		return sf::Vector2i(std::floor((float) pixelX / tileSize), std::floor( (float)pixelY / tileSize));
	}

	void recalculateNav();

	void drawMap(sf::RenderWindow& window);

	bool checkTileCollision(Actor& actor);

};