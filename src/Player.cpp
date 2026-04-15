#include "../include/Player.h"
#include "../include/Constants.h"
#include <iostream>

// --------------------------------
// Constructeur : charge les textures et initialise
// --------------------------------
Player::Player()
{
    // Position de départ
    x = 200.0f;
    width = Constants::PLAYER_WIDTH;
    normalHeight = Constants::PLAYER_HEIGHT;
    slideHeight = Constants::PLAYER_CROUCH_HEIGHT;
    height = normalHeight;

    // Paramètres physiques
    jumpForce = Constants::PLAYER_JUMP_FORCE;
    gravity = Constants::PLAYER_GRAVITY;
    groundY = Constants::GROUND_Y;
    velocityY = 0.0f;

    // Positions Y selon l'état
    normalY = groundY - normalHeight;
    slideY = groundY - slideHeight +30.0f;
    y = normalY;

    // États initiaux
    grounded = true;
    crouching = false;
    isJumping = false;
    dead = false;
    deathAnimationComplete = false;
    deathTimer = 0.0f;

    // ========== Chargement des textures ==========

    // Animation de course (14 images)
    for (int i = 1; i <= 14; i++)
    {
        sf::Texture tex;
        if (!tex.loadFromFile("assets/images/Run (" + std::to_string(i) + ").png"))
            std::cout << "Erreur: Run " << i << std::endl;
        runTextures.push_back(tex);
    }

    // Animation de repos 
    for (int i = 1; i <= 3; i++)
    {
        sf::Texture tex;
        if (!tex.loadFromFile("assets/images/Idle (" + std::to_string(i) + ").png"))
            std::cout << "Erreur: Idle " << i << std::endl;
        idleTextures.push_back(tex);
    }

    // Animation de saut 
    for (int i = 1; i <= 15; i++)
    {
        sf::Texture tex;
        if (!tex.loadFromFile("assets/images/Jump (" + std::to_string(i) + ").png"))
            std::cout << "Erreur: Jump " << i << std::endl;
        jumpTextures.push_back(tex);
    }

    // Animation de mort 
    for (int i = 1; i <= 14; i++)
    {
        sf::Texture tex;
        if (!tex.loadFromFile("assets/images/Dead (" + std::to_string(i) + ").png"))
            std::cout << "Erreur: Dead " << i << std::endl;
        deadTextures.push_back(tex);
    }

    // Animation de glissade 
    for (int i = 1; i <= 2; i++)
    {
        sf::Texture tex;
        if (!tex.loadFromFile("assets/images/sp" + std::to_string(i) + ".png"))
            std::cout << "Erreur: Slide " << i << std::endl;
        slideTextures.push_back(tex);
    }

    // Calcul des échelles pour l'affichage
    if (!runTextures.empty())
    {
        originalWidth = runTextures[0].getSize().x;
        originalHeight = runTextures[0].getSize().y;
        scaleX = Constants::PLAYER_WIDTH / originalWidth;
        scaleY = Constants::PLAYER_HEIGHT / originalHeight;
        sprite.setTexture(runTextures[0]);
        sprite.setScale(scaleX, scaleY);
    }

    if (!slideTextures.empty())
    {
        slideOriginalWidth = slideTextures[0].getSize().x;
        slideOriginalHeight = slideTextures[0].getSize().y;
        scaleSlideX = Constants::PLAYER_WIDTH / slideOriginalWidth;
        scaleSlideY = Constants::PLAYER_CROUCH_HEIGHT / slideOriginalHeight;
    }

    // Paramètres d'animation
    currentFrame = 0;
    frameTime = 0.08f;
    elapsedTime = 0.0f;
    animState = RUN;

    sprite.setPosition(x, y);
}

// --------------------------------
// Rectangle de collision réduit 
// --------------------------------
sf::FloatRect Player::getCollisionBounds() const
{
    float cx, cy, cw, ch;
    float shrinkX, shrinkY;

    if (crouching)
    {
        shrinkX = Constants::PLAYER_WIDTH * 0.25f;
        shrinkY = Constants::PLAYER_CROUCH_HEIGHT * 0.20f;
        cx = x + shrinkX / 2;
        cy = slideY + shrinkY / 2;
        cw = Constants::PLAYER_WIDTH - shrinkX;
        ch = Constants::PLAYER_CROUCH_HEIGHT - shrinkY;
    }
    else
    {
        shrinkX = Constants::PLAYER_WIDTH * 0.25f;
        shrinkY = Constants::PLAYER_HEIGHT * 0.20f;
        cx = x + shrinkX / 2;
        cy = y + shrinkY / 2;
        cw = Constants::PLAYER_WIDTH - shrinkX;
        ch = Constants::PLAYER_HEIGHT - shrinkY;
    }

    return sf::FloatRect(cx, cy, cw, ch);
}

// -------------------------------- Rectangle complet --------------------------------
sf::FloatRect Player::getBounds() const
{
    return sprite.getGlobalBounds();
}

// -------------------------------- Vérifie si le joueur est accroupi --------------------------------
bool Player::isCrouching() const
{
    return crouching;
}

