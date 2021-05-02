#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

#include "MoreInfo.h"

//Imported from previous, old project, pls don't look at code :))
class SlideBar {
public:
    SlideBar();

    void create(sf::Vector2f position, sf::Vector2f size, std::string descriptionName, double maximValue, double startingValue, std::string suffixText, std::string  fontFile);

    int getPercentage();
    void setPercentage(int percent);
    int getValue();

    //main function
    bool checkInput(sf::Vector2i transformedMousePos);

    void setPosition(sf::Vector2f position);

    void drawToScreen(sf::RenderWindow &window);

private:
    sf::RectangleShape boundary;            //For debugging purposes only
    sf::RectangleShape statusBar;           //The whole bar
    sf::RectangleShape statusMarker;        //Shows where the percentage is
    sf::RectangleShape filler;              //Fills the space before the statusMarker

    //value if slider is at 100%
    double maxValue;

    //used for locating the statusMarker
    int percentage;

    sf::Font font;
    sf::Text description;
    sf::Text valueText;
    std::string suffix;

};
