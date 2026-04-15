#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <SFML/Graphics.hpp>
#include "GameState.h"

class Game;

class PauseMenu
{
public:
    PauseMenu(sf::Font &font);
    void setTitleFont(sf::Font &font);
    void draw(sf::RenderWindow &window);
    void handleInput(sf::Event &event, bool &isPaused, GameState &currentState, Game *game);
    void reset();

private:
    sf::Font font;
    sf::Font titleFont;
    sf::Text titleText;
    sf::Text menuItems[3];
    int selectedItemIndex;

    void moveUp();
    void moveDown();
    void select(bool &isPaused, GameState &currentState, Game *game);
};

#endif