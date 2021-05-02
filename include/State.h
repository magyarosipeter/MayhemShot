#pragma once

#include <SFML/Graphics.hpp>

#include "StateMachine.h"

class StateMachine;

class State {
public:
	virtual void update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
    virtual void handleEvents(sf::Event &event) = 0;

	bool needEventHandling() {
        return this->eventHandling;
	}

protected:
    StateMachine* stateMachine;
    bool eventHandling=false;
};

