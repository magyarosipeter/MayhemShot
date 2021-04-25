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

    weapon = new Pistol;
    weaponSoundBuffer.loadFromFile(PISTOL_SOUND);
    weaponSound.setBuffer(weaponSoundBuffer);

    jumpSoundBuffer.loadFromFile(JUMP_SOUND);
    jumpSound.setBuffer(jumpSoundBuffer);

    pickUpSoundBuffer.loadFromFile(GUN_PICKUP_SOUND);
    pickUpSound.setBuffer(pickUpSoundBuffer);
}

int Player::getDamage() {
    if (weapon!=NULL) {
        return weapon->getDamage();
    }
}
sf::FloatRect Player::globalBounds() {
    return hitbox.getGlobalBounds();
}
void Player::setWeapon(Weapon* newWeapon) {
    if ( weaponSound.getStatus() == sf::SoundSource::Playing) {
        finishingWeaponSoundBuffer = *weaponSound.getBuffer();
        finishingWeaponSound.setBuffer(finishingWeaponSoundBuffer);

        finishingWeaponSound.setPlayingOffset(weaponSound.getPlayingOffset());
        finishingWeaponSound.play();
    }

    this->weapon = newWeapon;
    if (this->weapon->getType()=="Pistol") {
        weaponSoundBuffer.loadFromFile(PISTOL_SOUND);
    } else if (this->weapon->getType()=="Shotgun") {
        weaponSoundBuffer.loadFromFile(SHOTGUN_SOUND);
    } else if (this->weapon->getType()=="Rifle") {
        weaponSoundBuffer.loadFromFile(RIFLE_SOUND);
    } else if (this->weapon->getType()=="Sniper") {
        weaponSoundBuffer.loadFromFile(SNIPER_SOUND);
    } else {
        weaponSoundBuffer.loadFromFile(PISTOL_SOUND);
    }
}

void Player::movement(Tile tileMap[MAP_HEIGHT][MAP_WIDTH], sf::RenderWindow &window) {
    ///////////////////////////////////////////////////////////////////////////
    // PLAYER MOVEMENT AND COLLISION WITH MAP
    ///////////////////////////////////////////////////////////////////////////

    //left and right movement input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        xSpeed = -SIDE_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        xSpeed = SIDE_SPEED;
    } else {
        xSpeed = 0;
    }

    //jumping input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !falling && jumpFrames>JUMP_COOLDOWN_FRAMES && ySpeed==0) {
        ySpeed = JUMP_SPEED;
        falling = true;
        jumpFrames = 0;
        jumpSound.play();
    }

    //add gravity
    if (ySpeed < MAX_GRAVITY) {
        ySpeed += GRAVITY;
    }

    jumpFrames++;

    ///////////////////////
    // No need to check the whole array of blocks for collisions, enough to check the ones surrounding the player
    // horizontal coordinates
    int kezdetX = std::max(0,(int) hitbox.getPosition().x/64-2);
    int hatarX = std::min(MAP_WIDTH,((int) hitbox.getPosition().x/64 + 2));

    //horizontal element of collisions
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

    // out of bounds fix
    if (hitbox.getPosition().y>SCREEN_HEIGHT*2) {
        hitbox.setPosition(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
        ySpeed = 0;
    } else if ( hitbox.getPosition().y-hitbox.getSize().y/2 < 0 ) {
        hitbox.setPosition(hitbox.getPosition().x, hitbox.getSize().y/2 );
        ySpeed = 0;
    }

    ///////////////////////////////////////////////////////////////////////////
    // CALCULATING ROTATION, RELATIVE TO MOUSE POSITION
    ///////////////////////////////////////////////////////////////////////////
    sf::Vector2i transformedMousePos;
    transformedMousePos.x = ( ((double)sf::Mouse::getPosition(window).x) / window.getSize().x * 100 ) * SCREEN_WIDTH / 100;
    transformedMousePos.y = ( ((double)sf::Mouse::getPosition(window).y) / window.getSize().y * 100 ) * SCREEN_HEIGHT / 100;

    sf::Vector2f distance;
    distance.x = transformedMousePos.x-hitbox.getPosition().x;
    distance.y = transformedMousePos.y-hitbox.getPosition().y;

    float radian = std::atan2(distance.x, distance.y);
    rotation = radian*180/PI;
    if (weapon!=NULL) {
        weapon->setRotation( rotation );
    }

    if (weapon!=NULL) {
        weapon->setPosition(sf::Vector2f(hitbox.getPosition().x, hitbox.getPosition().y-hitbox.getSize().y*10/100));
    }
}

void Player::shoot(std::vector<Projectile> &projectiles) {
    if ( weapon!=NULL ) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootFrames > weapon->getCooldownFrames() ) {
            weapon->shoot(projectiles, rotation);
            shootFrames = 0;
            weapon->setAmmo(weapon->getAmmo()-1);
            this->playGunSound();

            if (weapon->getAmmo()==0) {
                delete weapon;
                weapon = NULL;
                //weapon = new Pistol;
            }
        }
    }

    shootFrames++;
}

void Player::playGunSound() {
    weaponSound.play();
}

void Player::playPickupSound() {
    pickUpSound.play();
}

void Player::drawToScreen(sf::RenderWindow &window) {
    window.draw(hitbox);
    if(weapon!=NULL) {
        weapon->drawToScreen(window);
    }
}
