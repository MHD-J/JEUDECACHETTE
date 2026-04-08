#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>

class Player
{
public:
    Player();
    void update();
    void jump();
    void crouch();
    void stand();
    void die();
    void draw(sf::RenderWindow &window);
    sf::FloatRect getBounds() const;
    void reset();
    bool isDead() const;
    bool isDeathAnimationComplete() const;

private:
    // Position
    float x;
    float y;
    float normalY;
    float slideY;

    // Dimensions 
    float width;
    float height;
    float normalHeight;
    float slideHeight;

    // Physics
    float velocityY;
    float jumpForce;
    float gravity;
    float groundY;

    // States
    bool grounded;
    bool crouching;
    bool isJumping;
    bool dead;
    bool deathAnimationComplete;

    // Scale
    float scaleX;
    float scaleY;
    float scaleSlideX;
    float scaleSlideY;
    float originalWidth;
    float originalHeight;
    float slideOriginalWidth;
    float slideOriginalHeight;

    // Animation
    sf::Sprite sprite;
    std::vector<sf::Texture> runTextures;
    std::vector<sf::Texture> idleTextures;
    std::vector<sf::Texture> jumpTextures;
    std::vector<sf::Texture> deadTextures;
    std::vector<sf::Texture> slideTextures;

    int currentFrame;
    float frameTime;
    float elapsedTime;
    float deathTimer;

    enum AnimState
    {
        IDLE,
        RUN,
        JUMP,
        DEAD,
        SLIDE
    };
    AnimState animState;

    void updateAnimation();
    void setAnimation(AnimState state);
};

#endif