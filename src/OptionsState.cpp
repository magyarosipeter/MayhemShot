#include "OptionsState.h"

std::string unsignedToStringMenu(unsigned n) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}

OptionsState::OptionsState(StateMachine* stateMachine) {
    this->stateMachine = stateMachine;

    std::fstream fin(OPTIONS_DATA);
    fin >> volume >> highScore;
    fin.close();

    volume = volume%101;

    backgroundTexture.loadFromFile(OPTIONS_BACKGROUND_TEXTURE);
    background.setTexture(backgroundTexture);
    background.setColor(sf::Color(255,255,255,120));

    title.setAttributes(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT*5/100),
        "Options and Credits",
        90,
        TIMES_FONT,
        ORANGE
    );

    font.loadFromFile(TIMES_FONT);
    descriptionText.setFont(font);
    descriptionText.setCharacterSize(50);
    descriptionText.setString("Made with SFML         and love    ");
    descriptionText.setOrigin(sf::Vector2f(descriptionText.getGlobalBounds().width/2, descriptionText.getGlobalBounds().height/2));
    descriptionText.setPosition(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT*80/100));

    creatorText.setFont(font);
    creatorText.setCharacterSize(50);
    creatorText.setString("By Magyarosi Péter");
    creatorText.setOrigin(sf::Vector2f(creatorText.getGlobalBounds().width/2, creatorText.getGlobalBounds().height/2));
    creatorText.setPosition(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT*70/100));

    SFMLTexture.loadFromFile(SFML_TEXTURE);
    heartTexture.loadFromFile(HEART_TEXTURE);
    SFMLSprite.setTexture(SFMLTexture);
    SFMLSprite.setScale(0.60, 0.60);
    SFMLSprite.setOrigin(SFMLSprite.getGlobalBounds().width/2, SFMLSprite.getGlobalBounds().height/2);
    SFMLSprite.setPosition(sf::Vector2f(690, 665));
    heartSprite.setTexture(heartTexture);
    heartSprite.setScale(0.55, 0.55);
    heartSprite.setOrigin(heartSprite.getGlobalBounds().width/2, heartSprite.getGlobalBounds().height/2);
    heartSprite.setPosition(sf::Vector2f(950, 665));

    backButton.setAttributes(
        sf::Vector2f(SCREEN_WIDTH*10/100, SCREEN_HEIGHT*90/100),
		sf::Vector2f(120, 50),
		"Back",
		60,
		TIMES_FONT,
		OPAQUE_GREY,
		OPAQUE_GREY,
		sf::Color::White,
		SALMON
    );

    highScoreText.setCharacterSize(50);
    highScoreText.setFont(font);
    highScoreText.setString("Highscore:");
    highScoreText.setOrigin(sf::Vector2f(highScoreText.getGlobalBounds().width/2, highScoreText.getGlobalBounds().height/2));
    highScoreText.setPosition(sf::Vector2f(SCREEN_WIDTH*3/4, SCREEN_HEIGHT*25/100));

    highScoreNumber.setCharacterSize(50);
    highScoreNumber.setFont(font);
    highScoreNumber.setString(""+unsignedToStringMenu(highScore));
    highScoreNumber.setOrigin(sf::Vector2f(highScoreNumber.getGlobalBounds().width/2, highScoreNumber.getGlobalBounds().height/2));
    highScoreNumber.setPosition(highScoreText.getPosition());
    highScoreNumber.move(0, highScoreNumber.getGlobalBounds().height*1.5f);

    volumeSlider.create(sf::Vector2f(SCREEN_WIDTH/7, SCREEN_HEIGHT*30/100), sf::Vector2f(400, 35), "Volume", 100, volume, "%", TIMES_FONT);
}

void OptionsState::update(sf::RenderWindow &window, sf::Time deltaTime, bool &mouseClicked) {
    sf::Vector2i transformedMousePos;
    transformedMousePos.x = ( ((double)sf::Mouse::getPosition(window).x) / window.getSize().x * 100 ) * SCREEN_WIDTH / 100;
    transformedMousePos.y = ( ((double)sf::Mouse::getPosition(window).y) / window.getSize().y * 100 ) * SCREEN_HEIGHT / 100;

    if(backButton.update(transformedMousePos, mouseClicked)) {
        stateMachine->popState();
    }
    if (volumeSlider.checkInput(transformedMousePos)) {
        std::ofstream fout(OPTIONS_DATA);
        volume = volumeSlider.getPercentage();
        fout << volume << " " << highScore;
        sf::Listener::setGlobalVolume( volume );
    }

    //std::cout << transformedMousePos.x << " " << transformedMousePos.y << std::endl;
}

void OptionsState::draw(sf::RenderWindow& window) {
    window.draw(background);

    title.drawToScreen(window);

    window.draw(creatorText);
    window.draw(SFMLSprite);
    window.draw(heartSprite);
    window.draw(descriptionText);

    window.draw(highScoreText);
    window.draw(highScoreNumber);

    volumeSlider.drawToScreen(window);

	backButton.drawToScreen(window);
}
