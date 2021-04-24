#pragma once

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "MoreInfo.h"

class Tile {
public:
    Tile();
    void setAttributes(short int id, sf::Vector2f position, sf::Texture* texture);
    void drawToScreen(sf::RenderWindow &window);
    bool isSolid();
    sf::FloatRect globalBounds();
    sf::RectangleShape hitbox;

private:
    bool solid;
    short int id;
    sf::Texture* texture;
    sf::Sprite sprite;
};

class Map {
public:
    Map();
    Tile tileMap[13][20];
    void loadMap(std::string textureLocation);
    void drawToScreen(sf::RenderWindow &window);

private:
    sf::Texture spriteSheet;
    sf::Texture* pSpriteSheet;
};