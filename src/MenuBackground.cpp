#include "../include/MenuBackground.h"
#include "../include/Constants.h"
#include <random>
#include <ctime>
#include <cmath>

MenuBackground::MenuBackground() : rng(std::time(0))
{
    createCircles();
}

void MenuBackground::createCircles()
{
    circles.clear();

    for (int i = 0; i < Constants::MENU_CIRCLES_COUNT; i++)
    {
        MovingCircle mc;

        // Taille aléatoire
        float radius = getRandom(Constants::MENU_CIRCLE_MIN_SIZE, Constants::MENU_CIRCLE_MAX_SIZE);
        mc.shape.setRadius(radius);

        // Position aléatoire
        float x = getRandom(0, Constants::WINDOW_WIDTH);
        float y = getRandom(0, Constants::WINDOW_HEIGHT);
        mc.shape.setPosition(x, y);

        // Couleur blanche avec transparence aléatoire
        int alpha = getRandomInt(Constants::MENU_CIRCLE_MIN_ALPHA, Constants::MENU_CIRCLE_MAX_ALPHA);
        mc.shape.setFillColor(sf::Color(255, 255, 255, alpha));
        mc.shape.setOutlineThickness(0);

        // Vitesse de déplacement aléatoire
        mc.speedX = getRandom(-Constants::MENU_CIRCLE_SPEED, Constants::MENU_CIRCLE_SPEED);
        mc.speedY = getRandom(-Constants::MENU_CIRCLE_SPEED, Constants::MENU_CIRCLE_SPEED);

        // Éviter les vitesses nulles
        if (mc.speedX == 0)
            mc.speedX = Constants::MENU_CIRCLE_SPEED * 0.5f;
        if (mc.speedY == 0)
            mc.speedY = Constants::MENU_CIRCLE_SPEED * 0.5f;

        mc.directionChangeTimer = getRandom(2.0f, 5.0f);

        circles.push_back(mc);
    }
}

sf::Color MenuBackground::getRandomColor()
{
    int alpha = getRandomInt(Constants::MENU_CIRCLE_MIN_ALPHA, Constants::MENU_CIRCLE_MAX_ALPHA);
    return sf::Color(255, 255, 255, alpha);
}

float MenuBackground::getRandom(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

int MenuBackground::getRandomInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

void MenuBackground::update(float dt)
{
    for (auto &mc : circles)
    {
        // Mise à jour de la position
        mc.shape.move(mc.speedX * dt, mc.speedY * dt);

        // Rebond sur les bords
        float x = mc.shape.getPosition().x;
        float y = mc.shape.getPosition().y;
        float radius = mc.shape.getRadius();

        if (x + radius * 2 > Constants::WINDOW_WIDTH || x < 0)
        {
            mc.speedX = -mc.speedX;
            // Remettre dans l'écran
            if (x < 0)
                mc.shape.setPosition(0, y);
            if (x + radius * 2 > Constants::WINDOW_WIDTH)
                mc.shape.setPosition(Constants::WINDOW_WIDTH - radius * 2, y);
        }

        if (y + radius * 2 > Constants::WINDOW_HEIGHT || y < 0)
        {
            mc.speedY = -mc.speedY;
            if (y < 0)
                mc.shape.setPosition(x, 0);
            if (y + radius * 2 > Constants::WINDOW_HEIGHT)
                mc.shape.setPosition(x, Constants::WINDOW_HEIGHT - radius * 2);
        }

        // Changement de direction périodique
        mc.directionChangeTimer -= dt;
        if (mc.directionChangeTimer <= 0)
        {
            mc.speedX += getRandom(-5.0f, 5.0f);
            mc.speedY += getRandom(-5.0f, 5.0f);

            // Limiter la vitesse
            float maxSpeed = Constants::MENU_CIRCLE_SPEED * 1.5f;
            if (mc.speedX > maxSpeed)
                mc.speedX = maxSpeed;
            if (mc.speedX < -maxSpeed)
                mc.speedX = -maxSpeed;
            if (mc.speedY > maxSpeed)
                mc.speedY = maxSpeed;
            if (mc.speedY < -maxSpeed)
                mc.speedY = -maxSpeed;

            mc.directionChangeTimer = getRandom(2.0f, 5.0f);
        }
    }
}

void MenuBackground::draw(sf::RenderWindow &window)
{
    for (auto &mc : circles)
    {
        window.draw(mc.shape);
    }
}

void MenuBackground::reset()
{
    createCircles();
}