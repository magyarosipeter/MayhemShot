#pragma once

#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation();
    sf::IntRect getCurrentIntRect();
    void advanceAnimation();
    void addIntRect(sf::IntRect newIntRect);

private:
    std::vector<sf::IntRect> frames;
    int index;
    int currentFrameValue;
    int switchFrameValue;
};

