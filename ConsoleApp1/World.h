/*
This file defines the World class and also defines the tile struct used to create the map.
*/
#pragma once
#include "common.h"

struct tile { //tile is a struct that defines an x and y cord for the object. The z field is used to denote the tile identifier. Please see
	//World.cpp file for listing of identifications 
	int x, y; 
	char z; //tile definition '=' = pathway; 'P' = player; '*' = rock
};


class World
{
public:

	void createMap(int mapWidth, int mapHeight);
	std::vector<tile> map; //stores a vector of tile objects denoting key map characteristics. 
	int mapHeight;
	int mapWidth;
	World();
};