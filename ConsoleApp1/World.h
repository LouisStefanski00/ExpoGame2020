/*
This file defines the World class and also defines the tile struct used to create the map.
*/
#pragma once
#include "common.h"
#include "PickUp.h"
#include "Enemy.h"

class World
{
public:
	void createMap(int mapWidth, int mapHeight);
	void generateEntities(int numOfEntities); //generities numOfEntities entities
	void getFps(bool fpsEnabled); //function to get fps

	std::vector<tile> map; //stores a vector of tile objects denoting key map characteristics. 
	std::vector<PickUp> entities; //holds all active entities on screen
	std::vector<Enemy> enemies;

	int mapHeight;
	int mapWidth;

	double lastClockTime; //last time the clock recorded

	sf::Clock clock; //window clock

	World();
};