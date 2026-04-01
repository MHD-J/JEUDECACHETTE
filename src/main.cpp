#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), "Jeu de Cachette");
    window.setVerticalSyncEnabled(true);
    sf::Font font;
    if (!font.loadFromFile(Constants::FONT_PATH))
    {
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Menu");
    text.setCharacterSize(Constants::MENU_TITLE_SIZE);
    text.setPosition(200, 200);
    text.setFillColor(Constants::COLOR_TEXT);

    sf::FloatRect textBounds = text.getLocalBounds();
    float centerX = (window.getSize().x - textBounds.width) / 2;
    float centerY = (window.getSize().y - textBounds.height) / 2;
    text.setPosition(centerX, centerY);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
            
        }
        window.clear(Constants::COLOR_Background);
        window.draw(text);
        window.display();
    }
    
    return 0;
}