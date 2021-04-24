#include "Game.h"

Game::Game() {
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "MayhemShot");
    window.setFramerateLimit(60);

    MainMenuState* mainMenuState = new MainMenuState(&gameState);

    gameState.pushState(mainMenuState);

    mouseClicked = false;
}

void Game::run() {
    frameTimer.restart();
    while (window.isOpen() and gameState.topState()!=NULL) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                window.setSize( sf::Vector2u((double)SCREEN_WIDTH/SCREEN_HEIGHT*event.size.height, event.size.height) );
            }
        }
        if ( !sf::Mouse::isButtonPressed(sf::Mouse::Left) ) mouseClicked = false;

        gameState.topState()->update(window, deltaTime, mouseClicked);

        if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) ) mouseClicked = true;

        window.clear(SKY_BLUE);
        gameState.topState()->draw(window);
        window.display();

        deltaTime = frameTimer.restart();
        std::cout << deltaTime.asMilliseconds() << std::endl;
    }
}
