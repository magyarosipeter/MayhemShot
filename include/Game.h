#pragma once

#include <iostream>

#include "MoreInfo.h"
#include "StateMachine.h"
#include "MainMenuState.h"

class Game {
public:
    Game();

    void run();

private:
    sf::RenderWindow window;

    StateMachine gameState;

    sf::Time deltaTime;
    sf::Clock frameTimer;

    bool mouseClicked;
};
