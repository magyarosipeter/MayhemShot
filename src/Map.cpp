#include "Map.h"

///////////////////////////////////////////////////
// TILE CLASS FUNCTIONS
///////////////////////////////////////////////////
Tile::Tile() {
    hitbox.setSize(sf::Vector2f(MAP_TILE_SIZE,MAP_TILE_SIZE));
    hitbox.setOrigin(sf::Vector2f(hitbox.getSize().x/2, hitbox.getSize().y/2));
    sprite.setOrigin(sf::Vector2f(hitbox.getSize().x/2, hitbox.getSize().y/2));
    hitbox.setFillColor(sf::Color::Red);
    solid = false;
}

sf::FloatRect Tile::globalBounds() {
    return hitbox.getGlobalBounds();
}

short int Tile::getId() {
    return this->id;
}

void Tile::setTextureRect(sf::IntRect intRect) {
    sprite.setTextureRect(intRect);
}

void Tile::setAttributes(short int id, sf::Vector2f position, sf::Texture* texture) {
    this->texture = texture;
    sprite.setTexture(*this->texture);
    sprite.setPosition(position);
    hitbox.setPosition(position);
    this->id = id;

    if (id==1) { //grass block
        solid = true;
        hitbox.setFillColor(sf::Color::Green);
        sprite.setTextureRect(sf::IntRect(MAP_TILE_SIZE,0,MAP_TILE_SIZE,MAP_TILE_SIZE));
    } else if (id==0) { //air block
        solid = false;
        hitbox.setFillColor(SKY_BLUE);
        sprite.setTextureRect(sf::IntRect(4*MAP_TILE_SIZE,0,MAP_TILE_SIZE,MAP_TILE_SIZE));
    }
}

bool Tile::isSolid() {
    return solid;
}

void Tile::drawToScreen(sf::RenderWindow &window) {
    //window.draw(hitbox);
    window.draw(sprite);
}

///////////////////////////////////////////////////
// MAP CLASS FUNCTIONS
///////////////////////////////////////////////////
Map::Map() {

}

void Map::loadMap(std::string textureLocation, std::string mapLocation) {
    spriteSheet.loadFromFile(textureLocation);
    pSpriteSheet = &spriteSheet;
    std::ifstream fin(mapLocation.c_str());
    for (int i=0 ; i<MAP_HEIGHT ; i++) {
        for (int j=0 ; j<MAP_WIDTH ; j++) {
            short int szam;
            fin >> szam;
            tileMap[i][j].setAttributes(szam, sf::Vector2f(MAP_TILE_SIZE/2+j*MAP_TILE_SIZE, MAP_TILE_SIZE/2+i*MAP_TILE_SIZE), pSpriteSheet);
        }
    }
    for (int i=0 ; i<MAP_HEIGHT ; i++) {
        for (int j=0 ; j<MAP_WIDTH ; j++) {
            if (tileMap[i][j].getId()==1) {
                //upper left corner
                if (i==0 and j==0) tileMap[i][j].setTextureRect(sf::IntRect(4*MAP_TILE_SIZE, 4*MAP_TILE_SIZE, -MAP_TILE_SIZE, MAP_TILE_SIZE));
                //upper right corner
                else if (i==0 and j==MAP_WIDTH-1) tileMap[i][j].setTextureRect(sf::IntRect(3*MAP_TILE_SIZE, 4*MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE));
                //lower right corner
                else if (i==MAP_HEIGHT-1 and j==MAP_WIDTH-1) tileMap[i][j].setTextureRect(sf::IntRect(3*MAP_TILE_SIZE, 3*MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE));
                //lower left corner
                else if (i==MAP_HEIGHT-1 and j==0) tileMap[i][j].setTextureRect(sf::IntRect(4*MAP_TILE_SIZE, 3*MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE));
                //ceiling
                else if (i==0) tileMap[i][j].setTextureRect(sf::IntRect(1*MAP_TILE_SIZE, 3*MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE));
                //left wall
                else if (j==0) tileMap[i][j].setTextureRect(sf::IntRect(2*MAP_TILE_SIZE, 2*MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE));
                //right wall
                else if (j==MAP_WIDTH-1) tileMap[i][j].setTextureRect(sf::IntRect(0, 2*MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE));
                //bottom
                else if (i==MAP_HEIGHT-1) tileMap[i][j].setTextureRect(sf::IntRect(MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE));
                //left cliff
                else if ( !tileMap[i-1][j].isSolid() and !tileMap[i][j-1].isSolid() and !tileMap[i+1][j].isSolid() and tileMap[i][j+1].isSolid() ) tileMap[i][j].setTextureRect(sf::IntRect(0, 0, MAP_TILE_SIZE, MAP_TILE_SIZE));
                //right cliff
                else if ( !tileMap[i-1][j].isSolid() and !tileMap[i][j+1].isSolid() and !tileMap[i+1][j].isSolid() and tileMap[i][j-1].isSolid() ) tileMap[i][j].setTextureRect(sf::IntRect(2*MAP_TILE_SIZE, 0, MAP_TILE_SIZE, MAP_TILE_SIZE));
                //right cliff when next to right wall
                else if ( !tileMap[i-1][j].isSolid() and !tileMap[i+1][j].isSolid() and tileMap[i][j-1].isSolid() and j==MAP_WIDTH-2 ) tileMap[i][j].setTextureRect(sf::IntRect(2*MAP_TILE_SIZE, 0, MAP_TILE_SIZE, MAP_TILE_SIZE));
                //left cliff when next to left wall
                else if ( !tileMap[i-1][j].isSolid() and !tileMap[i+1][j].isSolid() and tileMap[i][j+1].isSolid() and j==1 ) tileMap[i][j].setTextureRect(sf::IntRect(0, 0, MAP_TILE_SIZE, MAP_TILE_SIZE));
            } else {
                tileMap[i][j].setTextureRect(sf::IntRect(4*MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE));
            }
        }
    }
}

void Map::drawToScreen(sf::RenderWindow &window) {
    for (int i=0 ; i<MAP_HEIGHT ; i++) {
        for (int j=0 ; j<MAP_WIDTH ; j++) {
            tileMap[i][j].drawToScreen(window);
        }
    }
}
