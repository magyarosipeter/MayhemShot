#pragma once

#include <SFML/Graphics.hpp>

#include "MoreInfo.h"
#include "State.h"
#include "Button.h"
#include "Title.h"

class MainMenuState : public State {
public:
	MainMenuState(StateMachine* stateMachine);

	virtual void update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked);
	virtual void draw(sf::RenderWindow& window);

private:
    sf::Sprite background;
    sf::Texture backgroundTexture;

    Title title;

	Button singleplayerButton;
	Button multiplayerButton;
	Button optionsButton;
    Button quitButton;
};

