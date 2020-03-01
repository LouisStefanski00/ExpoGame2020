#pragma once
#include "common.h"
#include "Player.h"
//#include "Variables.h"
class PickUp
{
public:
	int x, y;
	void ability(Player& player); //performs specified action on specified player entity
	PickUp();
	~PickUp();
};

