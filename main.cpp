#include <SFML/Graphics.hpp>

#include <iostream>

#include "MoreInfo.h"
#include "StateMachine.h"
#include "MainMenuState.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "My window");

    window.setFramerateLimit(10);

    MainMenuState* mainMenuState = new MainMenuState;

    StateMachine gameState(mainMenuState);

    sf::Time deltaTime;
    sf::Clock frameTimer;

    while (window.isOpen() and gameState.topState()!=NULL) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        gameState.topState()->update(window, deltaTime);

        sf::Vector2f transformedMousePos;
        transformedMousePos.x = ( ((double)sf::Mouse::getPosition(window).x) / window.getSize().x * 100 ) * SCREEN_WIDTH / 100;
        transformedMousePos.y = ( ((double)sf::Mouse::getPosition(window).y) / window.getSize().y * 100 ) * SCREEN_HEIGHT / 100;
        std::cout << transformedMousePos.x << " " << transformedMousePos.y << std::endl;

        window.clear(sf::Color::Black);
        gameState.topState()->draw(window);
        window.display();

        deltaTime = frameTimer.restart();
    }

    return 0;
}
