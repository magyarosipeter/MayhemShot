#pragma once

#include <SFML/Graphics.hpp>
#include "MoreInfo.h"
#include <cmath>

class Projectile {
public:
    Projectile();

    void initialize(double angle, sf::Vector2f startingPos, int bulletSpeed, int bulletDamage);

    //called every frame to move bullet forward
    void movement();

    //getters
    sf::Vector2f getPosition();
    int getHitboxRadius();
    sf::FloatRect globalBounds();
    int getDamage();

    //draw
    void drawToScreen(sf::RenderWindow &window);

    sf::CircleShape hitbox;

private:
    int damage;
    sf::Vector2f velocity;
};
