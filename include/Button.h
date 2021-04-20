#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "MoreInfo.h"

enum ButtonStates { BTN_IDLE=0, BTN_HOVER=1, BTN_ACTIVE=2 };

class Button {
public:
	void setAttributes(sf::Vector2f position, sf::Vector2f size, std::string stringText, unsigned int characterSize, std::string fontFile,
		sf::Color idleColor, sf::Color hoverColor, sf::Color textColor, sf::Color textHoverColor);

	bool update(sf::Vector2i mousePosition, bool &mouseClicked);

	void drawToScreen(sf::RenderWindow& window);

private:
	short unsigned buttonState;

	sf::RectangleShape rectangle;
	sf::Font font;
	sf::Text text;

	unsigned idleSize, hoverSize;

	sf::Color idleColor, hoverColor, textColor, textHoverColor;
};

