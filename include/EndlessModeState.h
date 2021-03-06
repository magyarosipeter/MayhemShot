#pragma once

#include <SFML/Graphics.hpp>
#include "MoreInfo.h"
#include "State.h"
#include "Player.h"
#include "Map.h"
#include "Projectile.h"
#include "Enemy.h"
#include "WeaponCrate.h"
#include "MusicPlayer.h"
#include "PauseMenuState.h"
#include "DeathMenuState.h"

#define MIN_ENEMY_SPAWN_TIME 60
#define MAX_ENEMIES 7

class EndlessModeState : public State {
public:
    EndlessModeState(StateMachine* stateMachine);

    virtual void update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked);
	virtual void draw(sf::RenderWindow& window);

	virtual void handleEvents(sf::Event &event) {};

private:
    sf::Texture backgroundTexture;
    sf::Sprite background;

    Map map;

    Player player;

    std::vector<Projectile> projectiles;

    std::vector<Enemy> enemies;

    WeaponCrate weaponCrate;

    sf::SoundBuffer enemyDieSoundBuffer;
    sf::Sound enemyDieSound;
    sf::SoundBuffer enrageSoundBuffer;
    sf::Sound enrageSound;
    sf::SoundBuffer loseSoundBuffer;
    sf::Sound loseSound;

    sf::Texture enemy1Texture;
    sf::Texture enemy2Texture;

    ////// HUD elements //////
    sf::Font font;
    sf::Text playerScore;
    sf::Text ammoCount;
    int playerKills;
    /////////////////////////

    // counts the frames since an enemy last spawned
    unsigned enemySpawnFrames;

    sf::Texture fireTexture;
    Animation fireAnimation;
    sf::Sprite fireLeft;
    sf::Sprite fireRight;

    MusicPlayer musicPlayer;

    //functions
    void killEnemies();
    void enemyOutOfBounds();
    void playerOutOfBounds();
    void enemyPlayerCollision();
    void deleteProjectiles();
    void reset();
};
