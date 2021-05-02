#pragma once

#include "State.h"
#include "Button.h"
#include "Title.h"
#include "MusicPlayer.h"

class PauseMenuState : public State {
public:
    PauseMenuState(StateMachine* stateMachine, MusicPlayer* musicPlayer);

    virtual void update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked);
	virtual void draw(sf::RenderWindow& window);

	virtual void handleEvents(sf::Event &event) {};

private:
    Title title;

    Button resumeButton;
    Button optionsButton;
    Button backToMenuButton;

    sf::Font font;
    sf::Text warning;

    MusicPlayer* musicPlayer;
};
