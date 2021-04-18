#pragma once

#include <SFML/Graphics.hpp>

#include "MoreInfo.h"
#include "State.h"
#include "Button.h"

class MainMenuState : public State {
public:
	MainMenuState();

	virtual void update(sf::RenderWindow &window, sf::Time deltaTime);
	virtual void draw(sf::RenderWindow& window);

private:
	Button singleplayerButton;
	Button multiplayerButton;
	Button optionsButton;
    Button quitButton;
};

