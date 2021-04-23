#include "Player.h"

Player::Player() {
    hitbox.setSize(sf::Vector2f(40,60));
    hitbox.setOrigin(sf::Vector2f(hitbox.getSize().x/2, hitbox.getSize().y/2));
    hitbox.setPosition(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
    hitbox.setFillColor(sf::Color::Blue);

    xSpeed = 0;
    ySpeed = 0;
    falling = false;

    jumpFrames = JUMP_COOLDOWN_FRAMES+1;
}

void Player::movement(Tile tileMap[MAP_HEIGHT][MAP_WIDTH]) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        xSpeed = -SIDE_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        xSpeed = SIDE_SPEED;
    } else {
        xSpeed = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !falling && jumpFrames>JUMP_COOLDOWN_FRAMES && ySpeed==0) {
        ySpeed = JUMP_SPEED;
        falling = true;
        jumpFrames = 0;
    }

    if (ySpeed < -2*JUMP_SPEED) {
        ySpeed += GRAVITY;
    }

    jumpFrames++;

    //std::cout << std::max(0,(int) hitbox.getPosition().x/64-2) << " " << (int) hitbox.getPosition().x/64  << " " << std::min(MAP_WIDTH,((int) hitbox.getPosition().x/64 + 2)) << std::endl;

    ///////////////////////
    // No need to check the whole array of blocks for collisions, eunogh to check the ones surrounding the player
    // horizontal coordinates
    int kezdetX = std::max(0,(int) hitbox.getPosition().x/64-2);
    int hatarX = std::min(MAP_WIDTH,((int) hitbox.getPosition().x/64 + 2));
    // vertical coordinates - cause errors with collision, so for now we don't use them
    // int kezdetY = std::max(0,(int) hitbox.getPosition().y/64-2);
    // int hatarY = std::min(MAP_HEIGHT,((int) hitbox.getPosition().y/64 + 2));

    hitbox.move(xSpeed,0);
    if (xSpeed!=0) {
        for (int i=0 ; i<MAP_HEIGHT; i++) {
            for (int j=kezdetX ; j<hatarX ; j++) {
                if ( tileMap[i][j].isSolid() && tileMap[i][j].hitbox.getGlobalBounds().intersects(hitbox.getGlobalBounds()) ) {
                    if (xSpeed>0) {
                        hitbox.setPosition(tileMap[i][j].hitbox.getPosition().x-tileMap[i][j].hitbox.getSize().x/2-hitbox.getSize().x/2, hitbox.getPosition().y);
                    }
                    else if (xSpeed<0) {
                        hitbox.setPosition(tileMap[i][j].hitbox.getPosition().x+tileMap[i][j].hitbox.getSize().x/2+hitbox.getSize().x/2, hitbox.getPosition().y);
                    }
                    xSpeed = 0;
                }
            }
        }
    }

    hitbox.move(0, ySpeed);
    if (ySpeed!=0) {
        for (int i=0 ; i<MAP_HEIGHT; i++) {
            for (int j=kezdetX ; j<hatarX ; j++) {
                if ( tileMap[i][j].isSolid() && tileMap[i][j].hitbox.getGlobalBounds().intersects(hitbox.getGlobalBounds()) ) {
                    if (ySpeed>0) {
                        hitbox.setPosition(hitbox.getPosition().x, tileMap[i][j].hitbox.getPosition().y-tileMap[i][j].hitbox.getSize().y/2-hitbox.getSize().y/2);
                        falling = false;
                    }
                    else if (ySpeed<0) {
                        hitbox.setPosition(hitbox.getPosition().x, tileMap[i][j].hitbox.getPosition().y+tileMap[i][j].hitbox.getSize().y/2+hitbox.getSize().y/2);
                    }
                    ySpeed = 0;
                }
            }
        }
    }

    if (hitbox.getPosition().y>SCREEN_HEIGHT*2) {
        hitbox.setPosition(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
        ySpeed = 0;
    } else if ( hitbox.getPosition().y-hitbox.getSize().y/2 < 0 ) {
        hitbox.setPosition(hitbox.getPosition().x, hitbox.getSize().y/2 );
        ySpeed = 0;
    }
}

void Player::drawToScreen(sf::RenderWindow &window) {
    window.draw(hitbox);
}
