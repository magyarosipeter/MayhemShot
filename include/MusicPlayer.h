#pragma once

#include <SFML/Audio.hpp>

#include "MoreInfo.h"

class MusicPlayer {
public:
    MusicPlayer();
    void play();
    void stop();

private:
    sf::Music music;
    int index;
    std::vector<std::string> songFiles;
};

