#include "Enemy.h"


void Enemy::setLocation(int xPosition, int yPosition) //sets enemy objects location
{
	this->xPosition = xPosition;
	this->yPosition = yPosition;
}

Enemy::~Enemy() //called when enemy object is destroyed
{
	//std::cout << "Enemy object destroyed" << std::endl;
}
