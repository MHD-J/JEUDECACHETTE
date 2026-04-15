#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>

// Collision standard
bool checkCollision(const sf::FloatRect &rect1, const sf::FloatRect &rect2);

// Collision avec facteur de réduction personnalisé
bool checkCollisionShrunk(const sf::FloatRect &rect1, const sf::FloatRect &rect2,
                          float shrinkFactor1X, float shrinkFactor1Y,
                          float shrinkFactor2X, float shrinkFactor2Y);

#endif