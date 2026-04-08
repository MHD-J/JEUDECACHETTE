#include "../include/Player.h"
#include "../include/Constants.h"
#include <iostream>

Player::Player()
{
    // Position
    x = 200.0f;

    // Dimensions 
    width = Constants::PLAYER_WIDTH;
    normalHeight = Constants::PLAYER_HEIGHT;
    slideHeight = 200.0f; 
    height = normalHeight;

    // Physics
    jumpForce = Constants::PLAYER_JUMP_FORCE;
    gravity = Constants::PLAYER_GRAVITY;
    groundY = Constants::GROUND_Y;
    velocityY = 0.0f;

    // Positions
    normalY = groundY - normalHeight;
    slideY = normalY + 38;            
    y = normalY;

    // States
    grounded = true;
    crouching = false;
    isJumping = false;
    dead = false;
    deathAnimationComplete = false;
    deathTimer = 0.0f;

    // Run animation
    std::cout << "Loading Run textures..." << std::endl;
    for (int i = 1; i <= 14; i++)
    {
        sf::Texture tex;
        std::string path = "assets/images/Run (" + std::to_string(i) + ").png";
        if (!tex.loadFromFile(path))
        {
            std::cout << "Failed to load: " << path << std::endl;
        }
        runTextures.push_back(tex);
    }
    std::cout << "Loaded " << runTextures.size() << " run textures" << std::endl;

    // Idle animation
    std::cout << "Loading Idle textures..." << std::endl;
    for (int i = 1; i <= 3; i++)
    {
        sf::Texture tex;
        std::string path = "assets/images/Idle (" + std::to_string(i) + ").png";
        if (!tex.loadFromFile(path))
        {
            std::cout << "Failed to load: " << path << std::endl;
        }
        idleTextures.push_back(tex);
    }
    std::cout << "Loaded " << idleTextures.size() << " idle textures" << std::endl;

    // Jump animation
    std::cout << "Loading Jump textures..." << std::endl;
    for (int i = 1; i <= 15; i++)
    {
        sf::Texture tex;
        std::string path = "assets/images/Jump (" + std::to_string(i) + ").png";
        if (!tex.loadFromFile(path))
        {
            std::cout << "Failed to load: " << path << std::endl;
        }
        jumpTextures.push_back(tex);
    }
    std::cout << "Loaded " << jumpTextures.size() << " jump textures" << std::endl;

    // Death animation
    std::cout << "Loading Dead textures..." << std::endl;
    for (int i = 1; i <= 14; i++)
    {
        sf::Texture tex;
        std::string path = "assets/images/Dead (" + std::to_string(i) + ").png";
        if (!tex.loadFromFile(path))
        {
            std::cout << "Failed to load: " << path << std::endl;
        }
        deadTextures.push_back(tex);
    }
    std::cout << "Loaded " << deadTextures.size() << " dead textures" << std::endl;

    // Slide animation
    std::cout << "Loading Slide textures..." << std::endl;
    for (int i = 1; i <= 2; i++)
    {
        sf::Texture tex;
        std::string path = "assets/images/sp" + std::to_string(i) + ".png";
        if (!tex.loadFromFile(path))
        {
            std::cout << "Failed to load: " << path << std::endl;
        }
        slideTextures.push_back(tex);
    }
    std::cout << "Loaded " << slideTextures.size() << " slide textures" << std::endl;

    // 
    if (!runTextures.empty())
    {
        originalWidth = runTextures[0].getSize().x;
        originalHeight = runTextures[0].getSize().y;
        scaleX = Constants::PLAYER_WIDTH / originalWidth;
        scaleY = Constants::PLAYER_HEIGHT / originalHeight;

        sprite.setScale(scaleX, scaleY);
        sprite.setTexture(runTextures[0]);
    }

    //scale for slide textures 
    if (!slideTextures.empty())
    {
        slideOriginalWidth = slideTextures[0].getSize().x;
        slideOriginalHeight = slideTextures[0].getSize().y;
        scaleSlideX = 140.0f / slideOriginalWidth;  
        scaleSlideY = 180.0f / slideOriginalHeight;  

        std::cout << "Slide scale: " << scaleSlideX << ", " << scaleSlideY << std::endl;
    }

    // Animation setup
    currentFrame = 0;
    frameTime = 0.08f;
    elapsedTime = 0;
    animState = RUN;

    sprite.setPosition(x, y);
}

