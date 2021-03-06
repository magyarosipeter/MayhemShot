#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() {
    songFiles.push_back(SONG_1);
    songFiles.push_back(SONG_2);
    index = rand()%2;
    music.openFromFile(songFiles[index]);
    music.play();
    music.setVolume(50.f);
}

void MusicPlayer::play() {
    if (music.getStatus() == sf::SoundSource::Stopped) {
        index++;
        if (index==songFiles.size()) {
            index = 0;
        }
        music.openFromFile(songFiles[index]);
        music.stop();
        music.play();
    }
}

void MusicPlayer::stop() {
    music.stop();
}

void MusicPlayer::setVolume(int percentage) {
    music.setVolume(percentage);
}

