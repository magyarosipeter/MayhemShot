#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

#include "Entity.h"
#include "MoreInfo.h"
#include "Map.h"
#include "Weapon.h"
#include "Projectile.h"

#define JUMP_SPEED -40
#define SIDE_SPEED 11

#define JUMP_COOLDOWN_FRAMES 15

class Player : public Entity {
public:
    Player();

    virtual void movement(Tile tileMap[MAP_HEIGHT][MAP_WIDTH], sf::RenderWindow &window);
    virtual void drawToScreen(sf::RenderWindow &window);

    void shoot(std::vector<Projectile> &projectiles);
    void playGunSound();
    void playPickupSound();

    //getters
    int getDamage();
    int getAmmoCount();
    int getMaxAmmoCount();
    sf::FloatRect globalBounds();
    sf::Vector2f getPosition();

    //setters
    void setWeapon(Weapon* newWeapon);
    void setPosition(sf::Vector2f position);

private:
    Weapon* weapon;
    sf::SoundBuffer weaponSoundBuffer;
    sf::Sound weaponSound;
    sf::SoundBuffer finishingWeaponSoundBuffer;
    sf::Sound finishingWeaponSound;     //when you pick up a new weapon, the old one's sound has to end

    sf::SoundBuffer pickUpSoundBuffer;
    sf::Sound pickUpSound;

    bool falling;
    sf::SoundBuffer jumpSoundBuffer;
    sf::Sound jumpSound;

    int xSpeed, ySpeed;
    unsigned jumpFrames;         //counts the number of frames since the character last started jumped
    unsigned shootFrames;        //counts the number of frames since the character last shot
    float rotation;
};
