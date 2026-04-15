#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "MenuBackground.h"

class Menu
{
public:
    Menu(sf::Font &font);
    void setTitleFont(sf::Font &font);
    void update(float dt); // Nouvelle fonction
    void draw(sf::RenderWindow &window);
    void handleInput(sf::Event &event, GameState &currentState, sf::RenderWindow &window);
    void reset();

private:
    sf::Font font;
    sf::Font titleFont;
    sf::Text titleText;
    sf::Text menuItems[3];
    int selectedItemIndex;

    MenuBackground background; // Nouveau

    void moveUp();
    void moveDown();
    void select(GameState &currentState, sf::RenderWindow &window);
};

#endif