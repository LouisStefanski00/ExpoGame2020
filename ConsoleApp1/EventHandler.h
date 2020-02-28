#pragma once
#include "common.h"
#include <SFML/Graphics.hpp>

class EventHandler {
public:
	template <typename K, typename V>
	void move(int x, int y,K& map, int direction, V& player);
	template <typename K, typename V>
	void input(K& map, V& player);
private:
};
// 1 left; 2 right; 3 down; 4 up;
template<typename K, typename V>
inline void EventHandler::move(int x, int y, K& map, int direction, V& player) //takes x,y cords. A map class object, a direction, and a player class object
// a function to handle movement requests from event handler. 
{
	int max = map.mapWidth;

	if (direction == 2) { //right hand movement
		player.setLocation(x, y); //sets location on player class
		//updates previous tile pos and current tile pos
		map.map.at(((((max * y) + (x - 1))))).z = '='; //gets previous x pos
		map.map.at(((max * y) + x)).z = 'P';
	}
	else if (direction == 1) { //left hand movememnt
		player.setLocation(x, y);
		map.map.at(((max * y) + (x + 1))).z = '='; //gets previous x pos
		map.map.at((((max * y) + x))).z = 'P';
	}
	else if (direction == 3) { //moving down the map(towards end)
		player.setLocation(x, y);
		if ((y - 1) == 0) {
			map.map.at(x).z = '='; //previosu x pos
		}
		else {
			map.map.at((max * (y - 1)) + x).z = '='; //previous x pos with regards to y 
		}
		map.map.at((((max * y)) + x)).z = 'P';
	}
	else if (direction == 4) { //moving up map(towards top, start point)
		player.setLocation(x, y);
		map.map.at((max * (y + 1)) + x).z = '='; //gets previous x pos
		map.map.at((((max * y) + x))).z = 'P';
	}
}

template <typename K, typename V>
inline void EventHandler::input(K& map, V& player) 
// A function to handle all player actions such as movement. 
{ 
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && ((player.x + 1) < map.mapWidth)) { //gets input and checks if move is is map bounds
		if ((map.map.at(((player.y * map.mapWidth) + (player.x + 1))).z != '*')) {  //checks that the tile is a valid tile to move to
			this->move(player.x + 1, player.y, map, 2, player); //calls moves function for eventhandler
			player.playerObject.setPosition(sf::Vector2f((tileWidth * player.x), (tileLength * player.y))); //sets position of playerObject 
			playerTexture.loadFromFile("textures/player_19.png"); //directional texture 
			sf::sleep(sf::milliseconds(player.speed * 15.0)); //sleeps for 150ms as to prevent multiple inputs from a single key press
		}
		else if ((player.currentBreaks > 0) && (sf::Keyboard::isKeyPressed(sf::Keyboard::K))) { //breaks block
			this->move(player.x + 1, player.y, map, 2, player);
			player.playerObject.setPosition(sf::Vector2f((tileWidth * player.x), (tileLength * player.y)));
			playerTexture.loadFromFile("textures/player-right.jpg");
			player.currentBreaks -= 1;
			sf::sleep(sf::milliseconds(player.speed * 15.0)); 
		}
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && ((player.x - 1) >= 0)) {
		if (map.map.at((player.y * map.mapWidth) + (player.x - 1)).z != '*') {
			this->move(player.x - 1, player.y, map, 1, player);
			player.playerObject.setPosition(sf::Vector2f((tileWidth * player.x), (tileLength * player.y)));

			playerTexture.loadFromFile("textures/player-left.jpg");
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
		else if ((player.currentBreaks > 0) && (sf::Keyboard::isKeyPressed(sf::Keyboard::K))){ //breaks block
			this->move(player.x - 1, player.y, map, 1, player);
			player.playerObject.setPosition(sf::Vector2f((tileWidth * player.x), (tileLength * player.y)));

			player.currentBreaks -= 1;
			playerTexture.loadFromFile("textures/player-left.jpg");
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && ((player.y + 1)< map.mapHeight)) {
		if (map.map.at(((player.y + 1) * map.mapWidth) + (player.x)).z != '*') {
			this->move(player.x, player.y + 1, map, 3, player);
			player.playerObject.setPosition(sf::Vector2f((tileWidth * player.x), (tileLength * player.y)));
			playerTexture.loadFromFile("textures/player-down.jpg");
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
		else if ((player.currentBreaks > 0) && (sf::Keyboard::isKeyPressed(sf::Keyboard::K))){ //breaks block
			this->move(player.x, player.y + 1, map, 3, player);
			player.playerObject.setPosition(sf::Vector2f((tileWidth * player.x), (tileLength * player.y)));
			player.currentBreaks -= 1;
			playerTexture.loadFromFile("textures/player-down.jpg");
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && ((player.y - 1) >= 0)) {
		if (map.map.at((((player.y - 1) * map.mapWidth)) + player.x).z != '*') {
			this->move(player.x, player.y - 1, map, 4, player);
			player.playerObject.setPosition(sf::Vector2f((tileWidth * player.x), (tileLength * player.y)));
			playerTexture.loadFromFile("textures/player-up.jpg");
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
		else if ((player.currentBreaks > 0) && (sf::Keyboard::isKeyPressed(sf::Keyboard::K))) { //breaks block
			this->move(player.x, player.y - 1, map, 4, player);
			player.currentBreaks -= 1;
			player.playerObject.setPosition(sf::Vector2f((tileWidth * player.x), (tileLength * player.y)));
			playerTexture.loadFromFile("textures/player-up.jpg");
			sf::sleep(sf::milliseconds(player.speed * 15.0));
		}
	}
}
