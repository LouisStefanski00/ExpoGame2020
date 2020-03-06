#pragma once
#include "common.h"
#include "Variables.h"

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

template <typename K, typename V, typename P>
void drawEntities(K& window, V& players, P& enemies) { //draws player, enemies, and text
    window.draw(players.playerObject); //draws player texture to screen

    if (enemies.size() > 0) { //all of the code in this if statement will later be removed
        enemies.at(0).enemyObject.setPosition(enemies.at(0).xPosition * 50, enemies.at(0).yPosition);
        window.draw(enemies.at(0).enemyObject);
        //enemies.at(0).takeDamage(20, enemies);
    }

    window.draw(drawTextToScreen(((tileWidth * mapWidth) - 320), 0, 26, ("Total Breaks Remaining : " + std::to_string(players.currentBreaks))));
    //displays health
    window.draw(drawTextToScreen(5, 0, 26, ("Health : " + std::to_string(players.currentHealth))));

}