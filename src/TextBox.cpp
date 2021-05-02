#include "TextBox.h"

TextBox::TextBox() {
    selected = false;
}

bool TextBox::isSelected() {
    return selected;
}
void TextBox::setSelected(bool value) {
    selected = value;
}

void TextBox::setAttributes(sf::Vector2f position, sf::Vector2f rectangleSize, int characterSize, std::string fontFile, unsigned maxCharacters) {
    font.loadFromFile(fontFile);
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setPosition(position);

    rectangle.setSize(rectangleSize);
    rectangle.setPosition(position);
    rectangle.setFillColor(OPAQUE_GREY);

    textString = "";

    this->maxCharacters = maxCharacters;
}

void TextBox::setText(std::string stringForText) {
    this->textString = stringForText;
    text.setString(textString);
}
std::string TextBox::getText() {
    return textString;
}
std::string* TextBox::getTextAdress() {
    return &textString;
}
unsigned TextBox::getMaxCharacters() {
    return maxCharacters;
}
sf::Vector2f TextBox::getPosition() {
    return rectangle.getPosition();
}

bool TextBox::update(sf::Vector2i mousePosition, bool &mouseClicked) {
    text.setString(textString);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseClicked) {
        if ( rectangle.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y) ) ) {
			selected = true;
			mouseClicked = true;
			return true;
		}
		else {
            selected = false;
            return false;
		}
    }
    return false;
}

void TextBox::drawToScreen(sf::RenderWindow &window) {
    window.draw(rectangle);
    window.draw(text);
}
