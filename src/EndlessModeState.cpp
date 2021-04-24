#include "EndlessModeState.h"
#include "PauseMenuState.h"

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

void killEnemies(std::vector<Projectile> &projectiles, std::vector<Enemy> &enemies, Player &player) {
    for (int i=0 ; i<enemies.size() ; i++) {
        for (int j=0 ; j<projectiles.size() && i>=0 && i<enemies.size() ; j++) {
            if (projectiles[j].globalBounds().intersects(enemies[i].globalBounds())) {
                projectiles.erase(projectiles.begin()+j);
                j--;

                enemies[i].setHealth(enemies[i].getHealth() - player.getDamage());
                if (enemies[i].getHealth()<=0) {
                    enemies.erase(enemies.begin()+i);
                    i--;
                }
            }
        }
    }
}


void enemyOutOfBounds(std::vector<Enemy> &enemies) {
    unsigned i=0;
    while ( i<enemies.size() ) {
        if (enemies[i].getPosition().y>SCREEN_HEIGHT*110/100) {
            enemies[i].setAngry();
        }
        i++;
    }
}


EndlessModeState::EndlessModeState(StateMachine* stateMachine) {
    this->stateMachine = stateMachine;

    map.loadMap(GROUND_TILES_TEXTURE);
    weaponCrate.setRandomPosition(map.tileMap);

    //spawning an enemy is possible straight away when starting the game
    enemySpawnFrames = MIN_ENEMY_SPAWN_TIME;
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
    enemyOutOfBounds(enemies);

    //delete projectiles that collide with solid blocks
    deleteProjectiles(projectiles, map.tileMap);

    killEnemies(projectiles, enemies, player);

    //player picks up crate for random weapon
    if (player.globalBounds().intersects(weaponCrate.globalBounds())) {
        player.setWeapon(weaponCrate.rollWeapon());
        weaponCrate.setRandomPosition(map.tileMap);
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
}
