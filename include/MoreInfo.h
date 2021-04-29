#pragma once

//General
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 832

#define MAP_HEIGHT 13
#define MAP_WIDTH 20

#define MAP_TILE_SIZE 64

#define PI 3.14159

#define ENEMY_1_TEXTURE_SIZE 50
#define ENEMY_2_TEXTURE_SIZE 80

//Variables
#define GRAVITY 3
#define MAX_GRAVITY 21

#define COLOR_CLEAR sf::Color(255,255,255,0)
#define OPAQUE_GREY sf::Color(0,0,0,50)
#define GREY sf::Color(170,170,170)
#define ORANGE sf::Color(255,187,0)
#define SKY_BLUE sf::Color(119, 217, 252)

#define OPAQUE_RED sf::Color(255, 0, 0, 225)
#define SALMON sf::Color(237, 112, 81, 255)

//Font
#define TIMES_FONT "resources/fonts/Crimson-Roman.ttf"

//Textures
#define MENU_BACKGROUND_TEXTURE "resources/images/Background_01.png"
#define OPTIONS_BACKGROUND_TEXTURE "resources/images/Background_02.png"
#define GAME_BACKGROUND_TEXTURE "resources/images/Background_03.png"

#define GROUND_TILES_TEXTURE "resources/images/GroundTiles.png"
#define WEAPONS_TEXTURE "resources/images/weapons.png"
#define WEAPON_CRATE_TEXTURE "resources/images/crate.png"

#define ENEMY_1_TEXTURE "resources/images/enemy1.png"
#define ENEMY_2_TEXTURE "resources/images/enemy2.png"

#define PLAYER_TEXTURE "resources/images/player.png"

#define SFML_TEXTURE "resources/images/SFML_logo.png"
#define HEART_TEXTURE "resources/images/heart.png"

//Sound Effects
#define PISTOL_SOUND "resources/sounds/pistol.wav"
#define SHOTGUN_SOUND "resources/sounds/shotgun.wav"
#define RIFLE_SOUND "resources/sounds/rifle.wav"
#define SNIPER_SOUND "resources/sounds/sniper.wav"
#define GUN_PICKUP_SOUND "resources/sounds/gunPickup.wav"

#define LOSE_GAME_SOUND "resources/sounds/lose.wav"
#define ENEMY_DIE_SOUND "resources/sounds/enemyDie.wav"
#define ENEMY_ENRAGE_SOUND "resources/sounds/enemyEnrage.wav"
#define JUMP_SOUND "resources/sounds/jump.wav"

#define SONG_1 "resources/music/Steady Hands.ogg"
#define SONG_2 "resources/music/Mutant Slayer.ogg"
