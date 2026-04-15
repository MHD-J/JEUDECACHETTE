#include "../include/Game.h"
#include "../include/Constants.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

//--------------------------------
// Constructeur : initialise tous les composants
//--------------------------------
Game::Game(sf::RenderWindow &w, sf::Font &f)
    : window(w), font(f), menu(f), about(f), progressBar(f),
    gameOverScreen(f), heartSystem(f), pauseMenu(f)
{
    // window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    srand(time(0)); // Initialisation du générateur aléatoire pour les obstacles

    // Initialisation des polices
    titleFont = f; 
    textFont = f;

    currentState = GameState::MENU;
    isPaused = false;
    baseBgSpeed = Constants::BACKGROUND_SPEED;
    bgSpeed = baseBgSpeed;
    highScore = 0;

    // Initialisation du joueur et du chronomètre
    player = Player();
    timer = Timer();
    timer.setFont(font);

    // Chargement du high score depuis le fichier
    loadHighScore();

    // Chargement de la texture du fond
    if (!backgroundTexture.loadFromFile(Constants::BACKGROUND_IMAGE))
    {
        std::cout << "Impossible de charger l'image de fond" << std::endl;
    }

    background1.setTexture(backgroundTexture);
    background2.setTexture(backgroundTexture);
    float imgWidth = backgroundTexture.getSize().x;
    background1.setPosition(0, 0);
    background2.setPosition(imgWidth, 0);

    // Chargement du bunker
    if (!bunkerTexture.loadFromFile(Constants::BUNKER_IMAGE))
    {
        std::cout << "Impossible de charger l'image du bunker" << std::endl;
    }

    bunkerSprite.setTexture(bunkerTexture);
    float scaleX = Constants::BUNKER_WIDTH / bunkerTexture.getSize().x;
    float scaleY = Constants::BUNKER_HEIGHT / bunkerTexture.getSize().y;
    bunkerSprite.setScale(scaleX, scaleY);
    bunkerX = Constants::BUNKER_X;
    bunkerSprite.setPosition(bunkerX, Constants::BUNKER_Y);

    totalDistance = Constants::TOTAL_DISTANCE;
    currentDistance = 0;
    spawnTimer = 0;
    spawnDelay = Constants::BASE_SPAWN_DELAY;

    canTakeDamage = true;

    // Initialisation des variables de difficulté
    speedPenaltyTimer = 0.0f;
    originalBgSpeed = baseBgSpeed;
    isPenaltyActive = false;
    difficultyProgress = 0.0f;
    hitCount = 0;

    // Initialisation des variables de notification
    notificationText.setFont(font);
    notificationText.setCharacterSize(Constants::NOTIFICATION_SIZE);
    notificationText.setFillColor(sf::Color::Red);
    notificationText.setStyle(sf::Text::Bold);
    notificationTimer = 0.0f;
    showNotification = false;
}

//--------------------------------
// Boucle principale du jeu
//--------------------------------
void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();
        update();
        render();
    }
}

//--------------------------------
// Démarre une nouvelle partie
//--------------------------------
void Game::startGame()
{
    resetGame();
    timer.start();
    isPaused = false; // Réinitialiser l'état de pause
    currentState = GameState::PLAYING;
}

//--------------------------------
// Change l'état du jeu (MENU, PLAYING,...)
//--------------------------------
void Game::changeState(GameState newState)
{
    currentState = newState;
}

//--------------------------------
// Réinitialise complètement la partie
//--------------------------------
void Game::resetGame()
{
    player.reset();
    timer.reset();
    heartSystem.reset();
    canTakeDamage = true;

    bgSpeed = baseBgSpeed;
    spawnDelay = Constants::BASE_SPAWN_DELAY;
    Obstacle::setSpeed(bgSpeed); // Synchronisation obstacle/fond

    float imgWidth = backgroundTexture.getSize().x;
    background1.setPosition(0, 0);
    background2.setPosition(imgWidth, 0);
    bunkerSprite.setPosition(bunkerX, Constants::BUNKER_Y);

    currentDistance = 0;
    progressBar.reset();

    obstacles.clear();
    spawnTimer = 0;

    menu.reset();
    gameOverScreen.reset();
    pauseMenu.reset();

    // Initialisation des variables de difficulté
    speedPenaltyTimer = 0.0f;
    isPenaltyActive = false;
    bgSpeed = baseBgSpeed;
    originalBgSpeed = baseBgSpeed;
    difficultyProgress = 0.0f;
    hitCount = 0;

    // Initialisation des variables de notification
    notificationTimer = 0.0f;
    showNotification = false;
}

