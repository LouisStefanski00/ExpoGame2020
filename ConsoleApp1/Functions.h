#pragma once
#include "common.h"
#include "Variables.h"
#include "Enemy.h"

//A function to draw a tile on the screen. Takes x and y cords and a tileVal as defined.
template <typename K>
sf::RectangleShape getShape(int xAxis, int yAxis, int tileVal, K& textureParent) { //0 walkway 1 rock
    sf::RectangleShape square(sf::Vector2f(tileWidth, tileLength)); //creates object surface
    square.setPosition((xAxis * tileWidth), (yAxis * tileWidth)); //sets position of object
    if (tileVal == 0) { //determines texture & sets texture
        square.setTexture(&(dirtTexture));
    }
    else if (tileVal == 2) {
        square.setTexture(&(dirtTexture));
    }
    else if (tileVal == 5) {
        square.setFillColor(sf::Color::Black);
    }
    else if (tileVal == 6) {
        square.setFillColor(sf::Color::Blue);
    }
    else {
        square.setTexture(&(rockTexture));
    }
    return square;
}

sf::Text drawTextToScreen(int xPosition, int yPosition, int textSize, std::string textToScreen) { //a function to display text to screen
    sf::Text text;
    text.setFont(font);
    text.setString(textToScreen);
    text.setCharacterSize(textSize);
    text.setPosition(xPosition, yPosition);
    text.setFillColor(sf::Color::White);
    return text;
}

void loadTextures() { //a function to load all required game textures and fonts
    //textures
    rockTexture.loadFromFile("textures/rock.png");
   // playerTexture.loadFromFile("textures/player-right.jpg");
    dirtTexture.loadFromFile("textures/dirt.png");

    //fonts
    font.loadFromFile("fonts/sansation.ttf"); //loads font 

    //icons
    icon.loadFromFile("textures/dirt.png"); //loads window icon
}

template <typename K, typename V>
int findEntityPosition(K& map, V& player) { //finds entities position in vector, specific to abilities
    int entityPos;
    for (int i = 0; i < map.entities.size(); ++i) {
        if ((map.entities.at(i).x == player.x) && (map.entities.at(i).y == player.y)) {
            entityPos = i;
        }
    }
    return entityPos;
}

template <typename K, typename V, typename P>
void drawMainWindow(K& window, V& players, P& world) {
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
            else if (world.map.at(index).z == '+') {
                int tempVal; //redo later as a function 
                for (int z = 0; z < world.entities.size(); ++z) { //finds index in entities
                    if ((world.entities.at(z).x == j) && (world.entities.at(z).y == i)) {
                        tempVal = z;
                    }
                }
                switch (world.entities.at(tempVal).currentAbility) { //determins texture
                case 0:
                    window.draw(getShape(j, i, 5, players));
                    break;
                case 1:
                    window.draw(getShape(j, i, 6, players));
                    break;
                }
            }
            else {
                window.draw(getShape(j, i, 1, world));
            }
            index += 1;
        }
    }
}

template <typename K, typename V, typename P, typename S>
void drawEntities(K& window, V& players, P& enemies, S& map) { //draws player, enemies, and text

    if (enemies.size() > 0) { //all of the code in this if statement will later be removed
        int max = enemies.size();
        for (int i = 0; i < max; ++i) {
            if (enemies.size() > 1) {
                std::cout << enemies.at(1).yPosition << std::endl;
            }
            enemies.at(i).enemyObject.setPosition(enemies.at(i).xPosition * 50, enemies.at(i).yPosition * 50);
            if (enemies.at(i).alive) {
                window.draw(enemies.at(i).enemyObject);
            }
            max = enemies.size();
        }
    }

    window.draw(drawTextToScreen(((tileWidth * mapWidth) - 320), 0, 26, ("Total Breaks Remaining : " + std::to_string(players.currentBreaks))));
    //displays health
    window.draw(drawTextToScreen(5, 0, 26, ("Health : " + std::to_string(players.currentHealth))));
    window.draw(players.playerObject); //draws player texture to screen

}

template <typename K, typename V>
void spawnEnemy(K* player, V& map) { //spawns an enemy with reference to players location, create spawn delay
    Enemy* ptr = new Enemy(player, map);
    int location = (ptr->yPosition * mapWidth) + ptr->xPosition;
    if (map.map.at(location).z != 'E') {
        map.map.at(location).identifier = SOLID;
        map.map.at(location).z = 'E';
        map.enemies.emplace_back(*ptr);
    }
    else {
        
       }
}

template <typename K, typename V>
void encounterHandler(K& player, V& map) {
    for (int i = 0; i < map.enemies.size(); ++i) { //attacks player if player is in an enemy guard block
        if (((player.y * mapLength) + player.x) == map.enemies.at(i).guardBlock) {
            if (map.enemies.at(i).alive) {
                map.enemies.at(i).attack(player, map); //attacks player
            }
        }
    }
    player.update(map);
}

template <typename V>
int findEnemy(V& map, int location) {
    for (int i = 0; i < map.enemies.size(); ++i) {
        if (((map.enemies.at(i).yPosition * mapWidth) + map.enemies.at(i).xPosition) == location) {
            return i;
        }
    }
}