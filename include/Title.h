#pragma once

#include <SFML/Graphics.hpp>
#include <MoreInfo.h>
#include <math.h>
#include <iostream>

class Title {
public:
    void setAttributes(sf::Vector2f position, std::string textString, int characterSize, std::string fontFile, sf::Color color);

    void drawToScreen(sf::RenderWindow& window);

    void animation();

private:
    sf::Font font;
    sf::Text text;

    double maxRotation;
    int i;
    double sinValue;
};
