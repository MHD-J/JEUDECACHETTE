#ifndef MENUBACKGROUND_H
#define MENUBACKGROUND_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

struct MovingCircle
{
    sf::CircleShape shape;
    float speedX;
    float speedY;
    float directionChangeTimer;
};

class MenuBackground
{
public:
    MenuBackground();
    void update(float dt);
    void draw(sf::RenderWindow &window);
    void reset();

private:
    std::vector<MovingCircle> circles;
    std::mt19937 rng;

    void createCircles();
    sf::Color getRandomColor();
    float getRandom(float min, float max);
    int getRandomInt(int min, int max);
};

#endif