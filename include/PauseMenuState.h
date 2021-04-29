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

private:
    Title title;

    Button resumeButton;
    Button optionsButton;
    Button backToMenuButton;

    MusicPlayer* musicPlayer;
};
