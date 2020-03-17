/*
This file is responsable for all functions contained in world.h
Only use for class functions.
*/
#include "World.h"

void World::createMap(int mapWidth, int mapHeight)
{
	this->mapWidth = mapWidth; //sets mapWidth and mapHeight from arguments 
	this->mapHeight = mapHeight;

	//Notes about tile identifiers 
	// The '=' is a pathway. The pathway allows the player object to move onto it.
	// The '*' is a rock. The rock does not allow the player to move onto it, but will allow the player to break it. 

	for (int i = 0; i < mapHeight; ++i) { //loops through columns; y-cord
		for (int j = 0; j < mapWidth; ++j) { //loops through rows; x-cord
			if (j % 2 == 0) {
				this->map.push_back(tile{ j, i, '=', OPEN});
			}
			else if (i < 5) {
				this->map.push_back(tile{ j, i, '=', OPEN});

			}
			else {
				this->map.push_back(tile{ j, i, '*', SOLID});
			}
		}
	}
}

void World::generateEntities(int numOfEntities) {
	for (int i = 0; i < numOfEntities; ++i) {
		PickUp* pickUp = new PickUp;
		this->map.at(((pickUp->y * mapWidth) + pickUp->x)).z = '+';
		this->map.at(((pickUp->y * mapWidth) + pickUp->x)).identifier = ABILITY;

		this->entities.push_back(*pickUp);
	}
}


World::World() {
	lastClockTime = 0;
}

void World::getFps(bool fpsEnabled) //gets fps
{
	timeElaspsed = clock.getElapsedTime();
	if (fpsEnabled) { //displays fps
		float fps = sf::seconds(1) / (timeElaspsed);
		std::cout << fps << std::endl;
	}

}