/*
The main loop for the game, calls event handlers and stores key class objects [PLAYER, WORLD]
Please do not store functions or variables inside of this file unless absolutely neccesary.
*/

#include "common.h" //common.h holds key precompilers 
#include "Variables.h"
#include "Functions.h"
#include "World.h"
#include "EventHandler.h"
#include "Player.h"

/*
TO DO
------
ADD PICKUPS 
ADD ENEMYS
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
    players.setLocation(playerStartPositionX, playerStartPositionY);
    world.createMap(mapWidth, mapLength); //creates map of n^2 where n is length. Note: length and width should be equal. 
    loadTextures(); //loads all texture files and fonts into memory
    players.playerObject.setTexture(&(playerTexture)); //loads player texture

    sf::Clock clock;
    float lastTime = 0;
    int pindex = 0; //used to identify player index replace later

    //sfml definitions 
    sf::RenderWindow window(sf::VideoMode(world.mapWidth * tileWidth, world.mapHeight * tileLength), gameName); //creates window assuming tile length 50x50
    window.setIcon(50, 50, icon.getPixelsPtr()); //sets window icon

    while (window.isOpen()) //event loop
    {
        sf::Event event;
        if (fpsEnabled) { //displays fps
            float currentTime = clock.restart().asSeconds();
            float fps = 1.f / (currentTime);
            lastTime = currentTime;
            std::cout << fps << std::endl;
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        handler.input(world, players); //handles input 
        int index = 0;
        //loops through map vector drawing tiles onto the screen. 
        for (int i = 0; i < world.mapHeight; ++i) { //y-axis
            for (int j = 0; j < world.mapWidth; ++j) { //x-axis
                    if (world.map.at(index).z == '=') {
                        window.draw(getShape(j, i, 0, players));
                    }
                    else if (world.map.at(index).z == 'P') {
                        window.draw(getShape(j, i, 2, players));
                    }
                    else {
                        window.draw(getShape(j, i, 1, world));
                    }
                    index += 1;
            }
        }

        //displays remaining breaks
        window.draw(players.playerObject); //draws player texture to screen
        window.draw(drawTextToScreen(((tileWidth * mapWidth) - 320), 0, 26, ("Total Breaks Remaining : " + std::to_string(players.currentBreaks))));
        //displays health
        window.draw(drawTextToScreen(5, 0, 26, ("Health : " + std::to_string(players.currentHealth))));

        window.display(); //displays map
        
    }

    return 0;
}