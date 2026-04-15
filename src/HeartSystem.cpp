#include "../include/HeartSystem.h"
#include "../include/Constants.h"

HeartSystem::HeartSystem(sf::Font &font)
{
    maxHealth = Constants::PLAYER_MAX_HEALTH;
    currentHealth = maxHealth;

    // Texte de la vie
    healthText.setFont(font);
    healthText.setCharacterSize(28);
    healthText.setFillColor(Constants::COLOR_TEXT);
    healthText.setString("HP:");
    healthText.setPosition(Constants::HEART_START_X - 60, Constants::HEART_START_Y + 5);

    updateHearts();
}

void HeartSystem::setHealth(int health)
{
    currentHealth = std::max(0, std::min(health, maxHealth));
    updateHearts();
}

void HeartSystem::decreaseHealth()
{
    if (currentHealth > 0)
    {
        currentHealth--;
        updateHearts();
    }
}

void HeartSystem::reset()
{
    currentHealth = maxHealth;
    updateHearts();
}

void HeartSystem::updateHearts()
{
    hearts.clear();

    for (int i = 0; i < maxHealth; i++)
    {
        sf::CircleShape heart(Constants::HEART_SIZE / 2);

        if (i < currentHealth)
        {
            // full heart
            heart.setFillColor(Constants::HEART_COLOR_FULL);
            heart.setOutlineColor(Constants::HEART_OUTLINE_COLOR);
            heart.setOutlineThickness(Constants::HEART_OUTLINE_THICKNESS);
        }
        else
        {
            // empty heart
            heart.setFillColor(Constants::HEART_COLOR_EMPTY);
            heart.setOutlineColor(Constants::HEART_OUTLINE_COLOR);
            heart.setOutlineThickness(Constants::HEART_OUTLINE_THICKNESS);
        }

        float x = Constants::HEART_START_X + i * (Constants::HEART_SIZE + Constants::HEART_SPACING);
        float y = Constants::HEART_START_Y;
        heart.setPosition(x, y);

        hearts.push_back(heart);
    }
}

void HeartSystem::draw(sf::RenderWindow &window)
{
    window.draw(healthText);
    for (auto &heart : hearts)
    {
        window.draw(heart);
    }
}