#pragma once
#include "common.h"
#include "Player.h"
//#include "Variables.h"
class PickUp
{
public:
	int x, y;
	int currentAbility; //0 +5 breaks; //1 + 20 health
	void ability(Player& player); //performs specified action on specified player entity
	PickUp();
	~PickUp();
};

