#include "PickUp.h"

PickUp::PickUp() {
	this->x = rand() % 18;
	this->y = rand() % 18;
	if (this->x < 8) {
		currentAbility = 1;
		std::cout << "One" << std::endl;
	}
	else {
		currentAbility = 0;
		std::cout << " Two" << std::endl;
	}

}

PickUp::~PickUp() {
	std::cout << "PickUp entity destroyed" << std::endl;
}

void PickUp::ability(Player& player) {
	switch (currentAbility) {
	case 0: //add 5 breaks
		if (player.currentBreaks + 5 <= player.totalBreaks) {
			player.currentBreaks += 5; //adds 5 to players breaks
		}
		else {
			player.currentBreaks = player.totalBreaks; //fills players breaks if adding 5 would result in being over total breaks
		}
		break;
	case 1: //add 20 health
		if (player.currentHealth + 20 <= player.maxHealth) {
			player.currentHealth += 20; //adds 20 to players health
		}
		else {
			player.currentHealth = player.maxHealth; //fills players breaks if adding 5 would result in being over total breaks
		}
		break;
	default:
		std::cout << "Error with pickup" << std::endl;
		break;
	}
}