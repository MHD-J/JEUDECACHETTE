#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), Constants::WINDOW_TITLE);
    window.setVerticalSyncEnabled(true);
    sf::Font font;
    if (!font.loadFromFile(Constants::FONT_PATH))
    {
        return -1;
    }
    Game game(window,font);
    game.run();
    
    return 0;
}