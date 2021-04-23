#include "EndlessModeState.h"
#include "PauseMenuState.h"

EndlessModeState::EndlessModeState(StateMachine* stateMachine) {
    this->stateMachine = stateMachine;

    map.loadMap(GROUND_TILES_TEXTURE);
}

void EndlessModeState::update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked){
    sf::Vector2i transformedMousePos;
    transformedMousePos.x = ( ((double)sf::Mouse::getPosition(window).x) / window.getSize().x * 100 ) * SCREEN_WIDTH / 100;
    transformedMousePos.y = ( ((double)sf::Mouse::getPosition(window).y) / window.getSize().y * 100 ) * SCREEN_HEIGHT / 100;

    player.movement(map.tileMap);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        PauseMenuState* pauseMenuState = new PauseMenuState(this->stateMachine);
        this->stateMachine->pushState(pauseMenuState);
    }
}

void EndlessModeState::draw(sf::RenderWindow& window) {
    map.drawToScreen(window);

    player.drawToScreen(window);
}
