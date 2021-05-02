#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "MoreInfo.h"
#include "StateMachine.h"
#include "MainMenuState.h"

class Game {
public:
    Game();

    void run();

private:
    sf::RenderWindow window;
    sf::Image windowIcon;

    StateMachine gameState;

    sf::Time deltaTime;
    sf::Clock frameTimer;

    bool focused;

    bool mouseClicked;
};
