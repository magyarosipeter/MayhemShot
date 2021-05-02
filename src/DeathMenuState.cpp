#include "DeathMenuState.h"
#include <sstream>

std::string intToString2(int n) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}

DeathMenuState::DeathMenuState(StateMachine* stateMachine, int score, MusicPlayer* musicPlayer) {
    this->stateMachine = stateMachine;
    this->musicPlayer = musicPlayer;

    youDiedText.setAttributes(
        sf::Vector2f(SCREEN_WIDTH/2,SCREEN_HEIGHT*20/100),
        "You died!",
        120,
        TIMES_FONT,
        ORANGE
    );

    font.loadFromFile(TIMES_FONT);
    this->score.setFont(font);
    this->score.setCharacterSize(60);
    this->score.setString(std::string("Your score: "+intToString2(score)));
    this->score.setOrigin(this->score.getGlobalBounds().width/2, this->score.getGlobalBounds().height/2);
    this->score.setPosition(sf::Vector2f(SCREEN_WIDTH/2,SCREEN_HEIGHT*40/100));

    retryButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH/2,SCREEN_HEIGHT*60/100),
        sf::Vector2f(150, 80),
        "Retry",
        70,
        TIMES_FONT,
        OPAQUE_GREY,
        OPAQUE_GREY,
        sf::Color::White,
        SALMON
    );

    backToMenuButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH/2,SCREEN_HEIGHT*75/100),
        sf::Vector2f(500, 80),
        "Return to Main Menu",
        70,
        TIMES_FONT,
        OPAQUE_GREY,
        OPAQUE_GREY,
        sf::Color::White,
        SALMON
    );

    newHighscoreText.setAttributes(
        sf::Vector2f(SCREEN_WIDTH/2,SCREEN_HEIGHT*48/100),
        "New highscore!",
        20,
        TIMES_FONT,
        sf::Color::White
    );

    //read data from options, if latest score is bigger than highscore, we change it in the files
    unsigned highScore;
    unsigned volume;
    std::ifstream fin(OPTIONS_DATA);
    fin >> volume >> highScore;
    fin.close();
    if (highScore<score) {
        std::ofstream fout(OPTIONS_DATA);
        fout << volume <<" "<< score;
        highScoreVisible = true;
    }
    else {
        highScoreVisible = false;
    }
}

void DeathMenuState::update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked) {
    //get actual mouse position when window has been resized
    sf::Vector2i transformedMousePos;
    transformedMousePos.x = ( ((double)sf::Mouse::getPosition(window).x) / window.getSize().x * 100 ) * SCREEN_WIDTH / 100;
    transformedMousePos.y = ( ((double)sf::Mouse::getPosition(window).y) / window.getSize().y * 100 ) * SCREEN_HEIGHT / 100;

    if (retryButton.update(transformedMousePos, mouseClicked)) {
        stateMachine->popState();
    } else if (backToMenuButton.update(transformedMousePos, mouseClicked)) {
        musicPlayer->stop();
        stateMachine->popState(2);
    }

    if (highScoreVisible) {
        newHighscoreText.animation();
    }
}

void DeathMenuState:: draw(sf::RenderWindow& window) {
    youDiedText.drawToScreen(window);
    window.draw(score);

    retryButton.drawToScreen(window);
    backToMenuButton.drawToScreen(window);

    if (highScoreVisible) {
        newHighscoreText.drawToScreen(window);
    }
}