//--------------------------------
// Gestion des événements (clavier, souris)
//--------------------------------
void Game::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        // Touche Échap : retour au menu ou fermeture
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            if (currentState == GameState::PLAYING)
            {
                // isPaused = false; 
                currentState = GameState::MENU;
            }
            else if (currentState == GameState::MENU)
            {
                window.close();
            }
            else if (currentState == GameState::ABOUT)
            {
                currentState = GameState::MENU;
            }
        }

        // -------------- État MENU --------------
        if (currentState == GameState::MENU)
        {
            menu.handleInput(event, currentState, window);
            if (currentState == GameState::PLAYING)
            {
                startGame();
            }
        }
        // -------------- État ABOUT --------------
        else if (currentState == GameState::ABOUT)
        {
            about.handleInput(event, currentState);
        }
        // -------------- État PLAYING --------------
        else if (currentState == GameState::PLAYING)
        {
            // -------------- Gestion de la touche P  --------------
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
            {
                isPaused = !isPaused;
            }

            // -------------- Commandes du joueur si !isPaused --------------
            if (!isPaused)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Space ||
                        event.key.code == sf::Keyboard::Up)
                    {
                        player.jump();
                    }
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        player.crouch();
                    }
                }
                if (event.type == sf::Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        player.stand();
                    }
                }
            }
            // -------------- Menu pause (seulement si pausé => Tap P) --------------
            else
            {
                pauseMenu.handleInput(event, isPaused, currentState, this);
            }
        }

        // -------------- État GAME_OVER ou VICTORY --------------
        else if (currentState == GameState::GAME_OVER || currentState == GameState::VICTORY)
        {
            bool shouldReset = false;
            gameOverScreen.handleInput(event, currentState, shouldReset);
            if (shouldReset)
            {
                if (currentState == GameState::PLAYING)
                {
                    startGame();
                }
                else if (currentState == GameState::MENU)
                {
                    resetGame();
                }
            }
        }
    }
}

//--------------------------------
// Vérifie la collision avec le bunker
//--------------------------------
bool Game::checkBunkerCollision()
{
    sf::FloatRect playerBounds = player.getCollisionBounds();
    sf::FloatRect bunkerBounds = bunkerSprite.getGlobalBounds();

    float shrinkX = bunkerBounds.width * Constants::BUNKER_COLLISION_SHRINK;
    float shrinkY = bunkerBounds.height * Constants::BUNKER_COLLISION_SHRINK;

    sf::FloatRect shrunkBunker(
        bunkerBounds.left + shrinkX / 2,
        bunkerBounds.top + shrinkY / 2,
        bunkerBounds.width - shrinkX,
        bunkerBounds.height - shrinkY);

    return playerBounds.intersects(shrunkBunker);
}

//--------------------------------
// Empêche les obstacles d'apparaître trop proches
//--------------------------------
bool Game::checkObstacleDistance()
{
    if (obstacles.empty())
        return true;

    float lastObstacleX = obstacles.back()->getX();
    return (lastObstacleX < Constants::WINDOW_WIDTH - 400);
}

//--------------------------------
// Augmente la difficulté (vitesse + spawn)
//--------------------------------
void Game::updateDifficulty()
{
    float progress = currentDistance / totalDistance;

    // Difficulté plus rapide et visible
    if (progress < Constants::DIFFICULTY_START_PROGRESS)
        difficultyProgress = 0.0f;
    else if (progress > Constants::DIFFICULTY_MAX_PROGRESS)
        difficultyProgress = 1.0f;
    else
        difficultyProgress = (progress - Constants::DIFFICULTY_START_PROGRESS) /
                            (Constants::DIFFICULTY_MAX_PROGRESS - Constants::DIFFICULTY_START_PROGRESS);

    // Vitesse augmente plus rapidement
    float targetSpeed = baseBgSpeed + (Constants::MAX_OBSTACLE_SPEED - baseBgSpeed) * difficultyProgress;

    // Augmentation progressive au lieu de directe
    bgSpeed = bgSpeed + (targetSpeed - bgSpeed) * 0.05f;

    Obstacle::setSpeed(bgSpeed);

    // Spawn delay plus court
    float newSpawnDelay = Constants::BASE_SPAWN_DELAY - (Constants::BASE_SPAWN_DELAY - Constants::MIN_SPAWN_DELAY) * difficultyProgress;
    spawnDelay = std::max(Constants::MIN_SPAWN_DELAY, newSpawnDelay);
}

