#include "MultiplayerModeState.h"

MultiplayerModeState::MultiplayerModeState(StateMachine* stateMachine, sf::TcpSocket &socket) {
    this->stateMachine = stateMachine;

    this->socket = &socket;

    map.loadMap(GROUND_TILES_TEXTURE, MP_MAP1);

    enemy.setFillColor(sf::Color::Red);
    enemy.setSize(sf::Vector2f(40, 60));
    enemy.setOrigin(sf::Vector2f(20,30));
}

void MultiplayerModeState::update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked) {
    sf::Packet packetReceive;
    socket->receive(packetReceive);
    packetReceive >> enemyPosition.x >> enemyPosition.y;
    std::cout << enemyPosition.x << " " << enemyPosition.y << std::endl;

    enemy.setPosition(enemyPosition);

    player.movement(map.tileMap, window);

    sf::Packet packetSend;
    sf::Vector2f position = player.getPosition();
    packetSend << position.x << position.y;
    socket->send(packetSend);
}

void MultiplayerModeState::draw(sf::RenderWindow& window) {
    map.drawToScreen(window);

    window.draw(enemy);

    player.drawToScreen(window);
}
