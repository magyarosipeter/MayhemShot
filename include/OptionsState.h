#pragma once

#include <SFML/Graphics.hpp>

#include "MoreInfo.h"
#include "State.h"
#include "Button.h"

class OptionsState : public State {
public:
    OptionsState(StateMachine* stateMachine);

    virtual void update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked);
	virtual void draw(sf::RenderWindow& window);

private:
    sf::Sprite background;
    sf::Texture backgroundTexture;

    Button backButton;

    sf::Texture SFMLTexture;
    sf::Sprite SFMLSprite;
    sf::Texture heartTexture;
    sf::Sprite heartSprite;

    sf::Font font;
    sf::Text descriptionText;
    sf::Text creatorText;
};
