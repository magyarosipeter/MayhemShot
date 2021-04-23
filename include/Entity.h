#pragma once

#include <SFML/Graphics.hpp>
#include "Map.h"

class Entity {
public:
    virtual void movement(Tile tileMap[MAP_HEIGHT][MAP_WIDTH]) = 0;
    virtual void drawToScreen(sf::RenderWindow &window) = 0;

protected:
    sf::RectangleShape hitbox;
    sf::Texture texture;
    sf::Sprite sprite;
};
