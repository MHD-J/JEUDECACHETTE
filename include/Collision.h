#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include "../include/Obstacle.h"

class Collision {
public:
    // Fonction qui renvoie VRAI si le joueur touche un obstacle
    static bool checkCollision(const sf::Sprite& player, Obstacle* obstacle) {
        return player.getGlobalBounds().intersects(obstacle->getBounds());
    }
};

#endif