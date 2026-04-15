#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

/**
 * @namespace Constants
 * @brief Regroupe toutes les constantes du jeu (fenêtre, couleurs, dimensions, etc.)
 *
 * Ce namespace centralise les valeurs fixes utilisées dans tout le projet
 * afin de faciliter les modifications globales.
 */
namespace Constants
{

    // --------------------------------
    // SECTION 1 : CONFIGURATION DE LA FENÊTRE
    // --------------------------------

    const unsigned int WINDOW_WIDTH = 1600;             // Largeur de la fenêtre 
    const unsigned int WINDOW_HEIGHT = 900;             // Hauteur de la fenêtre 
    const std::string WINDOW_TITLE = "Jeu de Cachette"; // Titre de la fenêtre

    // --------------------------------
    // SECTION 2 : PERFORMANCES
    // --------------------------------

    const unsigned int FRAME_RATE_LIMIT = 60; // Limite de FPS 

    // --------------------------------
    // SECTION 3 : COULEURS
    // --------------------------------

    const sf::Color COLOR_Background(25, 35, 45);   // Fond des menus (bleu-gris foncé)
    const sf::Color COLOR_GAME_BG(144, 238, 144);   // Fond du jeu (vert clair)
    const sf::Color COLOR_HIGH_LIGHT(255, 200, 50); // Surbrillance (jaune/or)
    const sf::Color COLOR_TEXT(245, 245, 245);      // Texte (blanc cassé)
    const sf::Color COLOR_PLAYER(0, 0, 0);          // Joueur
    const sf::Color COLOR_OBSTACLE(200, 50, 50);    // Obstacles
    const sf::Color COLOR_PROGRESS(255, 180, 0);    // Barre de progression (orange)

    // --------------------------------
    // SECTION 4 : CHEMINS D'ACCÈS AUX FICHIERS
    // --------------------------------

    // Polices
    const std::string FONT_PATH = "assets/fonts/arial.ttf";
    const std::string FONT_PATH_TITLE = "assets/fonts/3Dumb.ttf";
    const std::string FONT_PATH_TEXT = "assets/fonts/2Dumb.ttf";

    // Images
    const std::string BACKGROUND_IMAGE = "assets/images/back.png";
    const std::string PLAYER_IMAGE = "assets/images/player.png";
    const std::string BUNKER_IMAGE = "assets/images/bunker.png";
    const std::string OBSTACLE_GROUND_IMAGE = "assets/images/obstacle_ground.png";
    const std::string OBSTACLE_AIR_IMAGE = "assets/images/obstacle_air.png";

    // High score
    const std::string HIGH_SCORE_FILE = "assets/highscore.txt";

    // --------------------------------
    // SECTION 5 : VITESSES ET MOUVEMENT
    // --------------------------------

    const float BACKGROUND_SPEED = 6.0f;        // Vitesse de base du défilement
    const float MAX_OBSTACLE_SPEED = 12.0f;     // Vitesse maximale (difficulté max)
    const float DIFFICULTY_SCALE_FACTOR = 0.5f; // Facteur d'augmentation de la difficulté
    // ========== Speed Penalty ==========
    const float SPEED_PENALTY_DURATION = 2.5f;
    const float SPEED_PENALTY_FACTOR = 0.4f;

    // ========== Difficulty Scaling ==========
    const float DIFFICULTY_START_PROGRESS = 0.1f;
    const float DIFFICULTY_MAX_PROGRESS = 0.6f;

    // ========== Time Penalty ==========
    const float FIRST_HIT_TIME_PENALTY = -2.0f;  // -2 secondes
    const float SECOND_HIT_TIME_PENALTY = -5.0f; // -5 secondes

    // ========== Notification System pour Time Penalty ==========
    const float NOTIFICATION_DURATION = 2.0f; 
    const int NOTIFICATION_SIZE = 30;        

    // --------------------------------
    // SECTION 6 : JOUEUR (dimensions, physique, animations)
    // --------------------------------

    // Dimensions
    const float PLAYER_WIDTH = 100.0f;         // Largeur du joueur
    const float PLAYER_HEIGHT = 150.0f;        // Hauteur debout
    const float PLAYER_CROUCH_HEIGHT = 150.0f; // Hauteur accroupi (identique à debout)

