#pragma once
#include "common.h"
#include "Variables.h"

//A function to draw a tile on the screen. Takes x and y cords and a tileVal as defined.
template <typename K>
sf::RectangleShape getShape(int xAxis, int yAxis, int tileVal, K& textureParent) { //0 walkway 1 rock
    sf::RectangleShape square(sf::Vector2f(tileWidth, tileLength)); //assumes the tiles are 50x50, modify with variable later
    square.setPosition((xAxis * tileWidth), (yAxis * tileWidth));
    if (tileVal == 0) {
        square.setTexture(&(dirtTexture));
    }
    else if (tileVal == 2) {
        square.setTexture(&(dirtTexture));
       // square.setTexture(&(playerTexture));
    }
    else if (tileVal == 5) {
        square.setFillColor(sf::Color::Black);
    }
    else if (tileVal == 6) {
        square.setFillColor(sf::Color::Black);

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
    playerTexture.loadFromFile("textures/player-right.jpg");
    dirtTexture.loadFromFile("textures/dirt.png");

    //fonts
    font.loadFromFile("fonts/sansation.ttf"); //loads font 

    //icons
    icon.loadFromFile("textures/dirt.png"); //loads window icon
}
