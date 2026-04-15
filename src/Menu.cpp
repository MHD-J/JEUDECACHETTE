#include "../include/Menu.h"
#include "../include/Constants.h"
#include "../include/GameState.h"

Menu::Menu(sf::Font &f) : font(f), titleFont(f)
{
    std::string optionTexts[3] = {"Play", "About", "Quit"};

    titleText.setFont(font);
    titleText.setString("HIDE AND SEEK");
    titleText.setCharacterSize(Constants::MENU_TITLE_SIZE);
    titleText.setFillColor(Constants::COLOR_HIGH_LIGHT);
    titleText.setStyle(sf::Text::Bold);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition(
        Constants::WINDOW_WIDTH / 2 - titleBounds.width / 2,
        Constants::MENU_TITLE_Y);

    for (int i = 0; i < 3; i++)
    {
        menuItems[i].setFont(font);
        menuItems[i].setString(optionTexts[i]);
        menuItems[i].setCharacterSize(Constants::MENU_OPTION_SIZE);
        menuItems[i].setFillColor(Constants::COLOR_TEXT);

        sf::FloatRect bounds = menuItems[i].getLocalBounds();
        float x = (Constants::WINDOW_WIDTH - bounds.width) / 2;
        float y = Constants::MENU_OPTION_START_Y + (i * Constants::MENU_OPTION_SPACING);
        menuItems[i].setPosition(x, y);
    }

    selectedItemIndex = 0;
    menuItems[selectedItemIndex].setFillColor(Constants::COLOR_HIGH_LIGHT);
}

void Menu::setTitleFont(sf::Font &newFont)
{
    titleFont = newFont;
    titleText.setFont(titleFont);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition(
        Constants::WINDOW_WIDTH / 2 - titleBounds.width / 2,
        Constants::MENU_TITLE_Y);
}

void Menu::update(float dt)
{
    background.update(dt);
}

void Menu::draw(sf::RenderWindow &window)
{
    background.draw(window);
    window.draw(titleText);
    for (int i = 0; i < 3; i++)
    {
        window.draw(menuItems[i]);
    }
}

void Menu::handleInput(sf::Event &event, GameState &currentState, sf::RenderWindow &window)
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
            select(currentState, window);
            break;
        default:
            break;
        }
    }
}

void Menu::moveUp()
{
    menuItems[selectedItemIndex].setFillColor(Constants::COLOR_TEXT);
    selectedItemIndex--;
    if (selectedItemIndex < 0)
        selectedItemIndex = 2;
    menuItems[selectedItemIndex].setFillColor(Constants::COLOR_HIGH_LIGHT);
}

void Menu::moveDown()
{
    menuItems[selectedItemIndex].setFillColor(Constants::COLOR_TEXT);
    selectedItemIndex++;
    if (selectedItemIndex > 2)
        selectedItemIndex = 0;
    menuItems[selectedItemIndex].setFillColor(Constants::COLOR_HIGH_LIGHT);
}

void Menu::select(GameState &currentState, sf::RenderWindow &window)
{
    switch (selectedItemIndex)
    {
    case 0:
        currentState = GameState::PLAYING;
        break;
    case 1:
        currentState = GameState::ABOUT;
        break;
    case 2:
        window.close();
        break;
    }
}

void Menu::reset()
{
    selectedItemIndex = 0;
    for (int i = 0; i < 3; i++)
    {
        menuItems[i].setFillColor(Constants::COLOR_TEXT);
    }
    menuItems[0].setFillColor(Constants::COLOR_HIGH_LIGHT);
    background.reset();
}