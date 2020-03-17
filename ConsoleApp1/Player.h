/*
This file defines the Player class and holds functions relating to the player object
*/
#pragma once
#include "common.h"
//#include "Variables.h"

typedef enum {UP, DOWN, LEFT, RIGHT} FACING;
typedef enum { WALKWAY, ROCK, ABILITYTILE } landingTile;

class Player
{
public:
	int x, y; //these variables refer to the tile struct coords
	int realX, realY; //these variables refer to the pixel coords
	int totalBreaks = 15;
	int currentBreaks;
	int maxHealth = 100;
	int currentHealth;
	int attackDamage = 20;

	sf::Time maxSpeed = sf::seconds(0.1);
	sf::Time currentSpeed = maxSpeed;

	double speed = 7;

	bool playerAlive;

	FACING facing;
	sf::RectangleShape playerObject; //phyiscal player object present in game world
	sf::Texture textureVariable;

	template <typename K>
	void move(landingTile tile, int tileWidth, int tileLength, K& map, int x, int y);
	template <typename K, typename V>
	void attack(K& enemy, V& enemyList);

	void setLocation(int x, int y);
	void takeDamage(int damageAmount);
	void getTexture();
	template <typename K>
	void reset(K& map);
	template <typename K>
	void update(K& map);

	Player();
	~Player();
};

inline void Player::takeDamage(int damageAmount) //a function called by an enemy object to damage the player object
{
	if ((currentHealth - damageAmount) > 0) {
		this->currentHealth -= damageAmount;
	}
	else {
		currentHealth = 0;
		playerAlive = false;
	}
}

inline Player::Player() { //called when a new player object is created
	currentBreaks = totalBreaks;
	playerObject.setSize(sf::Vector2f(50, 50)); //sets size of player object
	currentHealth = 79;
	facing = RIGHT;
	realX = 0;
	realY = 0;
	x = 0;
	y = 0;
	playerAlive = true;
}

template <typename V>
inline void Player::reset(V& map) { //resets player after death
	map.map.at((y * 18) + x).z = '=';
	map.map.at((y * 18) + x).identifier = OPEN;
	currentBreaks = totalBreaks;
	playerObject.setSize(sf::Vector2f(50, 50)); //sets size of player object
	currentHealth = 79;
	facing = RIGHT;
	realX = 0;
	realY = 0;
	x = 0;
	y = 0;
	map.map.at(0).z = 'P'; //replace hard coded values
	map.map.at(0).identifier = OPEN;
	playerObject.setPosition(sf::Vector2f((18 * this->x), (18 * this->y)));
	playerAlive = true;
}
inline Player::~Player() { //called when the player object is destroyed
	std::cout << "Player object destroyed." << std::endl;
}

inline void Player::setLocation(int x, int y) //moves the player by dx and dy where dx is the tiles moved and dy is the tiles moved.
{
	//This function is not normally used. Most movements are handled by Player::setLocation
	//Although this could be used if a suitable need arises. Just note: x and y do NOT correspond directly to the World::map vector
	this->x = x;
	this->y = y;
}

