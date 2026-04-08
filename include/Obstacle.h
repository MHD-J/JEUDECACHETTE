#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Classe parente
class Obstacle {
protected:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    virtual ~Obstacle() {}
    bool load(const std::string& path, float x, float y);
    virtual void update(float dt) = 0;
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
};

// --- Obstacle 1 : Pierre (Statique) ---
class Pierre : public Obstacle {
public:
    Pierre(float x, float y);
    void update(float dt) override;
};

// --- Obstacle 2 : Mine (Statique / Danger) ---
class Mine : public Obstacle {
public:
    Mine(float x, float y);
    void update(float dt) override;
};

// --- Obstacle 3 : Oiseau (Mouvement sinusoïdal en haut) ---
class Oiseau : public Obstacle {
private:
    float speed;
    float startY;
    float timer;
public:
    Oiseau(float x, float y);
    void update(float dt) override;
};

// --- Obstacle 4 : Spider (Mouvement vertical / monte et descend) ---
class Spider : public Obstacle {
private:
    float startY;
    float range;
    float speed;
public:
    Spider(float x, float y);
    void update(float dt) override;
};

#endif