#include "MainMenuState.h"
#include <iostream>

MainMenuState::MainMenuState() {
	singleplayerButton.setAttributes(
		sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT*40/100),
		sf::Vector2f(250, 50),
		"Singleplayer",
		60,
		TIMES_FONT,
		sf::Color::Blue,
		sf::Color::Cyan,
		sf::Color::Green,
		sf::Color::White,
		sf::Color::Magenta,
		sf::Color::Yellow
	);

    multiplayerButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT*55/100),
		sf::Vector2f(250, 50),
		"Multiplayer",
		60,
		TIMES_FONT,
		sf::Color(127,127,127),
		sf::Color(127,127,127),
		sf::Color(127,127,127),
		sf::Color(127,127,127),
		sf::Color(127,127,127),
		sf::Color(127,127,127)
    );

    optionsButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT*70/100),
		sf::Vector2f(250, 50),
		"Options",
		60,
		TIMES_FONT,
		sf::Color::Blue,
		sf::Color::Cyan,
		sf::Color::Green,
		sf::Color::White,
		sf::Color::Magenta,
		sf::Color::Yellow
    );

    quitButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT*85/100),
		sf::Vector2f(250, 50),
		"Quit",
		60,
		TIMES_FONT,
		sf::Color::Blue,
		sf::Color::Cyan,
		sf::Color::Green,
		sf::Color::White,
		sf::Color::Magenta,
		sf::Color::Yellow
    );
}

void MainMenuState::update(sf::RenderWindow &window, sf::Time deltaTime) {
    sf::Vector2i transformedMousePos;
    transformedMousePos.x = ( ((double)sf::Mouse::getPosition(window).x) / window.getSize().x * 100 ) * SCREEN_WIDTH / 100;
    transformedMousePos.y = ( ((double)sf::Mouse::getPosition(window).y) / window.getSize().y * 100 ) * SCREEN_HEIGHT / 100;

    if (singleplayerButton.update(transformedMousePos)) {
        std::cout <<"Singleplayer initiated";
    }
    if (optionsButton.update(transformedMousePos))  {
        std::cout <<"Singleplayer initiated";
    }
    if(quitButton.update(transformedMousePos)) {

    }
}

void MainMenuState::draw(sf::RenderWindow& window) {
	singleplayerButton.drawToScreen(window);
	multiplayerButton.drawToScreen(window);
	optionsButton.drawToScreen(window);
    quitButton.drawToScreen(window);
}
