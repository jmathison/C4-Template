#include "Map.h"

void GameMap::calcNeighbors(vertex & v)
{
	int x = v.coords.first;
	int y = v.coords.second;

	int coords_to_check[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

	for (auto coord : coords_to_check) {
		TileType t = getTile(x + coord[0], y + coord[1]);

		if (t != TileType::wall) {
			// If the tile is pathable, add to this vertex's connections
			gridcoord g = std::make_pair(coord[0], coord[1]);
			v.adjacent.push_back(g);
		}
	}

}

GameMap::GameMap(sf::RenderWindow& window, int width, int height)
{
	mapWidth = width;
	mapHeight = height;

	int pixelWidth = window.getSize().x;
	int pixelHeight = window.getSize().y;
	// Fit tiles to screen
	tileSize = (float)pixelHeight / (float)mapHeight;

	tiles = std::vector<TileType>(mapWidth * mapHeight);

	ground = sf::RectangleShape(sf::Vector2f(10, 10));
	ground.setFillColor(sf::Color::Green);

	wall = sf::RectangleShape(sf::Vector2f(10, 10));
	wall.setFillColor(sf::Color::White);

	// Load map here
	tiles[30] = TileType::wall;


	// Build nav grid
	recalculateNav();

}

TileType GameMap::getTile(int x, int y)
{
	if(x >= mapWidth || x < 0){
		return TileType::wall;
	}
	if (y >= mapHeight || y < 0) {
		return TileType::wall;
	}
	return tiles[y * mapWidth + x];
}

void GameMap::recalculateNav()
{
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			if (getTile(x, y) != TileType::wall) {
				// If it's not a wall, it's probably pathable!
				vertex v;
				v.coords = std::make_pair(x, y);
				calcNeighbors(v);
				nav.addVertex(x, y, v);
			}
		}
	}


}

void GameMap::drawMap(sf::RenderWindow& window)
{

	int pixelWidth = window.getSize().x;
	int pixelHeight = window.getSize().y;
	// Fit tiles to screen
	tileSize = (float) pixelHeight / (float) mapHeight;
	ground.setSize(sf::Vector2f(tileSize, tileSize));
	wall.setSize(sf::Vector2f(tileSize, tileSize));


	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			
			float draw_x = x * tileSize;
			float draw_y = y * tileSize;

			switch (getTile(x, y)) {
			case TileType::ground:
				// Draw Ground
				ground.setPosition(sf::Vector2f(draw_x, draw_y));
				window.draw(ground);
				break;
			case TileType::wall:
				// Draw Wall
				wall.setPosition(sf::Vector2f(draw_x, draw_y));
				window.draw(wall);
				break;
			}
		}
	}

}

bool GameMap::checkTileCollision(Actor & actor)
{
	// Find applicable tiles
	sf::Vector2i top_corner = getTilePos(actor.position.x, actor.position.y);
	sf::Vector2i bottom_corner = getTilePos(actor.position.x + actor.size.x, actor.position.y + actor.size.y);

	for (int y = top_corner.y; y <= bottom_corner.y; y++) {
		for (int x = top_corner.x; x <= bottom_corner.x; x++) {
			if (getTile(x, y) == TileType::wall) {
				return true;
			}
		}
	}


	return false;
}
