#pragma once

#include <SFML/Audio.hpp>
#include <algorithm>

#include "MoreInfo.h"

class MusicPlayer {
public:
    MusicPlayer();
    void play();
    void stop();
    void setVolume(int percentage);

private:
    sf::Music music;
    int index;
    std::vector<std::string> songFiles;
};

