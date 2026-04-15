#include "../include/GameOverScreen.h"
#include "../include/Constants.h"

GameOverScreen::GameOverScreen(sf::Font &f) : font(f), selectedIndex(0), victory(false), waitingForRelease(false), currentHighScore(0)
{
    titleText.setFont(font);
    titleText.setCharacterSize(Constants::GAMEOVER_TITLE_SIZE);
    titleText.setStyle(sf::Text::Bold);

    optionReplay.setFont(font);
    optionReplay.setString(" REPLAY ");
    optionReplay.setCharacterSize(Constants::GAMEOVER_OPTION_SIZE);

    optionMenu.setFont(font);
    optionMenu.setString("  MENU  ");
    optionMenu.setCharacterSize(Constants::GAMEOVER_OPTION_SIZE);

    highScoreText.setFont(font);
    highScoreText.setCharacterSize(28);
    highScoreText.setFillColor(Constants::COLOR_HIGH_LIGHT);

    reasonText.setFont(font);
    reasonText.setCharacterSize(24);
    reasonText.setFillColor(sf::Color(200, 200, 200));
}

void GameOverScreen::setVictory(bool isVictory)
{
    victory = isVictory;
    if (victory)
    {
        titleText.setString("VICTORY!");
        titleText.setFillColor(sf::Color(50, 255, 100));
        reasonText.setString("You reached the bunker!");
    }
    else
    {
        titleText.setString("GAME OVER");
        titleText.setFillColor(sf::Color::Red);
        reasonText.setString("You were eliminated...");
    }

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition(
        Constants::WINDOW_WIDTH / 2 - titleBounds.width / 2,
        Constants::WINDOW_HEIGHT / 2 - 200);

    // text reason
    sf::FloatRect reasonBounds = reasonText.getLocalBounds();
    reasonText.setPosition(
        Constants::WINDOW_WIDTH / 2 - reasonBounds.width / 2,
        Constants::WINDOW_HEIGHT / 2 - 100);

    // text high score
    highScoreText.setString("BEST DISTANCE: " + std::to_string((int)currentHighScore) + "m");
    sf::FloatRect highScoreBounds = highScoreText.getLocalBounds();
    highScoreText.setPosition(
        Constants::WINDOW_WIDTH / 2 - highScoreBounds.width / 2,
        Constants::WINDOW_HEIGHT / 2 - 40);

    sf::FloatRect replayBounds = optionReplay.getLocalBounds();
    optionReplay.setPosition(
        Constants::WINDOW_WIDTH / 2 - replayBounds.width / 2,
        Constants::GAMEOVER_OPTION_START_Y);

    sf::FloatRect menuBounds = optionMenu.getLocalBounds();
    optionMenu.setPosition(
        Constants::WINDOW_WIDTH / 2 - menuBounds.width / 2,
        Constants::GAMEOVER_OPTION_START_Y + Constants::GAMEOVER_OPTION_SPACING);

    selectedIndex = 0;
    optionReplay.setFillColor(Constants::COLOR_HIGH_LIGHT);
    optionMenu.setFillColor(Constants::COLOR_TEXT);
    waitingForRelease = false;
}

void GameOverScreen::setHighScore(float score)
{
    currentHighScore = score;
}

void GameOverScreen::draw(sf::RenderWindow &window)
{
    window.draw(titleText);
    window.draw(reasonText);
    window.draw(highScoreText);
    window.draw(optionReplay);
    window.draw(optionMenu);
}

void GameOverScreen::handleInput(sf::Event &event, GameState &currentState, bool &shouldReset)
{
    if (event.type == sf::Event::KeyPressed && !waitingForRelease)
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
            select(currentState, shouldReset);
            waitingForRelease = true;
            break;
        case sf::Keyboard::R:
            if (selectedIndex == 0)
            {
                select(currentState, shouldReset);
                waitingForRelease = true;
            }
            break;
        case sf::Keyboard::M:
            if (selectedIndex == 1)
            {
                select(currentState, shouldReset);
                waitingForRelease = true;
            }
            break;
        default:
            break;
        }
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        waitingForRelease = false;
    }
}

void GameOverScreen::setTitleFont(sf::Font &newFont)
{
    titleFont = newFont;
    titleText.setFont(titleFont);
}

void GameOverScreen::moveUp()
{
    optionReplay.setFillColor(Constants::COLOR_TEXT);
    optionMenu.setFillColor(Constants::COLOR_TEXT);
    selectedIndex--;
    if (selectedIndex < 0)
        selectedIndex = 1;

    if (selectedIndex == 0)
        optionReplay.setFillColor(Constants::COLOR_HIGH_LIGHT);
    else
        optionMenu.setFillColor(Constants::COLOR_HIGH_LIGHT);
}

void GameOverScreen::moveDown()
{
    optionReplay.setFillColor(Constants::COLOR_TEXT);
    optionMenu.setFillColor(Constants::COLOR_TEXT);
    selectedIndex++;
    if (selectedIndex > 1)
        selectedIndex = 0;

    if (selectedIndex == 0)
        optionReplay.setFillColor(Constants::COLOR_HIGH_LIGHT);
    else
        optionMenu.setFillColor(Constants::COLOR_HIGH_LIGHT);
}

void GameOverScreen::select(GameState &currentState, bool &shouldReset)
{
    shouldReset = true;

    if (selectedIndex == 0) 
    {
        currentState = GameState::PLAYING;
    }
    else // Menu
    {
        currentState = GameState::MENU;
    }
}

void GameOverScreen::reset()
{
    selectedIndex = 0;
    optionReplay.setFillColor(Constants::COLOR_HIGH_LIGHT);
    optionMenu.setFillColor(Constants::COLOR_TEXT);
    waitingForRelease = false;
}