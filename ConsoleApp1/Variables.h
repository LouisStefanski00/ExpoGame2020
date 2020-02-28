#pragma once
#include <string>
#include "common.h"

sf::Font font;

sf::Texture playerTexture;
sf::Texture rockTexture;
sf::Texture dirtTexture;
sf::Image icon;

std::string gameName = "Demo 1.1";

bool fogOfDisplay = false;
bool fpsEnabled = true;

int tileLength = 50;
int tileWidth = 50;

int mapLength = 18;
int mapWidth = 18;

int playerStartPositionX = 0;
int playerStartPositionY = 0;
