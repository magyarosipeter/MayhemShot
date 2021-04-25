#pragma once

#include <SFML/Graphics.hpp>
#include "MoreInfo.h"
#include "State.h"
#include "Player.h"
#include "Map.h"
#include "Projectile.h"
#include "Enemy.h"
#include "WeaponCrate.h"

#define MIN_ENEMY_SPAWN_TIME 60
#define MAX_ENEMIES 7

class EndlessModeState : public State {
public:
    EndlessModeState(StateMachine* stateMachine);

    virtual void update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked);
	virtual void draw(sf::RenderWindow& window);

private:
    Map map;

    Player player;

    std::vector<Projectile> projectiles;

    std::vector<Enemy> enemies;
    sf::SoundBuffer enemyDieSoundBuffer;
    sf::Sound enemyDieSound;
    sf::SoundBuffer enrageSoundBuffer;
    sf::Sound enrageSound;

    WeaponCrate weaponCrate;

    sf::Font font;
    sf::Text playerScore;
    int playerKills;

    unsigned enemySpawnFrames;              // counts the frames since an enemy last spawned

    sf::Music music;

    //functions
    void killEnemies();
    void enemyOutOfBounds();
};
