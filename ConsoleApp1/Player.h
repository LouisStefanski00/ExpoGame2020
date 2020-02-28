/*
This file defines the Player class and holds functions relating to the player object
*/
#pragma once
class Player
{
public:
	int x, y; //these variables refer to the tile struct coords
	int realX, realY; //these variables refer to the pixel coords
	int totalBreaks = 15;
	int currentBreaks;
	int maxHealth = 100;
	int currentHealth;
	double speed = 5;
	void move(int dx, int dy);
	void setLocation(int x, int y);
	sf::RectangleShape playerObject; //phyiscal player object present in game world
	Player();
	~Player();
};

inline Player::Player() {
	currentBreaks = totalBreaks;
	playerObject.setSize(sf::Vector2f(50, 50)); //sets size of player object
	currentHealth = maxHealth;
	realX = 0;
	realY = 0;
	x = 0;
	y = 0;
}

inline Player::~Player() {
	std::cout << "Player object destroyed." << std::endl;
}

inline void Player::move(int dx, int dy) //moves the player by dx and dy where dx is the tiles moved and dy is the tiles moved.
{
	//This function is not normally used. Most movements are handled by Player::setLocation
	//Although this could be used if a suitable need arises. Just note: x and y do NOT correspond directly to the World::map vector
	this->x += dx;
	this->y += dy;
}

inline void Player::setLocation(int x, int y) //x and y correspond directly to the players x and y cords
{
	//Use this function to move players location, NOTE: this function has the same overhead as move
	this->x = x;
	this->y = y;
}