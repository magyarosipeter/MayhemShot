#include "WeaponCrate.h"

WeaponCrate::WeaponCrate() {
    hitbox.setSize(sf::Vector2f(32,32));
    hitbox.setOrigin(sf::Vector2f(hitbox.getSize().x/2,hitbox.getSize().y/2));
    hitbox.setFillColor(sf::Color::White);

    texture.loadFromFile(WEAPON_CRATE_TEXTURE);
    sprite.setTexture(texture);

    sprite.setOrigin(sf::Vector2f(hitbox.getSize().x/2,hitbox.getSize().y/2));
}

sf::FloatRect WeaponCrate::globalBounds() {
    return hitbox.getGlobalBounds();
}

void WeaponCrate::setRandomPosition( Tile tileMap[MAP_HEIGHT][MAP_WIDTH] ) {
    sf::Vector2i pos;

    bool ok=false;

    do {
        pos.x=rand()%MAP_WIDTH;
        pos.y=rand()%MAP_HEIGHT;
        if (pos.y!=0 && tileMap[pos.y][pos.x].isSolid() && !tileMap[pos.y-1][pos.x].isSolid() ) {
            hitbox.setPosition(sf::Vector2f(pos.x*MAP_TILE_SIZE+hitbox.getSize().x, pos.y*MAP_TILE_SIZE-hitbox.getSize().y/2));
            sprite.setPosition(hitbox.getPosition());
            ok=true;
        }
    } while (!ok);
}

Weapon* WeaponCrate::rollWeapon() {
    int roll = rand()%4;
    switch (roll) {
    case 0:
        return new Pistol;
        break;
    case 1:
        return new Shotgun;
        break;
    case 2:
        return new Rifle;
        break;
    case 3:
        return new Sniper;
        break;
    default:
        return new Pistol;
    }
}

void WeaponCrate::drawToScreen(sf::RenderWindow &window) {
    window.draw(sprite);
}
