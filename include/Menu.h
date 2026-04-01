#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "GameState.h"

class Menu
{
public:
    Menu(sf::Font& font);
    void draw(sf::RenderWindow& window);
    void handleInput(sf::Event& event,GameState& currentState);

private:
    sf::Text options[3];
    int selectedindex ;
};

#endif