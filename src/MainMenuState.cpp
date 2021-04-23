#include "MainMenuState.h"
#include "OptionsState.h"
#include "EndlessModeState.h"
#include <iostream>

MainMenuState::MainMenuState(StateMachine* stateMachine) {
    this->stateMachine = stateMachine;

    backgroundTexture.loadFromFile(MENU_BACKGROUND_TEXTURE);
    background.setTexture(backgroundTexture);

    title.setAttributes(
        sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT*10/100),
        "MayhemShot",
        125,
        TIMES_FONT,
        ORANGE
    );

	singleplayerButton.setAttributes(
		sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT*40/100),
		sf::Vector2f(350, 60),
		"Singleplayer",
		70,
		TIMES_FONT,
		OPAQUE_GREY,
		OPAQUE_GREY,
		sf::Color::White,
		sf::Color::Magenta
	);

    multiplayerButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT*55/100),
		sf::Vector2f(330, 60),
		"Multiplayer",
		70,
		TIMES_FONT,
		OPAQUE_GREY,
		OPAQUE_GREY,
		GREY,
		sf::Color(127,127,127)
    );

    optionsButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT*70/100),
		sf::Vector2f(230, 60),
		"Options",
		70,
		TIMES_FONT,
		OPAQUE_GREY,
		OPAQUE_GREY,
		sf::Color::White,
		sf::Color::Magenta
    );

    quitButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT*85/100),
		sf::Vector2f(150, 60),
		"Quit",
		70,
		TIMES_FONT,
		OPAQUE_GREY,
		OPAQUE_GREY,
		sf::Color::White,
		sf::Color::Magenta
    );
}

void MainMenuState::update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked){
    sf::Vector2i transformedMousePos;
    transformedMousePos.x = ( ((double)sf::Mouse::getPosition(window).x) / window.getSize().x * 100 ) * SCREEN_WIDTH / 100;
    transformedMousePos.y = ( ((double)sf::Mouse::getPosition(window).y) / window.getSize().y * 100 ) * SCREEN_HEIGHT / 100;

    title.animation();

    if (singleplayerButton.update(transformedMousePos, mouseClicked)) {
        EndlessModeState* endlessModeState = new EndlessModeState(this->stateMachine);
        this->stateMachine->pushState(endlessModeState);
    }
    if (optionsButton.update(transformedMousePos, mouseClicked))  {
        OptionsState* optionsState = new OptionsState(this->stateMachine);
        this->stateMachine->pushState(optionsState);
    }
    if(quitButton.update(transformedMousePos, mouseClicked)) {
        window.close();
    }
}

void MainMenuState::draw(sf::RenderWindow& window) {
    window.draw(background);

    title.drawToScreen(window);

	singleplayerButton.drawToScreen(window);
	multiplayerButton.drawToScreen(window);
	optionsButton.drawToScreen(window);
    quitButton.drawToScreen(window);
}
