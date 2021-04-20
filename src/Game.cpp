#include "Game.h"

Game::Game() {
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "MayhemShot");
    window.setFramerateLimit(60);

    MainMenuState* mainMenuState = new MainMenuState(&gameState);

    gameState.pushState(mainMenuState);

    mouseClicked = false;
}

void Game::run() {
    while (window.isOpen() and gameState.topState()!=NULL) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                window.setSize( sf::Vector2u(window.getSize().x, (double)SCREEN_HEIGHT/SCREEN_WIDTH*window.getSize().x) );
            }
        }
        if ( !sf::Mouse::isButtonPressed(sf::Mouse::Left) ) mouseClicked = false;

        gameState.topState()->update(window, deltaTime, mouseClicked);

        if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) ) mouseClicked = true;

        window.clear(sf::Color::Black);
        gameState.topState()->draw(window);
        window.display();

        deltaTime = frameTimer.restart();
    }
}
