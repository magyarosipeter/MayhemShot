#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "MoreInfo.h"

#define SIDE_SPEED_ENEMY 4

class Enemy : public Entity {
public:
    Enemy();

    virtual void movement(Tile tileMap[MAP_HEIGHT][MAP_WIDTH], sf::RenderWindow &window);
    virtual void drawToScreen(sf::RenderWindow &window);

    //setters
    void setAngry();        //enemies become angry when they fall and are faster than normal
    void setHealth(int newValue);

    //getters
    sf::Vector2f getPosition();
    sf::FloatRect globalBounds();
    int getHealth();

private:
    int xSpeed, ySpeed;
    bool falling;
    int health;

};