template <typename K>
inline void Player::move(landingTile tile, int tileWidth, int tileLength, K& map, int x, int y) //x and y correspond directly to the players x and y cords
{
	//Use this function to move players location, NOTE: this function has the same overhead as move
	int max = map.mapWidth;
	this->x = x;
	this->y = y;
	switch (tile) {
	case(WALKWAY): //movement protocol for walkway tiles
		switch (this->facing) { 
		case(UP):
			map.map.at((max * (y + 1)) + x).z = '='; //gets previous x pos
			map.map.at((max * (y + 1)) + x).identifier = OPEN;
			map.map.at((((max * y) + x))).z = 'P';
			playerObject.setPosition(sf::Vector2f((tileWidth * this->x), (tileLength * this->y)));
			break;
		case (DOWN):
			if ((y - 1) == 0) {
				map.map.at(x).z = '='; //previosu x pos
				map.map.at(x).identifier = OPEN;
			}
			else {
				map.map.at((max * (y - 1)) + x).z = '='; //previous x pos with regards to y 
				map.map.at((max * (y - 1)) + x).identifier = OPEN;
			}
			map.map.at((((max * y)) + x)).z = 'P';
			playerObject.setPosition(sf::Vector2f((tileWidth * this->x), (tileLength * this->y)));
			break;
		case(LEFT):
			map.map.at(((max * y) + (x + 1))).z = '='; //gets previous x pos
			map.map.at(((max * y) + (x + 1))).identifier = OPEN;
			map.map.at((((max * y) + x))).z = 'P';
			playerObject.setPosition(sf::Vector2f((tileWidth * this->x), (tileLength * this->y)));
			break;
		case(RIGHT):
			map.map.at(((((max * y) + (x - 1))))).z = '='; //gets previous x pos
			map.map.at(((((max * y) + (x - 1))))).identifier = OPEN;
			map.map.at(((max * y) + x)).z = 'P';
			playerObject.setPosition(sf::Vector2f((tileWidth * this->x), (tileLength * this->y)));
			break;
		}
		break;

	case(ROCK): //movement protocol for rock(solid) tiles, if these are added changes to eventHandler.h will be 
		//required as currently if a player breaks a rock tile it is assigned to a walkway tile allowing for movement...
		switch (this->facing) {
		case(UP):
			break;
		case (DOWN):
			break;
		case(LEFT):
			break;
		case(RIGHT):
			break;
		}
		break;

	case(ABILITYTILE): //movement protocol for abilitytiles(ability)
		switch (this->facing) {
		case(UP):
			map.map.at((max * (y + 1)) + x).z = '='; //gets previous x pos
			map.map.at((max * (y + 1)) + x).identifier = OPEN;
			map.map.at((((max * y) + x))).z = 'P';
			playerObject.setPosition(sf::Vector2f((tileWidth * this->x), (tileLength * this->y)));
			break;
		case (DOWN):
			if ((y - 1) == 0) {
				map.map.at(x).z = '='; //previosu x pos
				map.map.at(x).identifier = OPEN;
			}
			else {
				map.map.at((max * (y - 1)) + x).z = '='; //previous x pos with regards to y 
				map.map.at((max * (y - 1)) + x).identifier = OPEN;
			}
			map.map.at((((max * y)) + x)).z = 'P';
			playerObject.setPosition(sf::Vector2f((tileWidth * this->x), (tileLength * this->y)));
			break;
		case(LEFT):
			map.map.at(((max * y) + (x + 1))).z = '='; //gets previous x pos
			map.map.at(((max * y) + (x + 1))).identifier = OPEN;
			map.map.at((((max * y) + x))).z = 'P';
			playerObject.setPosition(sf::Vector2f((tileWidth * this->x), (tileLength * this->y)));
			break;
		case(RIGHT):
			map.map.at(((((max * y) + (x - 1))))).z = '='; //gets previous x pos
			map.map.at(((((max * y) + (x - 1))))).identifier = OPEN;
			map.map.at(((max * y) + x)).z = 'P';
			playerObject.setPosition(sf::Vector2f((tileWidth * this->x), (tileLength * this->y)));
			break;
		}
		break;
	}

}

//template <typename K>
inline void Player::getTexture() { //gets player texture based on player facing
	switch (facing) {
	case (UP):
		textureVariable.loadFromFile("textures/player-up.jpg");
		break;
	case (DOWN):
		textureVariable.loadFromFile("textures/player-down.jpg");
		break;
	case (LEFT):
		textureVariable.loadFromFile("textures/player-left.jpg");
		break;
	case (RIGHT):
		textureVariable.loadFromFile("textures/player_19.png"); //directional texture 
		break;
	}
	playerObject.setTexture(&textureVariable);
}

template<typename K, typename V>
inline void Player::attack(K& enemy, V& map) //a function called by a player object that attacks an enemy object calling the enemy objects take damage function
{
	enemy.takeDamage(this->attackDamage, map);
}

template <typename K>
inline void Player::update(K& map)  //updates players speed 
{
	if (currentSpeed < maxSpeed) {
		currentSpeed += map.timeElaspsed;
	}
}