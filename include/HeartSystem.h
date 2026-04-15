#ifndef HEARTSYSTEM_H
#define HEARTSYSTEM_H

#include <SFML/Graphics.hpp>
#include <vector>

class HeartSystem
{
public:
    HeartSystem(sf::Font &font);
    void setHealth(int health);
    int getHealth() const { return currentHealth; }
    void decreaseHealth();
    void reset();
    void draw(sf::RenderWindow &window);
    bool isDead() const { return currentHealth <= 0; }

private:
    int currentHealth;
    int maxHealth;
    std::vector<sf::CircleShape> hearts;
    sf::Text healthText;

    void updateHearts();
};

#endif