// -------------------------------- Met à jour la physique et l'animation --------------------------------
void Player::update()
{
    // Gestion de l'animation de mort
    if (dead)
    {
        deathTimer += 1.0f / 60.0f;
        if (deathTimer >= 0.12f)
        {
            deathTimer = 0;
            currentFrame++;
            if (currentFrame >= (int)deadTextures.size())
            {
                currentFrame = (int)deadTextures.size() - 1;
                deathAnimationComplete = true;
            }
            if (currentFrame < (int)deadTextures.size())
            {
                sprite.setTexture(deadTextures[currentFrame]);
                sprite.setScale(scaleX, scaleY);
            }
        }
        return;
    }

    // Application de la gravité (sauf si accroupi)
    if (!crouching)
    {
        velocityY += gravity;
        y += velocityY;
    }

    // Collision avec le sol
    if (crouching)
    {
        if (y >= slideY)
        {
            y = slideY;
            velocityY = 0;
            grounded = true;
            isJumping = false;
        }
        else
        {
            grounded = false;
        }
    }
    else
    {
        if (y >= normalY)
        {
            y = normalY;
            velocityY = 0;
            grounded = true;
            isJumping = false;
        }
        else
        {
            grounded = false;
        }
    }

    // Changement d'animation selon l'état
    if (!grounded && isJumping)
    {
        if (animState != JUMP)
            setAnimation(JUMP);
    }
    else if (!crouching)
    {
        if (animState != RUN)
            setAnimation(RUN);
    }

    // Mise à jour de l'image de l'animation
    elapsedTime += 1.0f / 60.0f;
    if (elapsedTime >= frameTime)
    {
        elapsedTime = 0;
        currentFrame++;
        updateAnimation();
    }

    sprite.setPosition(x, y);
}

// --------------------------------  Fait sauter le joueur---------------
void Player::jump()
{
    if (grounded && !crouching && !dead)
    {
        velocityY = jumpForce;
        grounded = false;
        isJumping = true;
        setAnimation(JUMP);
        currentFrame = 0;
    }
}

// --------------------------------
// Met le joueur en position accroupie
// --------------------------------
void Player::crouch()
{
    if (!crouching && grounded && !dead)
    {
        crouching = true;
        height = slideHeight;
        y = slideY;
        setAnimation(SLIDE);
        currentFrame = 0;
        sprite.setPosition(x, y);
    }
}

// --------------------------------
// Remet le joueur debout
// --------------------------------
void Player::stand()
{
    if (crouching && !dead)
    {
        crouching = false;
        height = normalHeight;
        y = normalY;
        if (!runTextures.empty())
        {
            sprite.setTexture(runTextures[0]);
            sprite.setScale(scaleX, scaleY);
        }
        setAnimation(RUN);
        currentFrame = 0;
        sprite.setPosition(x, y);
    }
}

// --------------------------------
// Déclenche l'animation de mort
// --------------------------------
void Player::die()
{
    if (!dead)
    {
        dead = true;
        deathAnimationComplete = false;
        currentFrame = 0;
        deathTimer = 0;
        setAnimation(DEAD);
    }
}

// --------------------------------
// Affiche le joueur
// --------------------------------
void Player::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

// --------------------------------
// Réinitialise toutes les valeurs
// --------------------------------
void Player::reset()
{
    crouching = false;
    dead = false;
    deathAnimationComplete = false;
    deathTimer = 0;
    height = normalHeight;
    y = normalY;
    velocityY = 0.0f;
    grounded = true;
    isJumping = false;

    if (!runTextures.empty())
    {
        sprite.setTexture(runTextures[0]);
        sprite.setScale(scaleX, scaleY);
    }
    setAnimation(RUN);
    currentFrame = 0;
    sprite.setPosition(x, y);
}

// -------------------------------- Accesseurs --------------------------------
bool Player::isDead() const { return dead; }
bool Player::isDeathAnimationComplete() const { return deathAnimationComplete; }

// --------------------------------  Change l'image de l'animation courante  --------------------------------
void Player::updateAnimation()
{
    switch (animState)
    {
    case IDLE:
        if (currentFrame >= (int)idleTextures.size())
            currentFrame = 0;
        if (!idleTextures.empty())
        {
            sprite.setTexture(idleTextures[currentFrame]);
            sprite.setScale(scaleX, scaleY);
        }
        break;

    case RUN:
        if (currentFrame >= (int)runTextures.size())
            currentFrame = 0;
        if (!runTextures.empty())
        {
            sprite.setTexture(runTextures[currentFrame]);
            sprite.setScale(scaleX, scaleY);
        }
        break;

    case JUMP:
        if (currentFrame >= (int)jumpTextures.size())
            currentFrame = (int)jumpTextures.size() - 1;
        if (!jumpTextures.empty())
        {
            sprite.setTexture(jumpTextures[currentFrame]);
            sprite.setScale(scaleX, scaleY);
        }
        break;

    case DEAD:
        // Géré dans update()
        break;

    case SLIDE:
        if (currentFrame >= (int)slideTextures.size())
            currentFrame = (int)slideTextures.size() - 1;
        if (!slideTextures.empty())
        {
            sprite.setTexture(slideTextures[currentFrame]);
            sprite.setScale(scaleSlideX, scaleSlideY);
        }
        break;

    default:
        break;
    }
}

// --------------------------------  Change le type d'animation  --------------------------------
void Player::setAnimation(AnimState state)
{
    if (animState == state)
        return;
    animState = state;
    currentFrame = 0;
}