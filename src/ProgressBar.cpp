#include "../include/ProgressBar.h"
#include "../include/Constants.h"

ProgressBar::ProgressBar(sf::Font &font)
{
    maxDistance = Constants::TOTAL_DISTANCE;
    currentDistance = 0;
    barWidth = Constants::PROGRESS_BAR_WIDTH;
    barHeight = Constants::PROGRESS_BAR_HEIGHT;

    // Background bar (gray)
    backgroundBar.setSize(sf::Vector2f(barWidth, barHeight));
    backgroundBar.setFillColor(sf::Color(50, 50, 50));
    backgroundBar.setPosition(
        Constants::PROGRESS_BAR_POSITION_X,
        Constants::PROGRESS_BAR_POSITION_Y);

    // Fill bar (golden orange)
    fillBar.setSize(sf::Vector2f(0, barHeight));
    fillBar.setFillColor(Constants::COLOR_PROGRESS);
    fillBar.setPosition(
        Constants::PROGRESS_BAR_POSITION_X,
        Constants::PROGRESS_BAR_POSITION_Y);

    // Distance text
    distanceText.setFont(font);
    distanceText.setCharacterSize(20);
    distanceText.setFillColor(Constants::COLOR_TEXT);
    distanceText.setString("Distance: 0%");

    sf::FloatRect textBounds = distanceText.getLocalBounds();
    distanceText.setPosition(
        Constants::WINDOW_WIDTH / 2 - textBounds.width / 2,
        Constants::PROGRESS_BAR_POSITION_Y - 25);
}

void ProgressBar::update(float distance)
{
    currentDistance = distance;
    if (currentDistance > maxDistance)
    {
        currentDistance = maxDistance;
    }

    // Calculate fill percentage
    float percentage = currentDistance / maxDistance;
    float fillWidth = barWidth * percentage;

    fillBar.setSize(sf::Vector2f(fillWidth, barHeight));

    // Update text
    int percent = (int)(percentage * 100);
    distanceText.setString("Distance: " + std::to_string(percent) + "%");

    // Center text
    sf::FloatRect textBounds = distanceText.getLocalBounds();
    distanceText.setPosition(
        Constants::WINDOW_WIDTH / 2 - textBounds.width / 2,
        Constants::PROGRESS_BAR_POSITION_Y - 25);
}

void ProgressBar::draw(sf::RenderWindow &window)
{
    window.draw(backgroundBar);
    window.draw(fillBar);
    window.draw(distanceText);
}

void ProgressBar::reset()
{
    currentDistance = 0;
    fillBar.setSize(sf::Vector2f(0, barHeight));
    distanceText.setString("Distance: 0%");
}