    // Physique
    const float PLAYER_JUMP_FORCE = -16.0f; // Force du saut (négative = vers le haut)
    const float PLAYER_GRAVITY = 0.85f;     // Gravité appliquée à chaque frame

    // Position au sol
    const float GROUND_Y = 760.0f;                         // Hauteur du sol (Y)
    const float PLAYER_START_X = 200.0f;                   // Position X de départ
    const float PLAYER_START_Y = GROUND_Y - PLAYER_HEIGHT; // Position Y de départ

    // --------------------------------
    // SECTION 7 : OBSTACLES (dimensions, positions)
    // --------------------------------

    // Obstacles au sol
    const float OBSTACLE_WIDTH = 60.0f;                         // Largeur des obstacles au sol
    const float OBSTACLE_HEIGHT = 55.0f;                        // Hauteur des obstacles au sol
    const float GROUND_OBSTACLE_Y = GROUND_Y - OBSTACLE_HEIGHT; // Position Y

    // Obstacles aériens (drones)
    const float AIR_OBSTACLE_WIDTH = 70.0f;  // Largeur des drones
    const float AIR_OBSTACLE_HEIGHT = 55.0f; // Hauteur des drones
    const float AIR_OBSTACLE_Y = 585.0f;     // Position Y fixe des drones

    // Apparition des obstacles
    const float BASE_SPAWN_DELAY = 2.5f; // Délai de base entre deux apparitions
    const float MIN_SPAWN_DELAY = 1.2f;  // Délai minimum (difficulté max)

    // --------------------------------
    // SECTION 8 : BUNKER (objectif final)
    // --------------------------------

    const float BUNKER_WIDTH = 280.0f;                       // Largeur du bunker
    const float BUNKER_HEIGHT = 280.0f;                      // Hauteur du bunker
    const float BUNKER_Y = GROUND_Y - BUNKER_HEIGHT + 35.0f; // Position Y
    const float BUNKER_X = 28000.0f;                         // Position X (distance totale)
    const float TOTAL_DISTANCE = 28000.0f;                   // Distance totale à parcourir

    // --------------------------------
    // SECTION 9 : TEMPS ET CHRONOMÈTRE
    // --------------------------------

    const float INITIAL_TIME = 60.0f; // Temps initial (secondes)

    // --------------------------------
    // SECTION 10 : SYSTÈME DE VIES (CŒURS)
    // --------------------------------

    const int PLAYER_MAX_HEALTH = 3; // Nombre maximum de vies

    // Apparence des cœurs
    const float HEART_SIZE = 35.0f;                    // Diamètre d'un cœur
    const float HEART_SPACING = 15.0f;                 // Espace entre deux cœurs
    const float HEART_START_X = WINDOW_WIDTH - 150.0f; // Position X de départ
    const float HEART_START_Y = 20.0f;                 // Position Y de départ
    const float HEART_OUTLINE_THICKNESS = 2.0f;        // Épaisseur du contour

    // Couleurs des cœurs
    const sf::Color HEART_COLOR_FULL(255, 80, 80);      // Cœur plein (rouge vif)
    const sf::Color HEART_COLOR_EMPTY(80, 40, 40);      // Cœur vide (rouge foncé)
    const sf::Color HEART_OUTLINE_COLOR(200, 200, 200); // Contour (blanc grisé)

    // --------------------------------
    // SECTION 11 : INTERFACE UTILISATEUR (UI)
    // --------------------------------

    // Chronomètre
    const float TIMER_TEXT_SIZE = 36.0f;  // Taille de la police
    const float TIMER_POSITION_X = 30.0f; // Position X
    const float TIMER_POSITION_Y = 20.0f; // Position Y

    // Barre de progression
    const float PROGRESS_BAR_WIDTH = 500.0f;                                       // Largeur de la barre
    const float PROGRESS_BAR_HEIGHT = 25.0f;                                       // Hauteur de la barre
    const float PROGRESS_BAR_POSITION_X = (WINDOW_WIDTH - PROGRESS_BAR_WIDTH) / 2; // Centrée
    const float PROGRESS_BAR_POSITION_Y = 40.0f;                                   // Position Y

