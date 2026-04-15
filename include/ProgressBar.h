#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <SFML/Graphics.hpp>

class ProgressBar
{
public:
    ProgressBar(sf::Font &font);
    void update(float distance);
    void draw(sf::RenderWindow &window);
    void reset();

private:
    sf::RectangleShape backgroundBar;
    sf::RectangleShape fillBar;
    sf::Text distanceText;

    float maxDistance;
    float currentDistance;
    float barWidth;
    float barHeight;
};

#endif