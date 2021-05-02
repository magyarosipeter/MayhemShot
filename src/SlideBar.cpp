#include "SlideBar.h"

std::string toString2( int n ) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}

SlideBar::SlideBar() {
    // ctor
}

void SlideBar::create(sf::Vector2f position, sf::Vector2f size, std::string descriptionName, double maximValue, double startingValue, std::string suffixText, std::string fontFile) {
    maxValue = maximValue;

    percentage = startingValue/maximValue*100;

    statusBar.setFillColor(sf::Color::White);
    statusBar.setSize(size);

    boundary.setSize(sf::Vector2f(size.x*1.1, size.y*1.5));
    boundary.setFillColor(sf::Color::Cyan);

    statusMarker.setFillColor(sf::Color::Red);
    statusMarker.setSize(sf::Vector2f(20, size.y*1.35));
    statusMarker.setOrigin(sf::Vector2f(10, 0));

    description.setString(descriptionName);
    description.setCharacterSize(size.y);
    description.setFillColor(sf::Color::White);

    suffix = suffixText;
    valueText.setString(toString2(percentage*maximValue/100) + suffix);
    valueText.setCharacterSize(size.y*80/100);
    valueText.setFillColor(sf::Color::White);

    filler.setFillColor(sf::Color::Red);
    filler.setSize(sf::Vector2f(percentage*size.x/100, size.y));

    this->font.loadFromFile(fontFile);
    description.setFont(this->font);
    valueText.setFont(this->font);

    this->setPosition(position);
}

void SlideBar::setPosition(sf::Vector2f position) {
    statusBar.setPosition(position);
    statusMarker.setPosition(position);
    statusMarker.move( percentage*statusBar.getSize().x/100, -5);

    description.setPosition(position);
    description.move(0, -description.getGlobalBounds().height*2);

    boundary.setPosition(position);
    boundary.move( - (statusBar.getSize().x*1.075 - statusBar.getSize().x), -10 );

    valueText.setPosition(position);
    valueText.move( statusBar.getSize().x*1.06 , 0);

    filler.setPosition(position);
}

int SlideBar::getPercentage() {
    return percentage;
}

void SlideBar::setPercentage(int percent) {
    percentage = percent;
    filler.setSize(sf::Vector2f(percentage*statusBar.getSize().x/100, 15));
    valueText.setString(toString2(percentage*maxValue/100) + suffix);
    statusMarker.setPosition(statusBar.getPosition());
    statusMarker.move(percentage*statusBar.getSize().x/100, -5);
}

int SlideBar::getValue() {
    return percentage*maxValue/100.0f;
}

bool SlideBar::checkInput(sf::Vector2i transformedMousePos) {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if ( boundary.getGlobalBounds().contains( transformedMousePos.x, transformedMousePos.y ) ) {
            percentage = (transformedMousePos.x - statusBar.getPosition().x) / statusBar.getSize().x * 100;
            if (percentage < 0) {
                statusMarker.setPosition(statusBar.getPosition().x, statusMarker.getPosition().y );
                percentage = 0;
            }
            else if (percentage > 100) {
                statusMarker.setPosition(statusBar.getPosition().x+statusBar.getSize().x, statusMarker.getPosition().y );
                percentage = 100;
            }
            else {
                statusMarker.setPosition(transformedMousePos.x, statusMarker.getPosition().y );
            }
            filler.setSize(sf::Vector2f(percentage*statusBar.getSize().x/100, filler.getSize().y));
            valueText.setString(toString2(percentage*maxValue/100) + suffix);
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

void SlideBar::drawToScreen(sf::RenderWindow &window) {
    //window.draw(boundary);
    window.draw(description);
    window.draw(statusBar);
    window.draw(filler);
    window.draw(statusMarker);
    window.draw(valueText);
}
