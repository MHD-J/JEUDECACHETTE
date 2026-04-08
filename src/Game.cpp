#include "../include/Game.h"
#include "../include/Constants.h"
#include <iostream>
#include <algorithm>

Game::Game(sf::RenderWindow &window, sf::Font &font) : window(window), font(font)
{
    timer.setFont(font);
    if (!backgroundTexture.loadFromFile(Constants::BACKGROUND_IMAGE))
    {
        std::cout << "Failed to load background image" << std::endl;
    }

    background1.setTexture(backgroundTexture);
    background2.setTexture(backgroundTexture);
    float imgWidth = backgroundTexture.getSize().x;
    background1.setPosition(0, 0);
    background2.setPosition(imgWidth, 0);
    bgSpeed = Constants::BACKGROUND_SPEED;

    // Pour le Bunker
    if (!bunkerTexture.loadFromFile(Constants::BUNKER_IMAGE))
    {
        std::cout << "Failed to load bunker.png" << std::endl;
    }
    bunkerSprite.setTexture(bunkerTexture);
    bunkerSprite.setScale(
        Constants::BUNKER_WIDTH / bunkerTexture.getSize().x,
        Constants::BUNKER_HEIGHT / bunkerTexture.getSize().y);
    bunkerX = Constants::BUNKER_X;
    bunkerSprite.setPosition(bunkerX, Constants::BUNKER_Y);
}

void Game::run()
{
    currentState = GameState::PLAYING;  
    timer.start();
    while (window.isOpen())
    {
        handleEvents();
        update();
        render();
    }
}

void Game::resetGame()
{
    player.reset();
    timer.reset();
    timer.start();
    float imgWidth = backgroundTexture.getSize().x;
    background1.setPosition(0, 0);
    background2.setPosition(imgWidth, 0);
    bunkerSprite.setPosition(Constants::BUNKER_X, Constants::BUNKER_Y);
}
void Game::changeState(GameState newState)
{
    currentState = newState;
    if (currentState == GameState::PLAYING)
    {
        resetGame();
        timer.start();
    }
}

void Game::handleEvents()
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

        if (currentState == GameState::PLAYING)
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space ||
                    event.key.code == sf::Keyboard::Up)
                {
                    player.jump();
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    player.crouch();
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Down)
                {
                    player.stand();
                }
            }
        }
        if (currentState == GameState::VICTORY || currentState == GameState::GAME_OVER)
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
            {
                resetGame();
                currentState = GameState::PLAYING;
                timer.start();
            }
        }
    }
}

void Game::update()
{
    if (currentState == GameState::PLAYING)
    {
        player.update();
        timer.update();

        // Check time 
        if (timer.isExpired() && !player.isDead())
        {
            player.die();
        }

        // Update background
        background1.move(-bgSpeed, 0);
        background2.move(-bgSpeed, 0);

        float imgWidth = backgroundTexture.getSize().x;
        if (background1.getPosition().x + imgWidth < 0)
        {
            background1.setPosition(background2.getPosition().x + imgWidth, 0);
        }
        if (background2.getPosition().x + imgWidth < 0)
        {
            background2.setPosition(background1.getPosition().x + imgWidth, 0);
        }
        bunkerSprite.move(-bgSpeed, 0);

        // Check if player reached bunker
        if (player.getBounds().intersects(bunkerSprite.getGlobalBounds()))
        {
            currentState = GameState::VICTORY;
        }

        // Check death animation 
        if (player.isDead() && player.isDeathAnimationComplete())
        {
            currentState = GameState::GAME_OVER;
        }
    }
}

void Game::render()
{
    window.clear(Constants::COLOR_Background);

    if (currentState == GameState::PLAYING)
    {
        window.draw(background1);
        window.draw(background2);
        window.draw(bunkerSprite);
        player.draw(window);
        timer.draw(window);
    }
    else if (currentState == GameState::GAME_OVER)
    {
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Red);

        sf::FloatRect bounds = gameOverText.getLocalBounds();
        gameOverText.setPosition(
            Constants::WINDOW_WIDTH / 2 - bounds.width / 2,
            Constants::WINDOW_HEIGHT / 2 - bounds.height / 2);
        sf::Text restartText;
        restartText.setFont(font);
        restartText.setString("Press R to restart");
        restartText.setCharacterSize(30);
        restartText.setFillColor(sf::Color::White);
        restartText.setPosition(
            Constants::WINDOW_WIDTH / 2 - bounds.width / 2,
            Constants::WINDOW_HEIGHT / 2 + 50);

        window.draw(restartText);
        window.draw(gameOverText);
    }
    else if (currentState == GameState::VICTORY)
    {
        sf::Text victoryText;
        victoryText.setFont(font);
        victoryText.setString("VICTORY!");
        victoryText.setCharacterSize(60);
        victoryText.setFillColor(sf::Color::Green);

        sf::FloatRect bounds = victoryText.getLocalBounds();
        victoryText.setPosition(
            Constants::WINDOW_WIDTH / 2 - bounds.width / 2,
            Constants::WINDOW_HEIGHT / 2 - bounds.height / 2 - 50);

        sf::Text restartText;
        restartText.setFont(font);
        restartText.setString("Press R to play again");
        restartText.setCharacterSize(30);
        restartText.setFillColor(sf::Color::White);

        sf::FloatRect restartBounds = restartText.getLocalBounds();
        restartText.setPosition(
            Constants::WINDOW_WIDTH / 2 - restartBounds.width / 2,
            Constants::WINDOW_HEIGHT / 2 + 50);

        window.draw(victoryText);
        window.draw(restartText);
    }

    window.display();
}