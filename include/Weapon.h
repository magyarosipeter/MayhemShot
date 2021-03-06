#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MoreInfo.h"
#include "Projectile.h"

#define TEXTURE_WIDTH 100
#define TEXTURE_HEIGHT 60

class Weapon {
public:
    Weapon();

    //main function to call
    void shoot(std::vector<Projectile> &projectiles, float rotation);

    //setters
    void setPosition(sf::Vector2f position);
    void setRotation(float degrees);
    void setTextureRect(float degrees);
    void setAmmo(int value);

    //getters
    int getAmmo();
    int getMaxAmmo();
    int getDamage();
    std::string getType();
    unsigned getCooldownFrames();

    //draw
    void drawToScreen(sf::RenderWindow &window);

protected:
    sf::Texture texture;
    sf::Sprite sprite;

    std::string type;                 //Identifying string
    unsigned cooldownFrames;          //Time you have to wait before shooting again
    unsigned numberOfPellets;         //Number of projectiles a single click produces
    int spread;                       //Random chance for a bullet to go this many degrees off of it's original axis
    int ammo;
    int damage;

    double bulletSpeed;
};

class Pistol: public Weapon {
public:
    Pistol();
};

class Shotgun: public Weapon {
public:
    Shotgun();
};

class Rifle: public Weapon {
public:
    Rifle();
};

class Sniper: public Weapon {
public:
    Sniper();
};