void Player::update()
{
    if (dead)
    {
        // Death animation
        deathTimer += 1.0f / 60.0f;

        if (deathTimer >= 0.12f)
        {
            deathTimer = 0;
            currentFrame++;

            if (currentFrame >= (int)deadTextures.size())
            {
                currentFrame = deadTextures.size() - 1;
                deathAnimationComplete = true;
            }

            if (currentFrame < (int)deadTextures.size() && !deadTextures.empty())
            {
                sprite.setTexture(deadTextures[currentFrame]);
                sprite.setScale(scaleX, scaleY);
            }
        }
        return;
    }

    // Apply gravity if not crouching
    if (!crouching)
    {
        velocityY += gravity;
        y += velocityY;
    }

    // Ground collision
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

    // Update animation based on state
    if (!grounded && isJumping)
    {
        if (animState != JUMP)
            setAnimation(JUMP);
    }
    else if (crouching)
    {
        // Keep SLIDE animation
    }
    else
    {
        if (animState != RUN)
            setAnimation(RUN);
    }

    // Update animation frame
    if (!dead)
    {
        elapsedTime += 1.0f / 60.0f;
        if (elapsedTime >= frameTime)
        {
            elapsedTime = 0;
            currentFrame++;
            updateAnimation();
        }
    }

    // Update sprite position
    sprite.setPosition(x, y);
}

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

void Player::stand()
{
    if (crouching && !dead)
    {
        crouching = false;
        height = normalHeight;
        y = normalY;
        setAnimation(RUN);
        currentFrame = 0;
        
        if (!runTextures.empty())
        {
            sprite.setTexture(runTextures[0]);
            sprite.setScale(scaleX, scaleY);
        }
        sprite.setPosition(x, y);
    }
}

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

void Player::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

sf::FloatRect Player::getBounds() const
{
    return sprite.getGlobalBounds();
}

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

    // Restore normal scale and texture
    if (!runTextures.empty())
    {
        sprite.setTexture(runTextures[0]);
        sprite.setScale(scaleX, scaleY);
    }

    setAnimation(RUN);
    currentFrame = 0;
    sprite.setPosition(x, y);
}

bool Player::isDead() const
{
    return dead;
}

bool Player::isDeathAnimationComplete() const
{
    return deathAnimationComplete;
}

void Player::updateAnimation()
{
    switch (animState)
    {
    case IDLE:
        if (currentFrame >= (int)idleTextures.size())
            currentFrame = 0;
        if (currentFrame < (int)idleTextures.size() && !idleTextures.empty())
        {
            sprite.setTexture(idleTextures[currentFrame]);
            sprite.setScale(scaleX, scaleY);
        }
        break;

    case RUN:
        if (currentFrame >= (int)runTextures.size())
            currentFrame = 0;
        if (currentFrame < (int)runTextures.size() && !runTextures.empty())
        {
            sprite.setTexture(runTextures[currentFrame]);
            sprite.setScale(scaleX, scaleY);
        }
        break;

    case JUMP:
        if (currentFrame >= (int)jumpTextures.size())
        {
            currentFrame = jumpTextures.size() - 1;
        }
        if (currentFrame < (int)jumpTextures.size() && !jumpTextures.empty())
        {
            sprite.setTexture(jumpTextures[currentFrame]);
            sprite.setScale(scaleX, scaleY);
        }
        break;

    case DEAD:
        // Handled in update()
        break;

    case SLIDE:
        if (currentFrame >= (int)slideTextures.size())
        {
            currentFrame = slideTextures.size() - 1;
        }
        if (currentFrame < (int)slideTextures.size() && !slideTextures.empty())
        {
            sprite.setTexture(slideTextures[currentFrame]);
            sprite.setScale(scaleSlideX, scaleSlideY); // 140x200
        }
        break;

    default:
        break;
    }
}

void Player::setAnimation(AnimState state)
{
    if (animState == state)
        return;
    animState = state;
    currentFrame = 0;
}