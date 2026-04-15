#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Obstacle
{
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float x;
    float y;
    static float currentSpeed;

public:
    virtual ~Obstacle() {}
    virtual void update(float dt) = 0;
    void draw(sf::RenderWindow &window);

    static void setSpeed(float speed) { currentSpeed = speed; }
    static float getSpeed() { return currentSpeed; }
    sf::FloatRect getBounds() const;
    sf::FloatRect getCollisionBounds() const;

    bool isOffScreen() const;
    void setPosition(float px, float py);
    float getX() const;

    virtual bool isAir() const { return false; }
};

class GroundObstacle : public Obstacle
{
public:
    GroundObstacle(float x, float y, int type);
    void update(float dt) override;
    bool isAir() const override { return false; }
};

class AirObstacle : public Obstacle
{
public:
    AirObstacle(float x, float y);
    void update(float dt) override;
    bool isAir() const override { return true; }

private:
    float timer;
    float startY;
};

#endif