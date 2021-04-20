#include "OptionsState.h"

OptionsState::OptionsState(StateMachine* stateMachine) {
    this->stateMachine = stateMachine;

    backgroundTexture.loadFromFile(OPTIONS_BACKGROUND_TEXTURE);
    background.setTexture(backgroundTexture);
    background.setColor(sf::Color(255,255,255,120));

    backButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH*10/100, SCREEN_HEIGHT*90/100),
		sf::Vector2f(120, 50),
		"Back",
		60,
		TIMES_FONT,
		OPAQUE_GREY,
		OPAQUE_GREY,
		sf::Color::White,
		sf::Color::Magenta
    );
}

void OptionsState::update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked) {
    sf::Vector2i transformedMousePos;
    transformedMousePos.x = ( ((double)sf::Mouse::getPosition(window).x) / window.getSize().x * 100 ) * SCREEN_WIDTH / 100;
    transformedMousePos.y = ( ((double)sf::Mouse::getPosition(window).y) / window.getSize().y * 100 ) * SCREEN_HEIGHT / 100;

    if(backButton.update(transformedMousePos, mouseClicked)) {
        stateMachine->popState();
    }
}

void OptionsState::draw(sf::RenderWindow& window) {
    window.draw(background);

	backButton.drawToScreen(window);
}
