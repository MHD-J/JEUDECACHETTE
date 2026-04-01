#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <string>

namespace Constants
{

    // ========== Window Settings ==========
    const unsigned int WINDOW_WIDTH = 1200;
    const unsigned int WINDOW_HEIGHT = 1000;
    const std::string WINDOW_TITLE = "Jeu de Cachette";

    // ========== Frame Rate ==========
    const unsigned int FRAME_RATE_LIMIT = 60;

    // ========== Colors ==========
    const sf::Color COLOR_Background(144, 238, 144);
    const sf::Color COLOR_HIGH_LIGHT(102,255,255);
    const sf::Color COLOR_TEXT(34, 139, 34);
    const sf::Color COLOR_PLAYER(0, 0, 0);
    const sf::Color COLOR_OBSTACLE(255, 0, 0);
    const sf::Color COLOR_PROGRESS(0, 255, 0);

    // ========== Font Paths ==========
    const std::string FONT_PATH = "assets/fonts/arial.ttf";

    // ========== Image Paths ==========
    const std::string BACKGROUND_IMAGE = "assets/images/background.png";
    const std::string PLAYER_IMAGE = "assets/images/player.png";
    const std::string BUNKER_IMAGE = "assets/images/bunker.png";
    const std::string OBSTACLE_GROUND_IMAGE = "assets/images/obstacle_ground.png";
    const std::string OBSTACLE_AIR_IMAGE = "assets/images/obstacle_air.png";

    // ========== Player Constants ==========
    const float PLAYER_WIDTH = 40.0f;
    const float PLAYER_HEIGHT = 50.0f;
    const float PLAYER_CROUCH_HEIGHT = 30.0f;
    const float PLAYER_SPEED_X = 5.0f;
    const float PLAYER_JUMP_FORCE = -12.0f;
    const float PLAYER_GRAVITY = 0.8f;
    const float GROUND_Y = 500.0f;
    const float PLAYER_START_X = 150.0f;
    const float PLAYER_START_Y = GROUND_Y - PLAYER_HEIGHT;

    // ========== Obstacle Constants ==========
    const float OBSTACLE_WIDTH = 30.0f;
    const float OBSTACLE_HEIGHT = 40.0f;
    const float OBSTACLE_SPEED = 4.0f;
    const float OBSTACLE_SPAWN_DELAY_MIN = 60.0f;
    const float OBSTACLE_SPAWN_DELAY_MAX = 120.0f;
    const float AIR_OBSTACLE_Y = 400.0f;
    const float GROUND_OBSTACLE_Y = GROUND_Y - OBSTACLE_HEIGHT;

    // ========== Gameplay Constants ==========
    const float INITIAL_TIME = 60.0f;
    const float TOTAL_DISTANCE = 1000.0f;

    // ========== Bunker Constants ==========
    const float BUNKER_WIDTH = 50.0f;
    const float BUNKER_HEIGHT = 60.0f;
    const float BUNKER_Y = GROUND_Y - BUNKER_HEIGHT;

    // ========== Menu Constants ==========
    const float MENU_TITLE_SIZE = 48.0f;
    const float MENU_OPTION_SIZE = 32.0f;
    const float MENU_TITLE_Y = 150.0f;
    const float MENU_OPTION_START_Y = 300.0f;
    const float MENU_OPTION_SPACING = 60.0f;

    // ========== About Screen Constants ==========
    const float ABOUT_TEXT_SIZE = 24.0f;
    const float ABOUT_TEXT_START_X = 50.0f;
    const float ABOUT_TEXT_START_Y = 100.0f;
    const float ABOUT_LINE_SPACING = 35.0f;

    // ========== UI Constants ==========
    const float TIMER_TEXT_SIZE = 30.0f;
    const float TIMER_POSITION_X = 20.0f;
    const float TIMER_POSITION_Y = 20.0f;
    const float PROGRESS_BAR_WIDTH = 400.0f;
    const float PROGRESS_BAR_HEIGHT = 20.0f;
    const float PROGRESS_BAR_POSITION_X = (WINDOW_WIDTH - PROGRESS_BAR_WIDTH) / 2;
    const float PROGRESS_BAR_POSITION_Y = 30.0f;

    // ========== Obstacle Types ==========
    enum ObstacleType
    {
        GROUND,
        AIR
    };

    // ========== Player Health States ==========
    enum PlayerHealth
    {
        HEALTHY,
        INJURED,
        DEAD
    };

    // ========== Game States ==========
    enum GameState
    {
        MENU,
        ABOUT,
        PLAYING,
        GAME_OVER,
        VICTORY
    };

}

#endif