    // --------------------------------
    // SECTION 12 : MENU PRINCIPAL
    // --------------------------------

    const float MENU_TITLE_SIZE = 75.0f;      // Taille du titre
    const float MENU_OPTION_SIZE = 45.0f;     // Taille des options
    const float MENU_TITLE_Y = 180.0f;        // Position Y du titre
    const float MENU_OPTION_START_Y = 380.0f; // Position Y de la première option
    const float MENU_OPTION_SPACING = 80.0f;  // Espace entre les options

    // --------------------------------
    // SECTION 13 : ÉCRAN "À PROPOS"
    // --------------------------------

    const float ABOUT_TITLE_SIZE = 55.0f;    // Taille du titre
    const float ABOUT_TEXT_SIZE = 28.0f;     // Taille du texte
    const float ABOUT_TEXT_START_X = 150.0f; // Position X du texte
    const float ABOUT_TEXT_START_Y = 180.0f; // Position Y du texte
    const float ABOUT_LINE_SPACING = 45.0f;  // Espacement entre les lignes

    // --------------------------------
    // SECTION 14 : ÉCRAN DE PAUSE
    // --------------------------------

    const float PAUSE_TITLE_SIZE = 55.0f;      // Taille du titre
    const float PAUSE_OPTION_SIZE = 40.0f;     // Taille des options
    const float PAUSE_TITLE_Y = 200.0f;        // Position Y du titre
    const float PAUSE_OPTION_START_Y = 350.0f; // Position Y de la première option
    const float PAUSE_OPTION_SPACING = 70.0f;  // Espace entre les options

    // --------------------------------
    // SECTION 15 : ÉCRAN GAME OVER / VICTOIRE
    // --------------------------------

    const float GAMEOVER_TITLE_SIZE = 70.0f;      // Taille du titre
    const float GAMEOVER_OPTION_SIZE = 40.0f;     // Taille des options
    const float GAMEOVER_OPTION_START_Y = 450.0f; // Position Y de la première option
    const float GAMEOVER_OPTION_SPACING = 70.0f;  // Espace entre les options

    // --------------------------------
    // SECTION 16 : SYSTÈME DE COLLISION 
    // --------------------------------

    const float PLAYER_COLLISION_SHRINK_X = 0.30f;   // Réduction horizontale du joueur (30%)
    const float PLAYER_COLLISION_SHRINK_Y = 0.25f;   // Réduction verticale du joueur (25%)
    const float OBSTACLE_COLLISION_SHRINK_X = 0.40f; // Réduction horizontale des obstacles (40%)
    const float OBSTACLE_COLLISION_SHRINK_Y = 0.35f; // Réduction verticale des obstacles (35%)
    const float BUNKER_COLLISION_SHRINK = 0.35f;     // Réduction du bunker (35%)


    // =================================
    // SECTION 17 : CONSTANTES SPECIFIQUES AU MENU
    // =================================
    // ========== Menu Background Effects ==========
const int MENU_CIRCLES_COUNT = 30;           // Nombre de cercles
const float MENU_CIRCLE_MIN_SIZE = 20.0f;    // Taille minimale
const float MENU_CIRCLE_MAX_SIZE = 120.0f;   // Taille maximale
const float MENU_CIRCLE_MIN_ALPHA = 20;      // Alpha minimal 
const float MENU_CIRCLE_MAX_ALPHA = 60;      // Alpha maximal
const float MENU_CIRCLE_SPEED = 15.0f;       // Vitesse de déplacement
    // --------------------------------
    // SECTION 18 : ÉNUMÉRATIONS (types et états)
    // --------------------------------

    /**
     * @enum ObstacleType
     * @brief Distingue les obstacles au sol des obstacles aériens
     */
    enum ObstacleType
    {
        GROUND,
        AIR
    };

    /**
     * @enum PlayerHealth
     * @brief État de santé du joueur
     */
    enum PlayerHealth
    {
        HEALTHY,
        INJURED,
        DEAD
    };

    /**
     * @enum GameStateEnum
     * @brief États possibles du jeu
     */
    enum GameStateEnum
    {
        MENU,
        ABOUT,
        PLAYING,
        PAUSED,
        GAME_OVER,
        VICTORY
    };

}

#endif