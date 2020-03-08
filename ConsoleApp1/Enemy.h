#pragma once
#include "common.h"
class Enemy
{
public:
	int health;
	int xPosition, yPosition;
	int attackDamage;
	int guardBlock;

	sf::RectangleShape enemyObject;

	template <typename K>
	void attack(K& player);
	template <typename V>
	void takeDamage(int damageAmount, V& enemiesList);
	template <typename K>
	void getTexture(K& player);

	void setLocation(int xPosition, int yPosition);

	template <typename K, typename V>
	Enemy(K* player, V& map);
	Enemy(); //dummy constructor
	~Enemy();
};

template<typename K>
inline void Enemy::attack(K& player) //a function that allows the enemy object to attack a player object
{
	player.takeDamage(20);
}

template <typename V>
inline void Enemy::takeDamage(int damageAmount, V& enemiesList) //a function that a player object would call on the enemy object to damage it
{
	if (this->health - damageAmount > 0) {
		this->health -= damageAmount;
	}
	else {
		this->health = 0;
		enemiesList.erase(enemiesList.begin()); //removes enemy from entity list, assumes 1 entity could exist at time...
		this->~Enemy(); //enable after enemy is incorporated into conditional draw loop
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
