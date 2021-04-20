#pragma once

#include <SFML/Graphics.hpp>
#include "MoreInfo.h"
#include "State.h"
#include "Player.h"

class EndlessModeState : public State {
public:
    EndlessModeState(StateMachine* stateMachine);

    virtual void update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked);
	virtual void draw(sf::RenderWindow& window);

private:
    Player player;
};
