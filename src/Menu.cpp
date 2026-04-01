#include "../include/Menu.h"
#include "../include/Constants.h"


Menu::Menu(sf::Font& font){

    options[0].setFont(font);
    options[0].setString("Jouer");
    options[0].setCharacterSize(Constants::MENU_OPTION_SIZE);
    options[0].setPosition(200, Constants::MENU_OPTION_START_Y);
    options[0].setFillColor(Constants::COLOR_HIGH_LIGHT);
    options[1].setFont(font);
    options[1].setString("A propos");
    options[1].setCharacterSize(Constants::MENU_OPTION_SIZE);
    options[1].setPosition(200, Constants::MENU_OPTION_START_Y + Constants::MENU_OPTION_SPACING);
    options[1].setFillColor(sf::Color::White);
    options[2].setFont(font);
    options[2].setString("Quitter");
    options[2].setCharacterSize(Constants::MENU_OPTION_SIZE);
    options[2].setPosition(200, Constants::MENU_OPTION_START_Y + Constants::MENU_OPTION_SPACING * 2);
    options[2].setFillColor(sf::Color::White);
    selectedindex = 0;
}
void Menu::draw(sf::RenderWindow& window){
    for (int i = 0; i < 3; i++)
    {
       if(selectedindex == i){
        options[i].setFillColor(Constants::COLOR_HIGH_LIGHT);
       }else{
        options[i].setFillColor(Constants::COLOR_TEXT);
       }
        window.draw(options[i]);
    }
}
void Menu::handleInput(sf::Event& event,GameState& currentState){

    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedindex = (selectedindex - 1 + 3) % 3;
        }
        else if (event.key.code == sf::Keyboard::Down) {
            selectedindex = (selectedindex + 1) % 3;
        }
        else if (event.key.code == sf::Keyboard::Return) {
            if (selectedindex == 0) {
                currentState = GameState::PLAYING;
            }
            else if (selectedindex == 1) {
                currentState = GameState::ABOUT;
            }
            else if (selectedindex == 2) {
                currentState = GameState::QUIT;
            }
        }
    }
} 