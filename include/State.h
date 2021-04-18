#pragma once

#include <SFML/Graphics.hpp>

class State {
public:
	virtual void update(sf::RenderWindow &window, sf::Time deltaTime) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
};

