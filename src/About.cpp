#include "../include/About.h"
#include "../include/Constants.h"
#include "../include/GameState.h"
#include <sstream>

About::About(sf::Font &f) : font(f), scrollOffset(0.0f), maxScrollOffset(0.0f)
{
    // Titre
    titleText.setFont(font);
    titleText.setString("HIDE AND SEEK");
    titleText.setCharacterSize(55);
    titleText.setFillColor(Constants::COLOR_HIGH_LIGHT);
    titleText.setStyle(sf::Text::Bold);

    // Police de titre
    titleFont = font;
    titleText.setFont(titleFont);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition(
        Constants::WINDOW_WIDTH / 2 - titleBounds.width / 2,
        30);

    // Création des lignes d'information
    createInfoLines();

    // Texte de retour
    backText.setFont(font);
    backText.setString("Press ESCAPE to return to the menu");
    backText.setCharacterSize(22);
    backText.setFillColor(Constants::COLOR_HIGH_LIGHT);
    backText.setStyle(sf::Text::Italic);

    sf::FloatRect backBounds = backText.getLocalBounds();
    backText.setPosition(
        Constants::WINDOW_WIDTH / 2 - backBounds.width / 2,
        Constants::WINDOW_HEIGHT - 50);

    // Instruction de défilement
    scrollInstruction.setFont(font);
    scrollInstruction.setString("Use ARROWS or MOUSE to scroll");
    scrollInstruction.setCharacterSize(18);
    scrollInstruction.setFillColor(sf::Color(150, 150, 150));
    scrollInstruction.setPosition(Constants::WINDOW_WIDTH - 400, Constants::WINDOW_HEIGHT - 40);
}

void About::setTitleFont(sf::Font &newFont)
{
    titleFont = newFont;
    titleText.setFont(titleFont);

    // Recentrer
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition(
        Constants::WINDOW_WIDTH / 2 - titleBounds.width / 2,
        30);
}

