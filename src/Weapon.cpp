#include "Weapon.h"

//////////////////////////////////
// GENERAL
//////////////////////////////////
Weapon::Weapon() {
    texture.loadFromFile(WEAPONS_TEXTURE);
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(50, 20));
    sprite.setScale(sf::Vector2f(0.75f, 0.75f));
}

int Weapon::getAmmo() {
    return ammo;
}
int Weapon::getMaxAmmo() {
    if (type=="Pistol") return 12;
    else if (type=="Shotgun") return 6;
    else if (type=="Rifle") return 25;
    else if (type=="Sniper") return 5;
    else return -1;
}
void Weapon::setAmmo(int value) {
    ammo = value;
}
unsigned Weapon::getCooldownFrames() {
    return cooldownFrames;
}
int Weapon::getDamage() {
    return damage;
}
void Weapon::drawToScreen(sf::RenderWindow &window) {
    window.draw(sprite);
}
void Weapon::setPosition(sf::Vector2f position) {
    sprite.setPosition(position);
}
std::string Weapon::getType() {
    return type;
}

void Weapon::shoot(std::vector<Projectile> &projectiles, float rotation) {
    for (int i=0 ; i<numberOfPellets ; i++) {
        Projectile newProjectile;
        int spreadValue = rand()%spread;
        rand()%2==1 ? spreadValue*=-1 : spreadValue*=1;

        newProjectile.initialize(-rotation+180+spreadValue, sprite.getPosition(), bulletSpeed, damage);
        projectiles.push_back(newProjectile);
    }
}

void Weapon::setRotation(float degrees) {
    if (degrees>0) {
        sprite.setRotation(90-degrees);
    }
    else {
        sprite.setRotation(270-degrees);
    }
    this->setTextureRect(degrees);
}

void Weapon::setTextureRect(float degrees) {
    // needed to flip the gun texture when looking backwards
    if (degrees<0.f ) {
        if (type=="Pistol") {
            sprite.setTextureRect(sf::IntRect(TEXTURE_WIDTH,0,-TEXTURE_WIDTH, TEXTURE_HEIGHT));
        }
        else if (type=="Shotgun") {
            sprite.setTextureRect(sf::IntRect(2*TEXTURE_WIDTH,0,-TEXTURE_WIDTH, TEXTURE_HEIGHT));
        }
        else if (type=="Rifle") {
            sprite.setTextureRect(sf::IntRect(3*TEXTURE_WIDTH,0,-TEXTURE_WIDTH, TEXTURE_HEIGHT));
        }
        else if (type=="Sniper") {
            sprite.setTextureRect(sf::IntRect(4*TEXTURE_WIDTH,0,-TEXTURE_WIDTH, TEXTURE_HEIGHT));
        }
    }
    else {
        if (type=="Pistol") {
            sprite.setTextureRect(sf::IntRect(0,0,TEXTURE_WIDTH, TEXTURE_HEIGHT));
        }
        else if (type=="Shotgun") {
            sprite.setTextureRect(sf::IntRect(1*TEXTURE_WIDTH,0,TEXTURE_WIDTH, TEXTURE_HEIGHT));
        }
        else if (type=="Rifle") {
            sprite.setTextureRect(sf::IntRect(2*TEXTURE_WIDTH,0,TEXTURE_WIDTH, TEXTURE_HEIGHT));
        }
        else if (type=="Sniper") {
            sprite.setTextureRect(sf::IntRect(3*TEXTURE_WIDTH,0,TEXTURE_WIDTH, TEXTURE_HEIGHT));
        }
    }
}

//////////////////////////////////
// SUBCLASSES
//////////////////////////////////
Pistol::Pistol() {
    type = "Pistol";
    cooldownFrames = 25;
    spread = 2;
    numberOfPellets = 1;
    bulletSpeed = 14;
    damage = 2;
    ammo = 12;

    sprite.setTextureRect(sf::IntRect(0,0,TEXTURE_WIDTH, TEXTURE_HEIGHT));
    sprite.setScale(sf::Vector2f(0.5f, 0.5f));
}

Shotgun::Shotgun() {
    type = "Shotgun";
    cooldownFrames = 40;
    spread = 12;
    numberOfPellets = 5;
    bulletSpeed = 10;
    damage = 1;
    ammo = 6;

    sprite.setTextureRect(sf::IntRect(1*TEXTURE_WIDTH,0,TEXTURE_WIDTH, TEXTURE_HEIGHT));
}

Rifle::Rifle() {
    type = "Rifle";
    cooldownFrames = 8;
    spread = 5;
    numberOfPellets = 1;
    bulletSpeed = 17;
    damage = 1;
    ammo = 25;

    sprite.setTextureRect(sf::IntRect(2*TEXTURE_WIDTH,0,TEXTURE_WIDTH, TEXTURE_HEIGHT));
}

Sniper::Sniper() {
    type = "Sniper";
    cooldownFrames = 70;
    spread = 1;
    numberOfPellets = 1;
    bulletSpeed = 45;
    damage = 10;
    ammo = 5;

    sprite.setTextureRect(sf::IntRect(3*TEXTURE_WIDTH,0,TEXTURE_WIDTH, TEXTURE_HEIGHT));
}
