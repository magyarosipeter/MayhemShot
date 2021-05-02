#include "EndlessModeState.h"
#include <sstream>

std::string intToString(int n) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}

EndlessModeState::EndlessModeState(StateMachine* stateMachine) {
    this->stateMachine = stateMachine;

    map.loadMap(GROUND_TILES_TEXTURE, SP_MAP1);
    weaponCrate.setRandomPosition(map.tileMap);

    //spawning an enemy is possible straight away when starting the game
    enemySpawnFrames = MIN_ENEMY_SPAWN_TIME;

    enemyDieSoundBuffer.loadFromFile(ENEMY_DIE_SOUND);
    enemyDieSound.setBuffer(enemyDieSoundBuffer);

    enrageSoundBuffer.loadFromFile(ENEMY_ENRAGE_SOUND);
    enrageSound.setBuffer(enrageSoundBuffer);

    loseSoundBuffer.loadFromFile(LOSE_GAME_SOUND);
    loseSound.setBuffer(loseSoundBuffer);

    enemy1Texture.loadFromFile(ENEMY_1_TEXTURE);
    enemy2Texture.loadFromFile(ENEMY_2_TEXTURE);

    font.loadFromFile(TIMES_FONT);
    playerKills = 0;
    playerScore.setFont(font);
    playerScore.setCharacterSize(40);
    playerScore.setString("Score: 0");
    ammoCount.setFont(font);
    ammoCount.setCharacterSize(40);
    ammoCount.setString("Ammo: 12/12");
    ammoCount.setPosition(sf::Vector2f(SCREEN_WIDTH-ammoCount.getGlobalBounds().width*1.1, SCREEN_HEIGHT-ammoCount.getGlobalBounds().height*1.5));

    backgroundTexture.loadFromFile(GAME_BACKGROUND_TEXTURE);
    background.setTexture(backgroundTexture);

    fireTexture.loadFromFile(FIRE_TEXTURE);
    for (int i=0 ; i<8 ; i++) {
        fireAnimation.addIntRect(sf::IntRect(i*MAP_TILE_SIZE, 0, MAP_TILE_SIZE, MAP_TILE_SIZE));
    }
    fireAnimation.setSwitchFrameValue(6);

    fireLeft.setTexture(fireTexture);
    fireLeft.setTextureRect(fireAnimation.getCurrentIntRect());
    fireLeft.setOrigin(MAP_TILE_SIZE/2, MAP_TILE_SIZE/2);
    fireLeft.setPosition(sf::Vector2f(9*MAP_TILE_SIZE+MAP_TILE_SIZE/2, MAP_HEIGHT*MAP_TILE_SIZE-MAP_TILE_SIZE/2));

    fireRight.setTexture(fireTexture);
    fireRight.setTextureRect(fireAnimation.getCurrentIntRect());
    fireRight.setOrigin(MAP_TILE_SIZE/2, MAP_TILE_SIZE/2);
    fireRight.setPosition(sf::Vector2f(10*MAP_TILE_SIZE+MAP_TILE_SIZE/2, MAP_HEIGHT*MAP_TILE_SIZE-MAP_TILE_SIZE/2));
}

void EndlessModeState::deleteProjectiles() {
    unsigned i=0;
    while ( i<projectiles.size() ) {

        bool deleted=false;

        //calculate the projectile position in the Tile Map
        sf::Vector2i index;
        index.x = (int) projectiles[i].getPosition().x/MAP_TILE_SIZE;
        index.y = (int) projectiles[i].getPosition().y/MAP_TILE_SIZE;

        // out of bounds delete
        if ( index.x < 0 || index.y<0 || index.x>=MAP_WIDTH || index.y >=MAP_HEIGHT) {
            projectiles.erase(projectiles.begin()+i);
            deleted = true;
        }
        // collision with solid blocks delete
        else {
            for (int j=0; j<MAP_HEIGHT && !deleted ; j++) {
                for (int k=0 ; k<MAP_WIDTH && !deleted ; k++) {
                    if (map.tileMap[j][k].isSolid() && projectiles[i].hitbox.getGlobalBounds().intersects(map.tileMap[j][k].hitbox.getGlobalBounds())) {
                        projectiles.erase(projectiles.begin()+i);
                        deleted = true;
                    }
                }
            }
        }
        if (!deleted) {
            i++;
        }
    }
}

