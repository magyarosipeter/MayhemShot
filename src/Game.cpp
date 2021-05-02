#include "Game.h"

Game::Game() {
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "MayhemShot");
    window.setFramerateLimit(60);

    windowIcon.loadFromFile(GAME_ICON_TEXTURE);
    window.setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());

    MainMenuState* mainMenuState = new MainMenuState(&gameState);

    gameState.pushState(mainMenuState);

    mouseClicked = false;

    focused = true;

    std::ifstream fin(OPTIONS_DATA);
    unsigned score, volume;
    fin >> volume >> score;
    volume = volume%101;
    fin.close();
    sf::Listener::setGlobalVolume(volume);
}

void Game::run() {

    while (window.isOpen() and gameState.topState()!=NULL) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                window.setSize( sf::Vector2u((double)SCREEN_WIDTH/SCREEN_HEIGHT*event.size.height, event.size.height) );
            }
            if (event.type == sf::Event::LostFocus) {
                focused = false;
            }
            if (event.type == sf::Event::GainedFocus) {
                focused = true;
            }
            if (gameState.topState()->needEventHandling()) gameState.topState()->handleEvents(event);
        }

        if (focused) {
            if ( !sf::Mouse::isButtonPressed(sf::Mouse::Left) ) mouseClicked = false;

            gameState.topState()->update(window, deltaTime, mouseClicked);

            if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) ) mouseClicked = true;

            window.clear(SKY_BLUE);
            gameState.topState()->draw(window);
            window.display();
        }
    }

}
