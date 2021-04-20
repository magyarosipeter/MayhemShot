#include "Player.h"

Player::Player() {
    hitbox.setSize(sf::Vector2f(64,64));
    hitbox.setOrigin(sf::Vector2f(hitbox.getSize().x/2, hitbox.getSize().y/2));
    hitbox.setPosition(sf::Vector2f(0+hitbox.getSize().x/2, SCREEN_HEIGHT-hitbox.getSize().y/2));
    hitbox.setFillColor(sf::Color::Blue);

    xSpeed = 0;
    ySpeed = 0;
    falling = false;
}

void Player::movement() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        xSpeed = -SIDE_SPEED;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        xSpeed = SIDE_SPEED;
    } else {
        xSpeed = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !falling) {
        ySpeed = JUMP_SPEED;
        falling = true;
    }

    if ( hitbox.getPosition().y < SCREEN_HEIGHT-hitbox.getSize().y/2 ) {
        ySpeed += GRAVITY;
    } else {
        ySpeed = 0;
        hitbox.setPosition(sf::Vector2f(hitbox.getPosition().x, SCREEN_HEIGHT-hitbox.getSize().y/2-1));
        falling = false;
    }

    hitbox.move(sf::Vector2f(xSpeed, ySpeed));

    std::cout << ySpeed << std::endl;
}

void Player::drawToScreen(sf::RenderWindow &window) {
    window.draw(hitbox);
}
