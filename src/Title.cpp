#include "Title.h"

void Title::setAttributes(sf::Vector2f position, std::string textString, int characterSize, std::string fontFile, sf::Color color) {
    this->text.setFillColor(color);
    this->text.setCharacterSize(characterSize);
    this->text.setString(textString);

    font.loadFromFile(fontFile);
    this->text.setFont(this->font);

    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(position);

    maxRotation=6;
}

void Title::animation() {
    i++;
    if (i>360) i=0;

    sinValue = sin(i*PI/180);

    text.setRotation(sinValue*maxRotation);
}

void Title::drawToScreen(sf::RenderWindow& window) {
	window.draw(text);
}
