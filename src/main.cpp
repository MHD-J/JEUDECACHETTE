#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Game.h"
#include "../include/Constants.h"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT),
        Constants::WINDOW_TITLE);
    window.setFramerateLimit(Constants::FRAME_RATE_LIMIT);

    // Chargement des polices
    sf::Font fontTitle;
    sf::Font fontText;
    sf::Font fontArial;

    if (!fontTitle.loadFromFile(Constants::FONT_PATH_TITLE))
    {
        std::cout << "3Dumb.ttf non trouvé, utilisation Arial" << std::endl;
        fontTitle.loadFromFile(Constants::FONT_PATH);
    }

    if (!fontText.loadFromFile(Constants::FONT_PATH_TEXT))
    {
        std::cout << "2Dumb.ttf non trouvé, utilisation Arial" << std::endl;
        fontText.loadFromFile(Constants::FONT_PATH);
    }

    // Création du jeu avec la police de texte (2Dumb)
    Game game(window, fontText);

    // Application des polices (titre en 3Dumb)
    game.applyFonts(fontTitle, fontText);

    game.run();

    return 0;
}