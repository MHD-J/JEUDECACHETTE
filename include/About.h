#ifndef About_H
#define About_H
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "GameState.h"
class About{
    public:
        About(sf::Font& font);
        void draw(sf::RenderWindow& window);
        void handleInput(sf::Event& event,GameState& currentState);
    private:
        sf::Text infoText;
        sf::Text backText;
};
#endif