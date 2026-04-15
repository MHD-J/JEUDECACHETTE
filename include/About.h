#ifndef ABOUT_H
#define ABOUT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameState.h"

class About
{
public:
    About(sf::Font &font);
    void setTitleFont(sf::Font &font);
    void draw(sf::RenderWindow &window);
    void handleInput(sf::Event &event, GameState &currentState);
    void reset();
    void update();

private:
    sf::Font font;
    sf::Text titleText;
    sf::Font titleFont;
    sf::Text backText;
    sf::Text scrollInstruction;

    std::vector<sf::Text> infoLines;
    float scrollOffset;
    float maxScrollOffset;

    void createInfoLines();
};

#endif