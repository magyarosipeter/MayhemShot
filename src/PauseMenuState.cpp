#include "PauseMenuState.h"

PauseMenuState::PauseMenuState(StateMachine* stateMachine) {
    this->stateMachine = stateMachine;

    resumeButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH*50/100, SCREEN_HEIGHT*40/100),
        sf::Vector2f(410, 60),
        "Resume Game",
        75,
        TIMES_FONT,
        OPAQUE_GREY,
        OPAQUE_GREY,
        sf::Color::White,
        sf::Color::Magenta
    );

    backToMenuButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH*50/100, SCREEN_HEIGHT*60/100),
        sf::Vector2f(450, 60),
        "Return to Menu",
        75,
        TIMES_FONT,
        OPAQUE_GREY,
        OPAQUE_GREY,
        sf::Color::White,
        sf::Color::Magenta
    );
}

void PauseMenuState::update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked) {
    sf::Vector2i transformedMousePos;
    transformedMousePos.x = ( ((double)sf::Mouse::getPosition(window).x) / window.getSize().x * 100 ) * SCREEN_WIDTH / 100;
    transformedMousePos.y = ( ((double)sf::Mouse::getPosition(window).y) / window.getSize().y * 100 ) * SCREEN_HEIGHT / 100;

    if (resumeButton.update(transformedMousePos, mouseClicked)) {
        this->stateMachine->popState();
    }
    else if (backToMenuButton.update(transformedMousePos, mouseClicked)) {
        this->stateMachine->popState(2);
    }
}

void PauseMenuState::draw(sf::RenderWindow& window) {
    resumeButton.drawToScreen(window);
    backToMenuButton.drawToScreen(window);
}