//--------------------------------
// Sauvegarde le high score dans un fichier
//--------------------------------
void Game::saveHighScore()
{
    std::ofstream file(Constants::HIGH_SCORE_FILE);
    if (file.is_open())
    {
        file << highScore;
        file.close();
    }
}

//--------------------------------
// Charge le high score depuis un fichier
//--------------------------------
void Game::loadHighScore()
{
    std::ifstream file(Constants::HIGH_SCORE_FILE);
    if (file.is_open())
    {
        file >> highScore;
        file.close();
    }
    else
    {
        highScore = 0;
    }
}

//--------------------------------
// Met à jour les polices du jeu
//--------------------------------
void Game::applyFonts(sf::Font &newTitleFont, sf::Font &newTextFont)
{
    titleFont = newTitleFont;
    textFont = newTextFont;

    // Mise à jour du menu
    menu.setTitleFont(titleFont);
    // Note: menu utilise déjà textFont via son constructeur

    // Mise à jour de l'écran Game Over
    gameOverScreen.setTitleFont(titleFont);

    // Mise à jour de l'écran About
    about.setTitleFont(titleFont);

    // Mise à jour du menu Pause
    pauseMenu.setTitleFont(titleFont);

    // Mise à jour du timer
    timer.setFont(textFont);

    // Mise à jour de la barre de progression
    // progressBar utilise déjà la police passée au constructeur
}

