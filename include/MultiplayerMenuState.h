#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "State.h"
#include "TextBox.h"
#include "Button.h"
#include "Title.h"
#include <iostream>
#include <string>

class MultiplayerMenuState: public State {

public:
    MultiplayerMenuState(StateMachine* stateMachine);

    virtual void update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked);
	virtual void draw(sf::RenderWindow& window);

	virtual void handleEvents(sf::Event &event);

	void getPacket();

private:
    std::string enteredIp;

    Title title;

    sf::Font font;
    sf::Text ipText;
    sf::Text portText;

    TextBox ipTextBox;
    TextBox portTextBox;

    Button connectButton;
    Button backButton;

    sf::TcpSocket socket;

    sf::Text statusMessage;

    sf::Thread* packetThread;
};
