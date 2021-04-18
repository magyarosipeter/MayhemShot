#include "Button.h"
#include <iostream>

void Button::setAttributes(sf::Vector2f position, sf::Vector2f size, std::string stringText, unsigned int characterSize, std::string fontFile, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, sf::Color textColor, sf::Color textHoverColor, sf::Color textActiveColor) {
	rectangle.setSize(size);
	rectangle.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	rectangle.setPosition(position);

	this->font.loadFromFile(fontFile);
	this->text.setFont(font);

	this->text.setString(stringText);

	this->idleSize = characterSize;
    this->hoverSize = characterSize*115/100;

	this->text.setCharacterSize(characterSize);
	this->text.setFillColor(textColor);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
	this->text.setPosition(rectangle.getPosition());

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->textColor = textColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;

	buttonState = BTN_IDLE;
}

bool Button::update(sf::Vector2i mousePosition) {
	if ( rectangle.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y) ) ) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonState = BTN_ACTIVE;
		}
		else {
			buttonState = BTN_HOVER;
		}
	}
	else {
		buttonState = BTN_IDLE;
	}

	if (buttonState == BTN_ACTIVE) {
        this->text.setFillColor(textActiveColor);
        this->rectangle.setFillColor(activeColor);
        this->text.setCharacterSize(hoverSize);
	}
	else if (buttonState == BTN_HOVER) {
        this->text.setFillColor(textHoverColor);
        this->rectangle.setFillColor(hoverColor);
        this->text.setCharacterSize(hoverSize);
	}
	else if (buttonState == BTN_IDLE) {
		this->text.setFillColor(textColor);
		this->rectangle.setFillColor(idleColor);
		this->text.setCharacterSize(idleSize);
	}

	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(rectangle.getPosition());

    if (buttonState==BTN_ACTIVE) {
        return true;
    }
    else return false;
}

void Button::drawToScreen(sf::RenderWindow& window) {
	window.draw(rectangle);
	window.draw(text);
}
