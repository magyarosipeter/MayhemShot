#include "MultiplayerMenuState.h"
#include "MultiplayerModeState.h"

MultiplayerMenuState::MultiplayerMenuState(StateMachine* stateMachine) {
    this->stateMachine = stateMachine;
    eventHandling = true;

    font.loadFromFile(TIMES_FONT);

    title.setAttributes(
        sf::Vector2f(SCREEN_WIDTH*20/100, SCREEN_HEIGHT*10/100),
        "Multiplayer",
        90,
        TIMES_FONT,
        ORANGE
    );

    connectButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH*80/100, SCREEN_HEIGHT*80/100),
        sf::Vector2f(200, 60),
        "Connect",
        75,
        TIMES_FONT,
        OPAQUE_GREY,
        OPAQUE_GREY,
        sf::Color::White,
        SALMON
    );

    ipTextBox.setAttributes(
        sf::Vector2f(SCREEN_WIDTH*10/100, SCREEN_HEIGHT*30/100),
        sf::Vector2f(400,60),
        50,
        TIMES_FONT,
        15
    );

    portTextBox.setAttributes(
        sf::Vector2f(SCREEN_WIDTH*10/100, SCREEN_HEIGHT*45/100),
        sf::Vector2f(200,60),
        50,
        TIMES_FONT,
        5
    );

    backButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH*10/100, SCREEN_HEIGHT*90/100),
		sf::Vector2f(120, 50),
		"Back",
		60,
		TIMES_FONT,
		OPAQUE_GREY,
		OPAQUE_GREY,
		sf::Color::White,
		SALMON
    );

    ipText.setString("IP Address");
    ipText.setCharacterSize(40);
    ipText.setFont(font);
    ipText.setPosition( sf::Vector2f(ipTextBox.getPosition().x, ipTextBox.getPosition().y-ipText.getGlobalBounds().height*1.75f ) );

    portText.setString("Port");
    portText.setCharacterSize(40);
    portText.setFont(font);
    portText.setPosition( sf::Vector2f(portTextBox.getPosition().x, portTextBox.getPosition().y-portText.getGlobalBounds().height*1.75f ) );

    statusMessage.setCharacterSize(30);
    statusMessage.setFont(font);
    statusMessage.setPosition( sf::Vector2f(SCREEN_WIDTH*10/100, SCREEN_HEIGHT*55/100) );
}

void MultiplayerMenuState::handleEvents(sf::Event &event) {
    std::string* stringToModify;
    unsigned maxCharacters;
    if ( ipTextBox.isSelected() ) {
        stringToModify = ipTextBox.getTextAdress();
        maxCharacters = ipTextBox.getMaxCharacters();
    } else if ( portTextBox.isSelected() ) {
        stringToModify = portTextBox.getTextAdress();
        maxCharacters = portTextBox.getMaxCharacters();
    }

    if (event.type == sf::Event::TextEntered) {
        if ((event.text.unicode>=48 && event.text.unicode<=57) || event.text.unicode==46) {
            if (stringToModify->size()<maxCharacters) {
                (*stringToModify) += static_cast<char>(event.text.unicode);
            }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::BackSpace) {
            if (stringToModify->size()!=0) stringToModify->resize(stringToModify->size()-1);
        }
    }
}

void MultiplayerMenuState::getPacket() {
    if (socket.getRemoteAddress()!=sf::IpAddress::None) {
        sf::Packet packet;
        socket.receive(packet);
        bool proceed;
        packet >> proceed;
        if (proceed) {
            MultiplayerModeState* multiplayerModeState = new MultiplayerModeState(this->stateMachine, socket);
            stateMachine->pushState(multiplayerModeState);
        }
    }
}

void MultiplayerMenuState::update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked) {
    sf::Vector2i transformedMousePos;
    transformedMousePos.x = ( ((double)sf::Mouse::getPosition(window).x) / window.getSize().x * 100 ) * SCREEN_WIDTH / 100;
    transformedMousePos.y = ( ((double)sf::Mouse::getPosition(window).y) / window.getSize().y * 100 ) * SCREEN_HEIGHT / 100;

    if (backButton.update(transformedMousePos, mouseClicked)) {
        socket.disconnect();
        stateMachine->popState();
    }

    if (ipTextBox.update(transformedMousePos, mouseClicked)) {
        portTextBox.setSelected(false);
    }
    if (portTextBox.update(transformedMousePos, mouseClicked)) {
        ipTextBox.setSelected(false);
    }

    if (connectButton.update(transformedMousePos, mouseClicked)) {
        sf::Socket::Status status = socket.connect(ipTextBox.getText(), atoi(portTextBox.getText().c_str()), MULTIPLAYER_TIMEOUT);
        if (status != sf::Socket::Done){
            statusMessage.setString( std::string("Could not make connection to " + ipTextBox.getText() + ":" + portTextBox.getText()) );
        } else {
            statusMessage.setString("Connected successfully to " + ipTextBox.getText() + ":" + portTextBox.getText() + " . Waiting for server host to start game.");
            socket.setBlocking(false);
        }
    }

    this->getPacket();
}

void MultiplayerMenuState::draw(sf::RenderWindow& window) {
    title.drawToScreen(window);

    connectButton.drawToScreen(window);

    window.draw(ipText);
    ipTextBox.drawToScreen(window);

    window.draw(portText);
    portTextBox.drawToScreen(window);

    backButton.drawToScreen(window);

    window.draw(statusMessage);
}
