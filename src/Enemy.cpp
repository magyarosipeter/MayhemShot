#include "Enemy.h"

Enemy::Enemy(int type, sf::Texture* staticTexture) {
    this->texture = staticTexture;
    sprite.setTexture(*this->texture);

    if (type==1) {
        hitbox.setSize(sf::Vector2f(ENEMY_1_TEXTURE_SIZE,ENEMY_1_TEXTURE_SIZE));

        health = 3;

        sprite.setOrigin(sf::Vector2f(hitbox.getSize().x/2, hitbox.getSize().y/2));
        leftAnimation.addIntRect(sf::IntRect(0,0,ENEMY_1_TEXTURE_SIZE,ENEMY_1_TEXTURE_SIZE));
        leftAnimation.addIntRect(sf::IntRect(ENEMY_1_TEXTURE_SIZE,0,ENEMY_1_TEXTURE_SIZE,ENEMY_1_TEXTURE_SIZE));
        leftAnimation.addIntRect(sf::IntRect(2*ENEMY_1_TEXTURE_SIZE,0,ENEMY_1_TEXTURE_SIZE,ENEMY_1_TEXTURE_SIZE));
        leftAnimation.addIntRect(sf::IntRect(3*ENEMY_1_TEXTURE_SIZE,0,ENEMY_1_TEXTURE_SIZE,ENEMY_1_TEXTURE_SIZE));

        rightAnimation.addIntRect(sf::IntRect(ENEMY_1_TEXTURE_SIZE,0,-ENEMY_1_TEXTURE_SIZE,ENEMY_1_TEXTURE_SIZE));
        rightAnimation.addIntRect(sf::IntRect(2*ENEMY_1_TEXTURE_SIZE,0,-ENEMY_1_TEXTURE_SIZE,ENEMY_1_TEXTURE_SIZE));
        rightAnimation.addIntRect(sf::IntRect(3*ENEMY_1_TEXTURE_SIZE,0,-ENEMY_1_TEXTURE_SIZE,ENEMY_1_TEXTURE_SIZE));
        rightAnimation.addIntRect(sf::IntRect(4*ENEMY_1_TEXTURE_SIZE,0,-ENEMY_1_TEXTURE_SIZE,ENEMY_1_TEXTURE_SIZE));
    } else if (type==2) {
        hitbox.setSize(sf::Vector2f(ENEMY_2_TEXTURE_SIZE, ENEMY_2_TEXTURE_SIZE));

        health = 6;

        leftAnimation.addIntRect(sf::IntRect(0,0,ENEMY_2_TEXTURE_SIZE,ENEMY_2_TEXTURE_SIZE));
        leftAnimation.addIntRect(sf::IntRect(ENEMY_2_TEXTURE_SIZE,0,ENEMY_2_TEXTURE_SIZE,ENEMY_2_TEXTURE_SIZE));
        leftAnimation.addIntRect(sf::IntRect(2*ENEMY_2_TEXTURE_SIZE,0,ENEMY_2_TEXTURE_SIZE,ENEMY_2_TEXTURE_SIZE));
        leftAnimation.addIntRect(sf::IntRect(3*ENEMY_2_TEXTURE_SIZE,0,ENEMY_2_TEXTURE_SIZE,ENEMY_2_TEXTURE_SIZE));

        rightAnimation.addIntRect(sf::IntRect(ENEMY_2_TEXTURE_SIZE,0,-ENEMY_2_TEXTURE_SIZE,ENEMY_2_TEXTURE_SIZE));
        rightAnimation.addIntRect(sf::IntRect(2*ENEMY_2_TEXTURE_SIZE,0,-ENEMY_2_TEXTURE_SIZE,ENEMY_2_TEXTURE_SIZE));
        rightAnimation.addIntRect(sf::IntRect(3*ENEMY_2_TEXTURE_SIZE,0,-ENEMY_2_TEXTURE_SIZE,ENEMY_2_TEXTURE_SIZE));
        rightAnimation.addIntRect(sf::IntRect(4*ENEMY_2_TEXTURE_SIZE,0,-ENEMY_2_TEXTURE_SIZE,ENEMY_2_TEXTURE_SIZE));

    }
    sprite.setOrigin(sf::Vector2f(hitbox.getSize().x/2, hitbox.getSize().y/2));
    hitbox.setFillColor(sf::Color::Magenta);
    hitbox.setOrigin(sf::Vector2f(hitbox.getSize().x/2, hitbox.getSize().y/2));
    hitbox.setPosition(sf::Vector2f(SCREEN_WIDTH/2, 0-hitbox.getSize().y/2));

    if (rand()%2==1) xSpeed = -SIDE_SPEED_ENEMY;
    else xSpeed = SIDE_SPEED_ENEMY;
    ySpeed = 0;
    falling = false;
}

//setters
void Enemy::setAngry() {
    hitbox.setPosition(sf::Vector2f(SCREEN_WIDTH/2, 0-hitbox.getSize().y/2));
    hitbox.setFillColor(sf::Color::Red);

    if (rand()%2==1) xSpeed = -2*SIDE_SPEED_ENEMY;
    else xSpeed = 2*SIDE_SPEED_ENEMY;
    ySpeed = 0;
    falling = false;

    sprite.setColor(OPAQUE_RED);
}
void Enemy::setHealth(int newValue) {
    health = newValue;
}
void Enemy::setTexture(sf::Texture* staticTexture) {
    this->texture = staticTexture;
    sprite.setTexture(*this->texture);
    sprite.setTextureRect(sf::IntRect(0,0,50,50));
}

//getters
sf::Vector2f Enemy::getPosition() {
    return hitbox.getPosition();
}
sf::FloatRect Enemy::globalBounds() {
    return hitbox.getGlobalBounds();
}
int Enemy::getHealth() {
    return health;
}

void Enemy::movement(Tile tileMap[MAP_HEIGHT][MAP_WIDTH], sf::RenderWindow &window) {
    //out of bounds check

    if (ySpeed < MAX_GRAVITY) {
        ySpeed += GRAVITY;
    }

    ///////////////////////
    // No need to check the whole array of blocks for collisions, enough to check the ones surrounding the player
    // horizontal coordinates
    int kezdetX = std::max(0,(int) hitbox.getPosition().x/64-2);
    int hatarX = std::min(MAP_WIDTH,((int) hitbox.getPosition().x/64 + 2));

    //vertical elements of collision
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

    //horizontal element of collision
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
                    xSpeed *= -1;
                }
            }
        }
    }
    sprite.setPosition(hitbox.getPosition());

    leftAnimation.advanceAnimation();
    rightAnimation.advanceAnimation();
    if (xSpeed<0) {
        sprite.setTextureRect(leftAnimation.getCurrentIntRect());
    } else {
        sprite.setTextureRect(rightAnimation.getCurrentIntRect());
    }
}

void Enemy::drawToScreen(sf::RenderWindow &window) {
    //window.draw(hitbox);
    window.draw(sprite);
}
