#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#define MAX_ITEMS 3 // Jouer, À propos, Quitter

class Menu {
private:
    sf::Font font;
    sf::Text menuItems[MAX_ITEMS];
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    int selectedItemIndex;

public:
    Menu(float width, float height);
    
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    
    // Pour savoir quel bouton est cliqué
    int getPressedItem() { return selectedItemIndex; }
    
    // Optionnel : Gestion de la souris
    void updateMouse(sf::Vector2i mousePos);
    int handleClick(sf::Vector2i mousePos);
};

#endif