#include "Projectile.h"

Projectile::Projectile() {
    hitbox.setRadius(10);
    hitbox.setOrigin(sf::Vector2f(hitbox.getRadius()/2, hitbox.getRadius()/2));
    hitbox.setFillColor(sf::Color::Yellow);
}

void Projectile::movement() {
    hitbox.move(velocity);
}

void Projectile::initialize(double angle, sf::Vector2f startingPos, int bulletSpeed, int bulletDamage) {
    angle = 360 - angle;

    hitbox.setPosition(startingPos);

    double radian = angle*PI/180;

    velocity.x = sin(radian)*bulletSpeed;
    velocity.y = cos(radian)*bulletSpeed;

    velocity.x *= -1;
    velocity.y *= -1;

    damage = bulletDamage;
}

//getters
int Projectile::getDamage() {
    return damage;
}
sf::Vector2f Projectile::getPosition() {
    return hitbox.getPosition();
}
int Projectile::getHitboxRadius() {
    return hitbox.getRadius();
}
sf::FloatRect Projectile::globalBounds() {
    return hitbox.getGlobalBounds();
}

void Projectile::drawToScreen(sf::RenderWindow &window) {
    window.draw(hitbox);
}
