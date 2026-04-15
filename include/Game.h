#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <fstream>
#include "GameState.h"
#include "Player.h"
#include "Timer.h"
#include "Collision.h"
#include "Menu.h"
#include "About.h"
#include "Obstacle.h"
#include "ProgressBar.h"
#include "GameOverScreen.h"
#include "HeartSystem.h"
#include "PauseMenu.h"

class Game
{
public:
    Game(sf::RenderWindow &window, sf::Font &font);
    void run();
    void changeState(GameState newState);
    void resetGame();
    void startGame();
    void startTimer(){ timer.start(); };
    void applyFonts(sf::Font &titleFont, sf::Font &textFont);
    Timer timer;

private:
    // --------------- Fenêtre et état ---------------
    sf::RenderWindow &window;
    sf::Font &font;
    GameState currentState;
    bool isPaused; // État pause du jeu

    // damage hearts
    bool canTakeDamage;

    sf::Clock deltaClock;

    // --------------- Composants principaux du jeu ---------------
    Player player;                 // Gère le joueur (animation, saut, position)
    Menu menu;                     // Menu principal
    About about;                   // Écran "À propos"
    ProgressBar progressBar;       // Barre de progression
    GameOverScreen gameOverScreen; // Écran de fin (victoire/défaite)
    HeartSystem heartSystem;       // Système de cœurs (3 vies)
    PauseMenu pauseMenu;           // Menu de pause

    // --------------- Gestion des obstacles ---------------
    std::vector<std::unique_ptr<Obstacle>> obstacles; // Liste des obstacles
    float spawnTimer;                                 // Temps écoulé depuis le dernier spawn
    float spawnDelay;                                 // Délai avant le prochain spawn

    // --------------- Défilement du fond et vitesse ---------------
    sf::Texture backgroundTexture;
    sf::Sprite background1;
    sf::Sprite background2;
    float bgSpeed;     // Vitesse actuelle du fond
    float baseBgSpeed; // Vitesse de base

    // --------------- Bunker (objectif final) ---------------
    sf::Texture bunkerTexture;
    sf::Sprite bunkerSprite;
    float bunkerX; // Position X du bunker

    // --------------- Progression et distance ---------------
    float totalDistance;   // Distance totale à parcourir
    float currentDistance; // Distance actuelle parcourue
    float highScore;       // Meilleure distance enregistrée

    // --------------- Vitesse et difficulté ---------------
    // Speed penalty
    float speedPenaltyTimer;
    float originalBgSpeed;
    bool isPenaltyActive;
    int hitCount;

    // Difficulty
    float difficultyProgress;

    // Notification
    sf::Text notificationText;
    float notificationTimer;
    bool showNotification;

    // --------------- Polices ---------------
    sf::Font titleFont;
    sf::Font textFont;

    // --------------- Méthodes privées ---------------
    void handleEvents(); // Gère les entrées clavier/souris
    void update();       // Met à jour la logique du jeu
    void render();       // Affiche tous les éléments

    bool checkBunkerCollision();  // Vérifie si le joueur atteint le bunker
    void saveHighScore();         // Sauvegarde le high score dans un fichier
    void loadHighScore();         // Charge le high score depuis un fichier
    void updateDifficulty();      // Augmente la difficulté progressivement
    bool checkObstacleDistance(); // Évite les obstacles trop proches
};

#endif