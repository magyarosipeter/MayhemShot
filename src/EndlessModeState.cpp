#include "EndlessModeState.h"

EndlessModeState::EndlessModeState(StateMachine* stateMachine) {
    this->stateMachine = stateMachine;
}

void EndlessModeState::update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked){
    sf::Vector2i transformedMousePos;
    transformedMousePos.x = ( ((double)sf::Mouse::getPosition(window).x) / window.getSize().x * 100 ) * SCREEN_WIDTH / 100;
    transformedMousePos.y = ( ((double)sf::Mouse::getPosition(window).y) / window.getSize().y * 100 ) * SCREEN_HEIGHT / 100;

    player.movement();
}

void EndlessModeState::draw(sf::RenderWindow& window) {
    player.drawToScreen(window);
}
