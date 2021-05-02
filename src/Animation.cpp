#include "Animation.h"

Animation::Animation() {
    index = 0;
    currentFrameValue = 0;
    this->switchFrameValue = 10;
}

void Animation::advanceAnimation() {
    currentFrameValue++;
    if (currentFrameValue>=switchFrameValue) {
        currentFrameValue = 0;
        index++;
    }
    if (index>frames.size()-1) {
        index=0;
    }
}

void Animation::setSwitchFrameValue(unsigned switchFrameValue) {
    this->switchFrameValue = switchFrameValue;
}

void Animation::addIntRect(sf::IntRect newIntRect) {
    frames.push_back(newIntRect);
}

sf::IntRect Animation::getCurrentIntRect() {
    return frames[index];
}
