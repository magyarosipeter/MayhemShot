#pragma once

#include <SFML/Graphics.hpp>
#include "MoreInfo.h"
#include <iostream>

class TextBox {
public:
    TextBox();

    //init
    void setAttributes(sf::Vector2f position, sf::Vector2f rectangleSize, int characterSize, std::string fontFile, unsigned maxCharacters);

    //main function to call
    bool update(sf::Vector2i mousePosition, bool &mouseClicked);
    bool isSelected();
    void setSelected(bool value);

    //getters
    std::string getText();
    std::string* getTextAdress();
    unsigned getMaxCharacters();
    sf::Vector2f getPosition();

    //setters
    void setText(std::string stringForText);

    void drawToScreen(sf::RenderWindow &window);

private:
    bool selected;

    std::string textString;

    sf::RectangleShape rectangle;
    sf::Font font;
    sf::Text text;

    unsigned maxCharacters;
};

