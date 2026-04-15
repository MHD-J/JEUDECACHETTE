#include "../include/PauseMenu.h"
#include "../include/Constants.h"
#include "../include/Game.h"

PauseMenu::PauseMenu(sf::Font &f) : font(f)
{
    std::string optionTexts[3] = {"Resume", "Replay", "Menu"};

    titleText.setFont(font);
    titleText.setString("PAUSED");
    titleText.setCharacterSize(70);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setStyle(sf::Text::Bold);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition(
        Constants::WINDOW_WIDTH / 2 - titleBounds.width / 2,
        150);

    for (int i = 0; i < 3; i++)
    {
        menuItems[i].setFont(font);
        menuItems[i].setString(optionTexts[i]);
        menuItems[i].setCharacterSize(45);
        menuItems[i].setFillColor(sf::Color::White);

        sf::FloatRect bounds = menuItems[i].getLocalBounds();
        float x = (Constants::WINDOW_WIDTH - bounds.width) / 2;
        float y = 350 + (i * 80);
        menuItems[i].setPosition(x, y);
    }

    selectedItemIndex = 0;
    menuItems[selectedItemIndex].setFillColor(sf::Color::Yellow);
}

void PauseMenu::draw(sf::RenderWindow &window)
{
    sf::RectangleShape overlay(sf::Vector2f(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(overlay);

    window.draw(titleText);
    for (int i = 0; i < 3; i++)
    {
        window.draw(menuItems[i]);
    }
}

void PauseMenu::handleInput(sf::Event &event, bool &isPaused, GameState &currentState, Game *game)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Up:
            moveUp();
            break;
        case sf::Keyboard::Down:
            moveDown();
            break;
        case sf::Keyboard::Enter:
            select(isPaused, currentState, game);
            break;
        default:
            break;
        }
    }
}

void PauseMenu::setTitleFont(sf::Font &f)
{
    titleFont = f;
    titleText.setFont(titleFont);
}

void PauseMenu::moveUp()
{
    menuItems[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex--;
    if (selectedItemIndex < 0)
        selectedItemIndex = 2;
    menuItems[selectedItemIndex].setFillColor(sf::Color::Yellow);
}

void PauseMenu::moveDown()
{
    menuItems[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex++;
    if (selectedItemIndex > 2)
        selectedItemIndex = 0;
    menuItems[selectedItemIndex].setFillColor(sf::Color::Yellow);
}

void PauseMenu::select(bool &isPaused, GameState &currentState, Game *game)
{
    switch (selectedItemIndex)
    {
    case 0: // Resume
        isPaused = false;
        break;
    case 1: // Replay
        isPaused = false;
        if (game != nullptr)
        {
            game->resetGame();
            game->timer.start();
        }
        currentState = GameState::PLAYING;
        break;
    case 2: // Menu
        isPaused = false;
        currentState = GameState::MENU;
        break;
    }
}

void PauseMenu::reset()
{
    selectedItemIndex = 0;
    for (int i = 0; i < 3; i++)
    {
        menuItems[i].setFillColor(sf::Color::White);
    }
    menuItems[0].setFillColor(sf::Color::Yellow);
}