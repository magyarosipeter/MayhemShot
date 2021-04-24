#pragma once

#include <SFML/Graphics.hpp>
#include "MoreInfo.h"
#include <cmath>

class Projectile {
public:
    Projectile();

    void initialize(double angle, sf::Vector2f startingPos, int bulletSpeed);

    //called every frame to move bullet forward
    void movement();

    //getters
    sf::Vector2f getPosition();
    int getHitboxRadius();
    sf::FloatRect globalBounds();

    //draw
    void drawToScreen(sf::RenderWindow &window);

    sf::CircleShape hitbox;

private:

    sf::Vector2f velocity;
};
