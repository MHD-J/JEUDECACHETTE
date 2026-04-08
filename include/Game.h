#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Player.h"
#include "Timer.h"
#include "Collision.h"

class Game
{
public:
    Game(sf::RenderWindow &window, sf::Font &font);
    void run();
    void changeState(GameState newState);

private:
    sf::RenderWindow &window;
    sf::Font &font;
    GameState currentState;

    Player player;
    Timer timer;

    void handleEvents();
    void update();
    void render();
    void resetGame();

    // pour backG
    sf::Texture backgroundTexture;
    sf::Sprite background1;
    sf::Sprite background2;
    float bgSpeed;

    // pour Bunker
    sf::Texture bunkerTexture;
    sf::Sprite bunkerSprite;
    float bunkerX;
};

#endif