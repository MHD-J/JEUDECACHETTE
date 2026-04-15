#include "../include/Obstacle.h"
#include "../include/Constants.h"
#include <iostream>
#include <cmath>

float Obstacle::currentSpeed = 6.0f;
void Obstacle::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

sf::FloatRect Obstacle::getBounds() const
{
    return sprite.getGlobalBounds();
}

// COLLISION BOUNDS CORRIGÉE - Réduction beaucoup plus agressive
sf::FloatRect Obstacle::getCollisionBounds() const
{
    sf::FloatRect full = sprite.getGlobalBounds();

    // Réduction de 40% horizontale et 35% verticale pour éviter les collisions fantômes
    float shrinkX = full.width * 0.40f;
    float shrinkY = full.height * 0.35f;

    return sf::FloatRect(
        full.left + shrinkX / 2,
        full.top + shrinkY / 2,
        full.width - shrinkX,
        full.height - shrinkY);
}

bool Obstacle::isOffScreen() const
{
    return (sprite.getPosition().x + Constants::OBSTACLE_WIDTH < 0);
}

void Obstacle::setPosition(float px, float py)
{
    x = px;
    y = py;
    sprite.setPosition(x, y);
}

float Obstacle::getX() const
{
    return sprite.getPosition().x;
}

GroundObstacle::GroundObstacle(float x, float y, int type)
{
    std::string path;
    switch (type)
    {
    case 1:
        path = "assets/images/obstacle1.png";
        break;
    case 2:
        path = "assets/images/obstacle2.png";
        break;
    case 3:
        path = "assets/images/obstacle3.png";
        break;
    default:
        path = "assets/images/obstacle2.png";
        break;
    }

    if (!texture.loadFromFile(path))
    {
        std::cout << "Failed to load: " << path << std::endl;
    }

    sprite.setTexture(texture);

    float scaleX = Constants::OBSTACLE_WIDTH / texture.getSize().x;
    float scaleY = Constants::OBSTACLE_HEIGHT / texture.getSize().y;
    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(x, y);
}

void GroundObstacle::update(float dt)
{
    sprite.move(-Obstacle::currentSpeed, 0);
}

AirObstacle::AirObstacle(float x, float y) : timer(0), startY(y)
{
    std::string path = "assets/images/drone.png";

    if (!texture.loadFromFile(path))
    {
        std::cout << "Failed to load: " << path << std::endl;
    }

    sprite.setTexture(texture);

    float scaleX = Constants::AIR_OBSTACLE_WIDTH / texture.getSize().x;
    float scaleY = Constants::AIR_OBSTACLE_HEIGHT / texture.getSize().y;
    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(x, y);
}

void AirObstacle::update(float dt)
{
    timer += dt;

    float newY = startY + std::sin(timer * 2.5f) * 12.0f;

    sprite.setPosition(
        sprite.getPosition().x - Obstacle::currentSpeed,
        newY);
}