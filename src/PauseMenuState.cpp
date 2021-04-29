#include "PauseMenuState.h"
#include "OptionsState.h"

PauseMenuState::PauseMenuState(StateMachine* stateMachine, MusicPlayer* musicPlayer) {
    this->stateMachine = stateMachine;
    this->musicPlayer = musicPlayer;

    resumeButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH*50/100, SCREEN_HEIGHT*35/100),
        sf::Vector2f(240, 60),
        "Resume",
        75,
        TIMES_FONT,
        OPAQUE_GREY,
        OPAQUE_GREY,
        sf::Color::White,
        SALMON
    );

    optionsButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT*50/100),
		sf::Vector2f(250, 60),
		"Options",
		75,
		TIMES_FONT,
		OPAQUE_GREY,
		OPAQUE_GREY,
		sf::Color::White,
		SALMON
    );

    backToMenuButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH*50/100, SCREEN_HEIGHT*65/100),
        sf::Vector2f(450, 60),
        "Return to Menu",
        75,
        TIMES_FONT,
        OPAQUE_GREY,
        OPAQUE_GREY,
        sf::Color::White,
        SALMON
    );

    title.setAttributes(
        sf::Vector2f(SCREEN_WIDTH*50/100, SCREEN_HEIGHT*10/100),
        "PAUSED",
        120,
        TIMES_FONT,
        ORANGE
    );
}

void PauseMenuState::update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked) {
    sf::Vector2i transformedMousePos;
    transformedMousePos.x = ( ((double)sf::Mouse::getPosition(window).x) / window.getSize().x * 100 ) * SCREEN_WIDTH / 100;
    transformedMousePos.y = ( ((double)sf::Mouse::getPosition(window).y) / window.getSize().y * 100 ) * SCREEN_HEIGHT / 100;

    if (resumeButton.update(transformedMousePos, mouseClicked)) {
        this->stateMachine->popState();
    }
    else if (optionsButton.update(transformedMousePos, mouseClicked))  {
        OptionsState* optionsState = new OptionsState(this->stateMachine);
        this->stateMachine->pushState(optionsState);
    }
    else if (backToMenuButton.update(transformedMousePos, mouseClicked)) {
        musicPlayer->stop();
        this->stateMachine->popState(2);
    }
}

void PauseMenuState::draw(sf::RenderWindow& window) {
    title.drawToScreen(window);

    resumeButton.drawToScreen(window);
    optionsButton.drawToScreen(window);
    backToMenuButton.drawToScreen(window);
}
