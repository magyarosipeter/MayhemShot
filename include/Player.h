#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Entity.h"
#include "MoreInfo.h"
#include "Map.h"

#define JUMP_SPEED -40
#define SIDE_SPEED 11

#define JUMP_COOLDOWN_FRAMES 15

class Player : public Entity {
public:
    Player();

    virtual void movement(Tile tileMap[MAP_HEIGHT][MAP_WIDTH]);
    virtual void drawToScreen(sf::RenderWindow &window);

private:
    int xSpeed, ySpeed;
    bool falling;
    unsigned jumpFrames;         //counts the number of frames since the character last started jumped
    unsigned shootFrames;        //counts the number of frames since the character last shot
};
