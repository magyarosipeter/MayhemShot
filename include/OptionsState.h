#pragma once

#include <SFML/Graphics.hpp>

#include <fstream>

#include "MoreInfo.h"
#include "State.h"
#include "SlideBar.h"
#include "Button.h"
#include "Title.h"
#include "MusicPlayer.h"

class OptionsState : public State {
public:
    OptionsState(StateMachine* stateMachine);

    virtual void update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked);
	virtual void draw(sf::RenderWindow& window);

	virtual void handleEvents(sf::Event &event) {};

private:
    sf::Sprite background;
    sf::Texture backgroundTexture;

    Title title;

    Button backButton;

    //// Creator credits ////
    sf::Texture SFMLTexture;
    sf::Sprite SFMLSprite;
    sf::Texture heartTexture;
    sf::Sprite heartSprite;

    sf::Font font;
    sf::Text descriptionText;
    sf::Text creatorText;
    /////////////////////

    sf::Text highScoreText;
    sf::Text highScoreNumber;

    SlideBar volumeSlider;

    //options read from data file
    unsigned highScore;
    unsigned volume;
};
