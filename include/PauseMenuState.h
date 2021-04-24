#pragma once

#include "State.h"
#include "Button.h"

class PauseMenuState : public State {
public:
    PauseMenuState(StateMachine* stateMachine);

    virtual void update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked);
	virtual void draw(sf::RenderWindow& window);

private:
    Button resumeButton;
    Button optionsButton;
    Button backToMenuButton;
};
