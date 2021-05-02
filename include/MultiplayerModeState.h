#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "State.h"
#include "StateMachine.h"
#include "Map.h"
#include "Player.h"
#include <iostream>

class MultiplayerModeState : public State {
public:
    MultiplayerModeState(StateMachine* stateMachine, sf::TcpSocket &socket);

    virtual void update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked);
	virtual void draw(sf::RenderWindow& window);

	virtual void handleEvents(sf::Event &event) {};

private:
    Map map;

    Player player;
    sf::RectangleShape enemy;
    sf::Vector2f enemyPosition;

    sf::TcpSocket* socket;
};
