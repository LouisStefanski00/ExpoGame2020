#include "PickUp.h"

PickUp::PickUp() {
	this->x = rand() % 18;
	this->y = rand() % 18;

}

PickUp::~PickUp() {
	std::cout << "PickUp entity destroyed" << std::endl;
}

void PickUp::ability(Player& player) {
	if (player.currentBreaks + 5 <= player.totalBreaks) {
		player.currentBreaks += 5; //adds 5 to players breaks
	}
	else {
		player.currentBreaks = player.totalBreaks; //fills players breaks if adding 5 would result in being over total breaks
	}
}