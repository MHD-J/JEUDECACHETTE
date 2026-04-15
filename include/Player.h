#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>

class Player
{
public:
    Player();
    void update(); // Met à jour la position et l'animation
    void jump();   // Fait sauter le joueur
    void crouch(); // Met le joueur en position accroupie
    void stand();  // Remet le joueur debout
    void die();    // Déclenche l'animation de mort
    void draw(sf::RenderWindow &window);

    // Gestion des collisions
    sf::FloatRect getBounds() const;          // Rectangle complet (visuel)
    sf::FloatRect getCollisionBounds() const; // Rectangle réduit (précis)

    void reset();                          // Réinitialise le joueur
    bool isDead() const;                   // Vérifie si le joueur est mort
    bool isDeathAnimationComplete() const; // Animation de mort terminée
    bool isCrouching() const;              // Vérifie si le joueur est accroupi

    float getX() const { return x; }
    float getY() const { return y; }

private:
    // ========== Position et dimensions ==========
    float x, y;                      // Position actuelle
    float normalY, slideY;           // Positions Y (debout / accroupi)
    float width, height;             // Dimensions actuelles
    float normalHeight, slideHeight; // Hauteurs (debout / accroupi)

    // ========== Physique ==========
    float velocityY; // Vitesse verticale
    float jumpForce; // Force du saut
    float gravity;   // Gravité
    float groundY;   // Position Y du sol

    // ========== États ==========
    bool grounded;               // Au sol ?
    bool crouching;              // Accroupi ?
    bool isJumping;              // En train de sauter ?
    bool dead;                   // Mort ?
    bool deathAnimationComplete; // Animation de mort terminée ?

    // ========== Mise à l'échelle des textures ==========
    float scaleX, scaleY;                          // Échelle normale
    float scaleSlideX, scaleSlideY;                // Échelle accroupi
    float originalWidth, originalHeight;           // Dimensions originales (debout)
    float slideOriginalWidth, slideOriginalHeight; // Dimensions originales (accroupi)

    // ========== Sprites et animations ==========
    sf::Sprite sprite;
    std::vector<sf::Texture> runTextures;   // Animation course
    std::vector<sf::Texture> idleTextures;  // Animation repos
    std::vector<sf::Texture> jumpTextures;  // Animation saut
    std::vector<sf::Texture> deadTextures;  // Animation mort
    std::vector<sf::Texture> slideTextures; // Animation glissade

    int currentFrame;  // Image actuelle
    float frameTime;   // Durée par image
    float elapsedTime; // Temps écoulé depuis dernière image
    float deathTimer;  // Temporisateur pour l'animation de mort

    // ========== Types d'animations ==========
    enum AnimState
    {
        IDLE,
        RUN,
        JUMP,
        DEAD,
        SLIDE
    };
    AnimState animState;

    void updateAnimation();             // Change l'image de l'animation
    void setAnimation(AnimState state); // Change le type d'animation
};

#endif