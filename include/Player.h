#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Entity.h"
#include "MoreInfo.h"

#define JUMP_SPEED -50
#define SIDE_SPEED 12

class Player : public Entity {
public:
    Player();

    virtual void movement();
    virtual void drawToScreen(sf::RenderWindow &window);

private:
    int xSpeed, ySpeed;
    bool falling;
};
