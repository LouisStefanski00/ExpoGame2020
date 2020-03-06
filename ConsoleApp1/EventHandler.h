#pragma once
#include "common.h"
#include "Player.h"
#include "Functions.h"
#include <SFML/Graphics.hpp>
class EventHandler {
public:
	template <typename K, typename V>
	void input(K& map, V& player);
private:
};

template <typename K, typename V>
inline void EventHandler::input(K& map, V& player)
// A function to handle all player actions such as movement. 
{ 
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && ((player.x + 1) < map.mapWidth)) { //gets input and checks if move is is map bounds
		if ((map.map.at(((player.y * map.mapWidth) + (player.x + 1))).identifier == OPEN)) {  //checks that the tile is a valid tile to move to
			player.facing = RIGHT;
			player.move(WALKWAY, tileWidth, tileLength, map, player.x + 1, player.y);
			sf::sleep(sf::milliseconds(player.speed * 15.0)); //sleeps for 150ms as to prevent multiple inputs from a single key press
		}
		else if ((map.map.at(((player.y * map.mapWidth) + (player.x + 1))).identifier == ABILITY)) { //when player picks up ability;
			player.facing = RIGHT;
			player.move(ABILITYTILE, tileWidth, tileLength, map, player.x + 1, player.y);
			int entityPos = findEntityPosition(map, player);
			map.entities.at(entityPos).ability(player); //performs pickup ability
			map.entities.erase(map.entities.begin() + (entityPos)); //deletes item from entities and deconstructs it
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
		else if ((player.currentBreaks > 0) && (sf::Keyboard::isKeyPressed(sf::Keyboard::K))) { //breaks block
			if ((map.map.at(((player.y * map.mapWidth) + (player.x + 1))).z != 'E'))
			//player.move(WALKWAY, tileWidth, tileLength, map, player.x + 1, player.y);
			player.facing = RIGHT;
			player.currentBreaks -= 1;
			spawnEnemy(&player, map); //spawns enemy
			sf::sleep(sf::milliseconds(player.speed * 15.0)); 
		}
	}

	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && ((player.x - 1) >= 0)) { //moving left
		if ((map.map.at((player.y * map.mapWidth) + (player.x - 1)).identifier == OPEN)){
			player.facing = LEFT;
			player.move(WALKWAY, tileWidth, tileLength , map, player.x - 1, player.y);
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
		else if ((map.map.at((player.y * map.mapWidth) + (player.x - 1)).identifier == ABILITY)) { //picks up ability
			player.facing = LEFT;
			player.move(ABILITYTILE, tileWidth, tileLength, map, player.x - 1, player.y);
			int entityPos = findEntityPosition(map, player);
			map.entities.at(entityPos).ability(player); //performs pickup ability
			map.entities.erase(map.entities.begin() + (entityPos)); //deletes item from entities and deconstructs it
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
		else if ((player.currentBreaks > 0) && (sf::Keyboard::isKeyPressed(sf::Keyboard::K))){ //breaks block
			player.currentBreaks -= 1;
			player.facing = LEFT;
			player.move(WALKWAY, tileWidth, tileLength, map, player.x - 1, player.y);
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
	}

	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && ((player.y + 1)< map.mapHeight)) { //moving right
		if ((map.map.at(((player.y + 1) * map.mapWidth) + (player.x)).identifier == OPEN)) {
			player.facing = DOWN;
			player.move(WALKWAY, tileWidth, tileLength, map, player.x, player.y + 1);
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
		else if ((map.map.at(((player.y + 1) * map.mapWidth) + (player.x)).identifier == ABILITY)) { //picks up ability
			player.facing = DOWN;
			player.move(ABILITYTILE, tileWidth, tileLength, map, player.x, player.y + 1);
			int entityPos = findEntityPosition(map, player);
			map.entities.at(entityPos).ability(player); //performs pickup ability
			map.entities.erase(map.entities.begin() + (entityPos)); //deletes item from entities and deconstructs it
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
		else if ((player.currentBreaks > 0) && (sf::Keyboard::isKeyPressed(sf::Keyboard::K))){ //breaks block
			player.currentBreaks -= 1;
			player.facing = DOWN;
			player.move(WALKWAY, tileWidth, tileLength, map, player.x, player.y + 1);
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
	}

	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && ((player.y - 1) >= 0)) { //moving up
		if ((map.map.at((((player.y - 1) * map.mapWidth)) + player.x).identifier == OPEN)) {
			player.facing = UP;
			player.move(WALKWAY, tileWidth, tileLength, map, player.x, player.y - 1);
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
		else if ((map.map.at((((player.y - 1) * map.mapWidth)) + player.x).identifier == ABILITY)) { //picksup ability
			player.facing = UP;
			player.move(ABILITYTILE, tileWidth, tileLength, map, player.x, player.y - 1);
			int entityPos = findEntityPosition(map, player);
			map.entities.at(entityPos).ability(player); //performs pickup ability
			map.entities.erase(map.entities.begin() + (entityPos)); //deletes item from entities and deconstructs it
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
		else if ((player.currentBreaks > 0) && (sf::Keyboard::isKeyPressed(sf::Keyboard::K))) { //breaks block
			player.currentBreaks -= 1;
			player.facing = UP;
			player.move(WALKWAY, tileWidth, tileLength, map, player.x, player.y - 1);
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
	}
	player.getTexture();
}
