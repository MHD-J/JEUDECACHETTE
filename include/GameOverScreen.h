#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <SFML/Graphics.hpp>
#include "GameState.h"

class GameOverScreen
{
public:
    GameOverScreen(sf::Font &font);
    void draw(sf::RenderWindow &window);
    void handleInput(sf::Event &event, GameState &currentState, bool &shouldReset);
    void setVictory(bool isVictory);
    void setHighScore(float score);
    void setTitleFont(sf::Font &font); // Pour le titre (3Dumb)
    void reset();

private:
    sf::Font font;
    sf::Text titleText;
    sf::Font titleFont;
    sf::Text optionReplay;
    sf::Text optionMenu;
    sf::Text highScoreText;
    sf::Text reasonText;
    int selectedIndex;
    bool victory;
    bool waitingForRelease;
    float currentHighScore;

    void moveUp();
    void moveDown();
    void select(GameState &currentState, bool &shouldReset);
};

#endif