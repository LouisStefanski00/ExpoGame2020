#pragma once
#include "common.h"
class Enemy
{
public:
	int health;
	int xPosition, yPosition;
	int attackDamage;
	int guardBlock;

	sf::Time speed = sf::seconds(1);
	sf::RectangleShape enemyObject;

	template <typename K, typename V>
	void attack(K& player, V map);
	template <typename V>
	void takeDamage(int damageAmount, V& map);
	template <typename K>
	void getTexture(K& player);

	void setLocation(int xPosition, int yPosition);

	bool alive = true;
	template <typename K, typename V>
	Enemy(K* player, V& map);
	Enemy(); //dummy constructor
	~Enemy();
};

template<typename K, typename V>
inline void Enemy::attack(K& player, V map) //a function that allows the enemy object to attack a player object
{
	if (speed < sf::seconds(0)) {
		player.takeDamage(20);
		speed = sf::seconds(1);
	}
	else {
		speed -= map.timeElaspsed;
	}
}

template <typename V>
inline void Enemy::takeDamage(int damageAmount, V& map) //a function that a player object would call on the enemy object to damage it
{
	if (this->health - damageAmount > 0) {
		this->health -= damageAmount;
	}
	else {
		this->health = 1;
		int location = (this->yPosition * 18) + this->xPosition;
		int vecIndx = -1;
		for (int i = 0; i < map.enemies.size(); ++i) {
			if (((this->yPosition * 18) + this->xPosition) == location) {
				vecIndx = i;
			}
		}
		if (vecIndx != -1) {
			this->alive = false; //redundancy 
			for (int i = 0; i < map.enemies.size(); ++i) {
				if (((this->yPosition * 18) + this->xPosition) == location) {
					map.enemies.erase(map.enemies.cbegin() + i, map.enemies.cbegin() + i);
				}
			}
			//map.enemies.erase(map.enemies.cbegin() + (vecIndx) , map.enemies.cbegin() + (vecIndx)); //removes enemy from entity list, assumes 1 entity could exist at time...
			map.map.at(location).z = '=';
			map.map.at(location).identifier = OPEN;
		}
	}
}

template<typename K>
inline void Enemy::getTexture(K& player) //a function called whenever a texture is to be assigned or updated on an enemy object
{
	switch (player.facing) {
	case (0): //up
		enemyObject.setFillColor(sf::Color::Blue);
		break;
	case (1): //DOWN
		enemyObject.setFillColor(sf::Color::Magenta);
		break;
	case (2): //left
		enemyObject.setFillColor(sf::Color::Red);
		break;
	case (3): //right
		enemyObject.setFillColor(sf::Color::Black);
		break;
	}
}

inline Enemy::Enemy() {}

template<typename K, typename V>
inline Enemy::Enemy(K* player, V& map) //called on enemy objects creation
{
	this->health = 100;
	switch (player->facing) { //determins enemy x and y cords nd guard block
	case(0): //up
		this->xPosition = (player->x);
		this->yPosition = player->y - 1;
		this->guardBlock = ((yPosition + 1) * 18) + xPosition; //sub mapLength var
		break;
	case(1): //down
		this->xPosition = (player->x);
		this->yPosition = player->y + 1;
		this->guardBlock = ((yPosition - 1 ) * 18) + xPosition; //sub mapLength var
		break;
	case(2): //left
		this->xPosition = (player->x -1);
		this->yPosition = player->y;
		this->guardBlock = (yPosition * 18) + xPosition + 1; //sub mapLength var
		break;
	case(3): //right
		this->xPosition = (player->x + 1);
		this->yPosition = player->y;
		this->guardBlock = (yPosition * 18) + xPosition - 1; //sub mapLength var
		break;
	default:
		break;
	}
	this->attackDamage = 20;
	this->enemyObject.setSize(sf::Vector2f(50, 50)); //sets size of player object
	this->getTexture(*player);
}
