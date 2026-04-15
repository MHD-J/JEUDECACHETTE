#include "../include/Collision.h"

bool checkCollision(const sf::FloatRect &rect1, const sf::FloatRect &rect2)
{
    return rect1.intersects(rect2);
}

bool checkCollisionShrunk(const sf::FloatRect &rect1, const sf::FloatRect &rect2,
                          float shrinkFactor1X, float shrinkFactor1Y,
                          float shrinkFactor2X, float shrinkFactor2Y)
{
    // Réduire le premier rectangle
    sf::FloatRect shrunk1(
        rect1.left + (rect1.width * shrinkFactor1X / 2),
        rect1.top + (rect1.height * shrinkFactor1Y / 2),
        rect1.width * (1 - shrinkFactor1X),
        rect1.height * (1 - shrinkFactor1Y));

    // Réduire le deuxième rectangle
    sf::FloatRect shrunk2(
        rect2.left + (rect2.width * shrinkFactor2X / 2),
        rect2.top + (rect2.height * shrinkFactor2Y / 2),
        rect2.width * (1 - shrinkFactor2X),
        rect2.height * (1 - shrinkFactor2Y));

    return shrunk1.intersects(shrunk2);
}