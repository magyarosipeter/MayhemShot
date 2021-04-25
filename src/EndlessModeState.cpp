#include "EndlessModeState.h"
#include "PauseMenuState.h"
#include <sstream>

std::string intToString(int n) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}

EndlessModeState::EndlessModeState(StateMachine* stateMachine) {
    this->stateMachine = stateMachine;

    map.loadMap(GROUND_TILES_TEXTURE);
    weaponCrate.setRandomPosition(map.tileMap);

    //spawning an enemy is possible straight away when starting the game
    enemySpawnFrames = MIN_ENEMY_SPAWN_TIME;

    enemyDieSoundBuffer.loadFromFile(ENEMY_DIE_SOUND);
    enemyDieSound.setBuffer(enemyDieSoundBuffer);

    enrageSoundBuffer.loadFromFile(ENEMY_ENRAGE_SOUND);
    enrageSound.setBuffer(enrageSoundBuffer);

    font.loadFromFile(TIMES_FONT);
    playerKills = 0;
    playerScore.setFont(font);
    playerScore.setCharacterSize(40);
    playerScore.setString("Score: 0");

    music.openFromFile(SONG_1);
    music.play();
}

void deleteProjectiles(std::vector<Projectile> &projectiles, Tile tileMap[MAP_HEIGHT][MAP_WIDTH]) {
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
                    if (tileMap[j][k].isSolid() && projectiles[i].hitbox.getGlobalBounds().intersects(tileMap[j][k].hitbox.getGlobalBounds())) {
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

void EndlessModeState::update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked) {
    //get actual mouse position when window has been resized
    sf::Vector2i transformedMousePos;
    transformedMousePos.x = ( ((double)sf::Mouse::getPosition(window).x) / window.getSize().x * 100 ) * SCREEN_WIDTH / 100;
    transformedMousePos.y = ( ((double)sf::Mouse::getPosition(window).y) / window.getSize().y * 100 ) * SCREEN_HEIGHT / 100;

    //WASD input, movement and collision
    player.movement(map.tileMap, window);

    //mouse input, shooting
    player.shoot(projectiles);

    //move projectiles
    for (unsigned i=0 ; i<projectiles.size() ; i++) projectiles[i].movement();

    //move enemies
    for (unsigned i=0 ; i<enemies.size() ; i++) {
        enemies[i].movement(map.tileMap, window);
    }
    //deal with enemies falling out of the map
    this->enemyOutOfBounds();

    //kill enemy and delete projectile that collide with them
    this->killEnemies();
    //killEnemies(projectiles, enemies, player);

    //delete projectiles that collide with solid blocks
    deleteProjectiles(projectiles, map.tileMap);

    //player picks up crate for random weapon
    if (player.globalBounds().intersects(weaponCrate.globalBounds())) {
        player.setWeapon(weaponCrate.rollWeapon());
        weaponCrate.setRandomPosition(map.tileMap);
        player.playPickupSound();
    }

    //press ESC to open the pause menu
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        PauseMenuState* pauseMenuState = new PauseMenuState(this->stateMachine);
        this->stateMachine->pushState(pauseMenuState);
    }

    //spawn enemies
    enemySpawnFrames++;
    if (enemySpawnFrames>MIN_ENEMY_SPAWN_TIME && enemies.size()<MAX_ENEMIES) {
        if (rand()%(1+enemies.size()*30)==0) {
            Enemy enemy;
            enemies.push_back(enemy);
            enemySpawnFrames = 0;
        }
    }
}

void EndlessModeState::draw(sf::RenderWindow& window) {
    map.drawToScreen(window);

    for(unsigned i=0 ; i<projectiles.size() ; i++) {
        projectiles[i].drawToScreen(window);
    }
    for (unsigned i=0 ; i<enemies.size() ; i++) {
        enemies[i].drawToScreen(window);
    }

    player.drawToScreen(window);

    weaponCrate.drawToScreen(window);

    window.draw(playerScore);
}
