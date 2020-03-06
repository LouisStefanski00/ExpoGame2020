#pragma once
/*
* A file that holds key precompilers
* NOTE: DO NOT INCLUDE ANY CUSTOM HEADER OR CPP FILES IN THIS FILE
*/
typedef enum { SOLID, OPEN, ABILITY, ENEMY } IDENTIFIER;
struct tile { //tile is a struct that defines an x and y cord for the object. The z field is used to denote the tile identifier. Please see
	//World.cpp file for listing of identifications 
	int x, y;
	char z; //tile definition '=' = pathway; 'P' = player; '*' = rock; '+' = pick up
	//int identifier;
	IDENTIFIER identifier;
};

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
