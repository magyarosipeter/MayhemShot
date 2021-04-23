#include "Map.h"

///////////////////////////////////////////////////
// TILE CLASS FUNCTIONS
///////////////////////////////////////////////////
Tile::Tile() {
    hitbox.setSize(sf::Vector2f(64,64));
    hitbox.setOrigin(sf::Vector2f(hitbox.getSize().x/2, hitbox.getSize().y/2));
    sprite.setOrigin(sf::Vector2f(hitbox.getSize().x/2, hitbox.getSize().y/2));
    hitbox.setFillColor(sf::Color::Red);
    solid = false;
}

sf::FloatRect Tile::globalBounds() {
    return hitbox.getGlobalBounds();
}

void Tile::setAttributes(short int id, sf::Vector2f position, sf::Texture* texture) {
    this->texture = texture;
    sprite.setTexture(*this->texture);
    sprite.setPosition(position);
    hitbox.setPosition(position);

    if (id==1) { //grass block
        solid = true;
        hitbox.setFillColor(sf::Color::Green);
        sprite.setTextureRect(sf::IntRect(64,0,64,64));
    } else if (id==0) { //air block
        solid = false;
        hitbox.setFillColor(SKY_BLUE);
        sprite.setTextureRect(sf::IntRect(4*64,0,64,64));
    }
}

bool Tile::isSolid() {
    return solid;
}

void Tile::drawToScreen(sf::RenderWindow &window) {
    window.draw(hitbox);
    window.draw(sprite);
}

///////////////////////////////////////////////////
// MAP CLASS FUNCTIONS
///////////////////////////////////////////////////
Map::Map() {

}

void Map::loadMap(std::string textureLocation) {
    spriteSheet.loadFromFile(textureLocation);
    pSpriteSheet = &spriteSheet;
    std::ifstream fin("resources/maps/map1.in");
    for (int i=0 ; i<13 ; i++) {
        for (int j=0 ; j<20 ; j++) {
            short int szam;
            fin >> szam;
            tileMap[i][j].setAttributes(szam, sf::Vector2f(32+j*64, 32+i*64), pSpriteSheet );
        }
    }
}

void Map::drawToScreen(sf::RenderWindow &window) {
    for (int i=0 ; i<13 ; i++) {
        for (int j=0 ; j<20 ; j++) {
            tileMap[i][j].drawToScreen(window);
        }
    }
}
