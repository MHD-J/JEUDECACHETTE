#include "../include/Obstacle.h"
#include <iostream>
#include <cmath>

// Méthodes communes
bool Obstacle::load(const std::string& path, float x, float y) {
    if (!texture.loadFromFile(path)) {
        std::cerr << "Erreur chargement : " << path << std::endl;
        return false;
    }
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    return true;
}

void Obstacle::draw(sf::RenderWindow& window) { window.draw(sprite); }
sf::FloatRect Obstacle::getBounds() const { return sprite.getGlobalBounds(); }

// --- PIERRE ---
Pierre::Pierre(float x, float y) { load("assets/textures/pierre.png", x, y); }
void Pierre::update(float dt) {} // Ne bouge pas

// --- MINE ---
Mine::Mine(float x, float y) { load("assets/textures/mine.png", x, y); }
void Mine::update(float dt) {
    // Optionnel : faire clignoter la mine
    static float t = 0; t += dt;
    sprite.setColor(sf::Color(255, 255, 255, 200 + 55 * std::sin(t * 5)));
}

// --- OISEAU ---
Oiseau::Oiseau(float x, float y) : speed(180.f), startY(y), timer(0.f) {
    load("assets/textures/oiseau.png", x, y);
}
void Oiseau::update(float dt) {
    timer += dt;
    // Avance horizontalement + ondule verticalement (sinus)
    float newY = startY + std::sin(timer * 3.0f) * 40.f;
    sprite.setPosition(sprite.getPosition().x + speed * dt, newY);
    
    if (sprite.getPosition().x > 1200) sprite.setPosition(-100, startY);
}

// --- SPIDER ---
Spider::Spider(float x, float y) : startY(y), range(150.f), speed(100.f) {
    load("assets/textures/spider.png", x, y);
}
void Spider::update(float dt) {
    // L'araignée descend et monte (va-et-vient vertical)
    static int direction = 1;
    sprite.move(0, speed * dt * direction);
    
    if (std::abs(sprite.getPosition().y - startY) > range) {
        direction *= -1; // Change de sens
    }
}