void About::createInfoLines()
{
    std::vector<std::string> lines;

    lines.push_back("");
    lines.push_back("DESCRIPTION :");
    lines.push_back("An endless runner game where you must reach the bunker");
    lines.push_back("before the time runs out, while avoiding obstacles.");
    lines.push_back("");
    lines.push_back("___________________________________________________________");
    lines.push_back("");
    lines.push_back("HOW TO PLAY :");
    lines.push_back("");
    lines.push_back("   UP / SPACE           : Jump");
    lines.push_back("   DOWN                 : Crouch / Slide");
    lines.push_back("   P                    : Pause / Resume");
    lines.push_back("   ESCAPE               : Quit / Back to menu");
    lines.push_back("");
    lines.push_back("___________________________________________________________");
    lines.push_back("");
    lines.push_back("LIFE SYSTEM (3 HEARTS) :");
    lines.push_back("");
    lines.push_back("   Each collision with an obstacle makes you lose 1 heart.");
    lines.push_back("   Lose all your hearts and it's GAME OVER.");
    lines.push_back("");
    lines.push_back("___________________________________________________________");
    lines.push_back("");
    lines.push_back("PENALTIES PER COLLISION :");
    lines.push_back("");
    lines.push_back("   1st collision :");
    lines.push_back("      - Loss of 2 seconds on the timer");
    lines.push_back("      - Speed reduction (40%) for 2.5 seconds");
    lines.push_back("");
    lines.push_back("   2nd collision :");
    lines.push_back("      - Loss of 5 seconds on the timer");
    lines.push_back("      - Speed reduction (40%) for 2.5 seconds");
    lines.push_back("");
    lines.push_back("   3rd collision (last heart) :");
    lines.push_back("      - Loss of the last heart => GAME OVER");
    lines.push_back("");
    lines.push_back("___________________________________________________________");
    lines.push_back("");
    lines.push_back("OBJECTIVE :");
    lines.push_back("");
    lines.push_back("   Reach the bunker located at 3800 meters.");
    lines.push_back("   You have a total of 60 seconds.");
    lines.push_back("   Difficulty increases with distance traveled.");
    lines.push_back("");
    lines.push_back("___________________________________________________________");
    lines.push_back("");
    lines.push_back("DIFFICULTY :");
    lines.push_back("");
    lines.push_back("   The further you go, the more the speed increases.");
    lines.push_back("   Obstacles appear more frequently.");
    lines.push_back("");
    lines.push_back("___________________________________________________________");
    lines.push_back("");
    lines.push_back("OBSTACLES :");
    lines.push_back("");
    lines.push_back("   - Ground obstacles  : Jump over them");
    lines.push_back("   - Air obstacles     : Crouch to avoid them");
    lines.push_back("");
    lines.push_back("___________________________________________________________");
    lines.push_back("");
    lines.push_back("DEVELOPED BY :");
    lines.push_back("");
    lines.push_back(" Mohamed ");
    lines.push_back(" Aaissam ");
    lines.push_back("");

    float yPos = 130;
    for (const auto &line : lines)
    {
        sf::Text text;
        text.setFont(font);
        text.setString(line);
        text.setCharacterSize(22);

        if (line.find("DESCRIPTION") != std::string::npos ||
            line.find("HOW TO PLAY") != std::string::npos ||
            line.find("LIFE SYSTEM") != std::string::npos ||
            line.find("PENALTIES") != std::string::npos ||
            line.find("OBJECTIVE") != std::string::npos ||
            line.find("DIFFICULTY") != std::string::npos ||
            line.find("OBSTACLES") != std::string::npos ||
            line.find("DEVELOPED BY") != std::string::npos)
        {
            text.setFillColor(Constants::COLOR_HIGH_LIGHT);
            text.setStyle(sf::Text::Bold);
        }
        else if (line.find("1st collision") != std::string::npos ||
                 line.find("2nd collision") != std::string::npos ||
                 line.find("3rd collision") != std::string::npos)
        {
            text.setFillColor(sf::Color(255, 150, 100));
        }
        else if (line.find("- Loss of") != std::string::npos)
        {
            text.setFillColor(sf::Color(255, 100, 100));
        }
        else if (line.find("Speed reduction") != std::string::npos)
        {
            text.setFillColor(sf::Color(100, 200, 255));
        }
        else if (line.find("GAME OVER") != std::string::npos)
        {
            text.setFillColor(sf::Color::Red);
            text.setStyle(sf::Text::Bold);
        }
        else
        {
            text.setFillColor(Constants::COLOR_TEXT);
        }

        text.setPosition(80, yPos);
        infoLines.push_back(text);
        yPos += 30;
    }

    // Calcul du défilement maximum
    float lastY = yPos;
    float screenHeight = Constants::WINDOW_HEIGHT;
    maxScrollOffset = std::max(0.0f, lastY - screenHeight + 100);
}

void About::update()
{
    // Rien à mettre à jour pour l'instant
}

void About::draw(sf::RenderWindow &window)
{
    window.draw(titleText);

    // Affichage des lignes avec défilement
    for (auto &line : infoLines)
    {
        float newY = line.getPosition().y - scrollOffset;
        if (newY > 80 && newY < Constants::WINDOW_HEIGHT - 80)
        {
            line.setPosition(line.getPosition().x, newY);
            window.draw(line);
            // Remettre la position originale
            line.setPosition(line.getPosition().x, newY + scrollOffset);
        }
    }

    window.draw(backText);
    window.draw(scrollInstruction);
}

void About::handleInput(sf::Event &event, GameState &currentState)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            currentState = GameState::MENU;
        }
        else if (event.key.code == sf::Keyboard::Up)
        {
            scrollOffset -= 30;
            if (scrollOffset < 0)
                scrollOffset = 0;
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            scrollOffset += 30;
            if (scrollOffset > maxScrollOffset)
                scrollOffset = maxScrollOffset;
        }
    }
    else if (event.type == sf::Event::MouseWheelScrolled)
    {
        if (event.mouseWheelScroll.delta > 0)
        {
            scrollOffset -= 40;
            if (scrollOffset < 0)
                scrollOffset = 0;
        }
        else if (event.mouseWheelScroll.delta < 0)
        {
            scrollOffset += 40;
            if (scrollOffset > maxScrollOffset)
                scrollOffset = maxScrollOffset;
        }
    }
}

void About::reset()
{
    scrollOffset = 0.0f;
}