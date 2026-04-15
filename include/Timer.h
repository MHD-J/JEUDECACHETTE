#ifndef TIMER_H
#define TIMER_H

#include <SFML/Graphics.hpp>

class Timer
{
public:
    Timer();
    void update();
    void start();
    void stop();
    void reset();
    bool isExpired() const;
    void draw(sf::RenderWindow &window);
    void setFont(sf::Font &font); 
    void addTime(float seconds);

private:
    float remainingTime;
    float initialTime;
    bool isRunning;
    sf::Text timerText;
    sf::Color normalColor;
    sf::Color warningColor;
    void updateText();
};

#endif