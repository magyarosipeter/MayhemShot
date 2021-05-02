#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>

#include "State.h"
#include "Button.h"
#include "Title.h"
#include "EndlessModeState.h"

class DeathMenuState: public State {
public:
    DeathMenuState(StateMachine* stateMachine, int score, MusicPlayer* musicPlayer);

    virtual void update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked);
	virtual void draw(sf::RenderWindow& window);

	virtual void handleEvents(sf::Event &event) {};

private:
    Title youDiedText;

    Button retryButton;
    Button backToMenuButton;

    sf::Font font;
    sf::Text score;

    bool highScoreVisible;
    Title newHighscoreText;

    MusicPlayer* musicPlayer;
};