//--------------------------------
// Met à jour la logique du jeu
//--------------------------------
void Game::update()
{
    // Calcul du delta time
    float dt = deltaClock.restart().asSeconds();
    if (dt > 0.033f)
        dt = 0.033f; // Limite à 33ms
    if (currentState == GameState::MENU)
    {
        menu.update(dt);
    }
    if (currentState == GameState::PLAYING && !isPaused)
    {
        player.update();

        if (player.isDead())
        {
            if (player.isDeathAnimationComplete())
            {
                gameOverScreen.setVictory(false);
                gameOverScreen.setHighScore(highScore);
                currentState = GameState::GAME_OVER;
            }
            return;
        }

        // -------------- Mise à jour du temps --------------
        timer.update();

        if (timer.isExpired() && !heartSystem.isDead())
        {
            heartSystem.decreaseHealth();
            if (heartSystem.isDead())
            {
                player.die();
                return;
            }
            else
            {
                timer.start();
            }
        }

        // -------------- Difficulté --------------
        updateDifficulty();

        // -------------- Défilement du fond --------------
        background1.move(-bgSpeed, 0);
        background2.move(-bgSpeed, 0);

        float imgWidth = backgroundTexture.getSize().x;
        if (background1.getPosition().x + imgWidth < 0)
        {
            background1.setPosition(background2.getPosition().x + imgWidth, 0);
        }
        if (background2.getPosition().x + imgWidth < 0)
        {
            background2.setPosition(background1.getPosition().x + imgWidth, 0);
        }

        // -------------- Distance et bunker --------------
        currentDistance += bgSpeed;
        if (currentDistance > totalDistance)
            currentDistance = totalDistance;

        progressBar.update(currentDistance);

        if (currentDistance > highScore)
        {
            highScore = currentDistance;
            saveHighScore();
        }

        bunkerSprite.move(-bgSpeed, 0);

        if (currentDistance >= totalDistance - 50)
        {
            if (checkBunkerCollision())
            {
                currentState = GameState::VICTORY;
                gameOverScreen.setVictory(true);
                gameOverScreen.setHighScore(highScore);
                return;
            }
        }

        // -------------- Mise à jour des obstacles --------------
        for (int i = 0; i < (int)obstacles.size(); i++)
        {
            obstacles[i]->update(1.0f / 60.0f);
            if (obstacles[i]->isOffScreen())
            {
                obstacles.erase(obstacles.begin() + i);
                i--;
            }
        }

        // -------------- Apparition des obstacles --------------
        spawnTimer += 1.0f / 60.0f;
        if (spawnTimer >= spawnDelay && checkObstacleDistance())
        {
            spawnTimer = 0;
            int type = rand() % 2;

            if (type == 0)
            {
                int groundType = (rand() % 3) + 1;
                obstacles.push_back(std::make_unique<GroundObstacle>(
                    Constants::WINDOW_WIDTH + 50,
                    Constants::GROUND_OBSTACLE_Y,
                    groundType));
            }
            else
            {
                obstacles.push_back(std::make_unique<AirObstacle>(
                    Constants::WINDOW_WIDTH + 50,
                    Constants::AIR_OBSTACLE_Y));
            }
        }

        // -------------- Collisions --------------
        bool hit = false;
        for (auto &obstacle : obstacles)
        {
            if (checkCollision(player.getCollisionBounds(), obstacle->getCollisionBounds()))
            {
                hit = true;
                break;
            }
        }

        if (hit && canTakeDamage)
        {
            heartSystem.decreaseHealth();
            canTakeDamage = false;

            if (heartSystem.getHealth() <= 0)
            {
                player.die();
                return;
            }
            else
            {
                hitCount++;

                if (hitCount == 1)
                {
                    timer.addTime(-2.0f);
                    // Notification
                    showNotification = true;
                    notificationTimer = 2.0f;
                    notificationText.setString("-2 SECONDES !");
                    notificationText.setFillColor(sf::Color(255, 100, 100));
                }
                else if (hitCount == 2)
                {
                    timer.addTime(-5.0f);
                    // Notification
                    showNotification = true;
                    notificationTimer = 2.0f;
                    notificationText.setString("-5 SECONDES !");
                    notificationText.setFillColor(sf::Color(255, 50, 50));
                }

                if (!isPenaltyActive)
                {
                    isPenaltyActive = true;
                    speedPenaltyTimer = Constants::SPEED_PENALTY_DURATION;
                    originalBgSpeed = bgSpeed;
                    bgSpeed = bgSpeed * Constants::SPEED_PENALTY_FACTOR;
                    Obstacle::setSpeed(bgSpeed);
                }
            }
        }
        else if (!hit)
        {
            canTakeDamage = true;
        }

        // -------------- Retour à la vitesse normale --------------
        if (isPenaltyActive)
        {
            speedPenaltyTimer -= 1.0f / 60.0f;
            if (speedPenaltyTimer <= 0.0f)
            {
                isPenaltyActive = false;
                bgSpeed = originalBgSpeed;
                Obstacle::setSpeed(bgSpeed);
            }
        }

        // -------------- Gestion de la notification (timer) --------------
        if (showNotification)
        {
            notificationTimer -= 1.0f / 60.0f;
            if (notificationTimer <= 0.0f)
            {
                showNotification = false;
            }
        }
    }
}

//--------------------------------
// Affiche tous les éléments à l'écran
//--------------------------------
void Game::render()
{
    if (currentState == GameState::MENU || currentState == GameState::ABOUT)
    {
        window.clear(Constants::COLOR_Background);
    }
    else
    {
        window.clear(Constants::COLOR_GAME_BG);
    }

    if (currentState == GameState::PLAYING)
    {
        // -------------- Affichage des éléments du jeu --------------
        window.draw(background1);
        window.draw(background2);
        window.draw(bunkerSprite);

        for (auto &obstacle : obstacles)
            obstacle->draw(window);

        player.draw(window);

        timer.draw(window);
        progressBar.draw(window);
        heartSystem.draw(window);

        // -------------- Menu pause  --------------

        if (isPaused)
        {
            pauseMenu.draw(window);
        }
    }
    else if (currentState == GameState::MENU)
    {
        menu.draw(window);
    }
    else if (currentState == GameState::ABOUT)
    {
        about.draw(window);
    }
    else if (currentState == GameState::GAME_OVER || currentState == GameState::VICTORY)
    {
        if (currentState == GameState::VICTORY)
            window.clear(Constants::COLOR_Background);
        else
            window.clear(Constants::COLOR_Background);

        gameOverScreen.draw(window);
    }

    // Afficher la notification si active
    if (showNotification)
    {
        // Centrer le texte
        sf::FloatRect bounds = notificationText.getLocalBounds();
        notificationText.setPosition(
            Constants::WINDOW_WIDTH / 2 - bounds.width / 2,
            Constants::WINDOW_HEIGHT / 2 - 100);
        window.draw(notificationText);
    }

    window.display();
}