void EndlessModeState::killEnemies() {
    int i=0;
    while (i<projectiles.size()) {
        bool collided = false;
        int j=0;
        while (j<enemies.size() && !collided) {
            //projectile number "i" collided with enemy number "j"
            if (projectiles[i].globalBounds().intersects(enemies[j].globalBounds())) {

                enemies[j].setHealth(enemies[j].getHealth() - projectiles[i].getDamage());

                if (enemies[j].getHealth()<=0) {
                    enemies.erase(enemies.begin()+j);
                    this->enemyDieSound.play();
                    playerKills++;
                    playerScore.setString(std::string("Score: "+intToString(playerKills)));
                }
                collided = true;
            }
            // else we continue iterating through the enemies
            else {
                j++;
            }
        }
        if (!collided) {
            i++;
        } else {
            projectiles.erase(projectiles.begin()+i);
        }
    }
}

void EndlessModeState::enemyOutOfBounds() {
    unsigned i=0;
    while ( i<enemies.size() ) {
        if (enemies[i].getPosition().y>SCREEN_HEIGHT*110/100) {
            enemies[i].setAngry();
            enrageSound.play();
        }
        i++;
    }
}

void EndlessModeState::playerOutOfBounds() {
    if (player.getPosition().y > SCREEN_HEIGHT+player.globalBounds().height/2) {
        loseSound.play();
        DeathMenuState* deathMenuState = new DeathMenuState(this->stateMachine, playerKills, &musicPlayer);
        this->reset();
        this->stateMachine->pushState(deathMenuState);
    }
}

void EndlessModeState::reset() {
    projectiles.clear();
    enemies.clear();
    Weapon* starterWeapon = new Pistol;
    player.setWeapon(starterWeapon);
    player.setPosition(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
    playerScore.setString("Score: 0");
    playerKills = 0;
}

void EndlessModeState::enemyPlayerCollision() {
    for (int i=0 ; i<enemies.size() ; i++) {
        if (enemies[i].globalBounds().intersects(player.globalBounds())) {
            loseSound.play();
            DeathMenuState* deathMenuState = new DeathMenuState(this->stateMachine, playerKills, &musicPlayer);
            this->reset();
            this->stateMachine->pushState(deathMenuState);
            break;
        }
    }
}

void EndlessModeState::update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked) {
    //WASD input, movement and collision
    player.movement(map.tileMap, window);

    //mouse input, shooting
    player.shoot(projectiles);

    //move projectiles
    for (unsigned i=0 ; i<projectiles.size() ; i++) projectiles[i].movement();

    //move enemies
    for (unsigned i=0 ; i<enemies.size() ; i++) enemies[i].movement(map.tileMap, window);
    //deal with enemies falling out of the map
    this->enemyOutOfBounds();

    //kill enemy and delete projectile that collide with them
    this->killEnemies();

    //delete projectiles that collide with solid blocks
    this->deleteProjectiles();

    //player picks up crate for random weapon
    if (player.globalBounds().intersects(weaponCrate.globalBounds())) {
        player.setWeapon(weaponCrate.rollWeapon());
        weaponCrate.setRandomPosition(map.tileMap);
        player.playPickupSound();
    }

    //press ESC to open the pause menu
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        PauseMenuState* pauseMenuState = new PauseMenuState(this->stateMachine, &this->musicPlayer);
        this->stateMachine->pushState(pauseMenuState);
    }

    //spawn enemies
    enemySpawnFrames++;
    if (enemySpawnFrames>MIN_ENEMY_SPAWN_TIME && enemies.size()<MAX_ENEMIES) {
        if (rand()%(1+enemies.size()*15)==0) {
            if (rand()%5==0) {
                Enemy enemy(2, &enemy2Texture);
                enemies.push_back(enemy);
            } else {
                Enemy enemy(1, &enemy1Texture);
                enemies.push_back(enemy);
            }
            enemySpawnFrames = 0;
        }
    }

    this->enemyPlayerCollision();

    this->playerOutOfBounds();

    ammoCount.setString("Ammo: "+intToString(player.getAmmoCount()) + "/" + intToString(player.getMaxAmmoCount() ) );

    fireAnimation.advanceAnimation();
    fireLeft.setTextureRect(fireAnimation.getCurrentIntRect());
    fireRight.setTextureRect(fireAnimation.getCurrentIntRect());

    musicPlayer.play();
}

void EndlessModeState::draw(sf::RenderWindow& window) {
    window.draw(background);

    map.drawToScreen(window);

    window.draw(fireLeft);
    window.draw(fireRight);

    for(unsigned i=0 ; i<projectiles.size() ; i++) {
        projectiles[i].drawToScreen(window);
    }
    for (unsigned i=0 ; i<enemies.size() ; i++) {
        enemies[i].drawToScreen(window);
    }

    player.drawToScreen(window);

    weaponCrate.drawToScreen(window);

    window.draw(playerScore);
    window.draw(ammoCount);
}
