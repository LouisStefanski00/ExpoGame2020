/*
The main loop for the game, calls event handlers and stores key class objects [PLAYER, WORLD]
Please do not store functions or variables inside of this file unless absolutely neccesary.
*/

#include "common.h" //common.h holds key precompilers 
#include "Functions.h"
#include "World.h"
#include "EventHandler.h"
#include "Player.h"
#include "PickUp.h"

/*
TO DO
------
ADD ENEMYS

Enemy - add in texture,,,, create other actions..., use sf::Time with clock in window to determine time intervals
ADD SPECIAL TILES?
IMPROVE MAP GENERATION
SOUNDS?
SKINS?
*/


int main()
{
    //class definitions 
    World world; //map
    EventHandler handler; //event handler
    Player players;

   // players.setLocation(playerStartPositionX, playerStartPositionY);
    world.createMap(mapWidth, mapLength); //creates map of n^2 where n is length. Note: length and width should be equal. 
    world.generateEntities(2);

    loadTextures(); //loads all texture files and fonts into memory
    players.getTexture(); //sets players texture
    int pindex = 0; //used to identify player index replace later

    //sfml definitions 
    sf::RenderWindow window(sf::VideoMode(world.mapWidth * tileWidth, world.mapHeight * tileLength), gameName); //creates window assuming tile length 50x50
    window.setIcon(50, 50, icon.getPixelsPtr()); //sets window icon

    while (window.isOpen()) //event loop
    {
        sf::Event event;
        world.getFps(fpsEnabled);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        handler.input(world, players); //handles input 
        drawMainWindow(window, players, world); //draws map to the scren
        drawEntities(window, players, world.enemies); //draws additional entities such as player, enemies, and text
        encounterHandler(players, world); //handles attacks
        window.display(); //displays screen objects

    }

    return 0;
}