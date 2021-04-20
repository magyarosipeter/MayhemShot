#pragma once

#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual void movement() = 0;
    virtual void drawToScreen(sf::RenderWindow &window) = 0;

protected:
    sf::RectangleShape hitbox;
    sf::Texture texture;
    sf::Sprite sprite;
};
