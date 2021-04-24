#pragma once

#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "Map.h"
#include "MoreInfo.h"


class WeaponCrate {
public:
    WeaponCrate();

    sf::FloatRect globalBounds();

    void setRandomPosition(Tile tileMap[MAP_HEIGHT][MAP_WIDTH]);
    void drawToScreen(sf::RenderWindow &window);

    Weapon* rollWeapon();

private:
    sf::RectangleShape hitbox;
    sf::Texture texture;
};
