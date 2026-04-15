#include "../include/Timer.h"
#include "../include/Constants.h"

Timer::Timer()
{
    initialTime = Constants::INITIAL_TIME;
    remainingTime = initialTime;
    isRunning = false;
    normalColor = Constants::COLOR_TEXT;
    warningColor = sf::Color::Red;
    timerText.setCharacterSize(Constants::TIMER_TEXT_SIZE);
    timerText.setPosition(Constants::TIMER_POSITION_X, Constants::TIMER_POSITION_Y);
    updateText();
}

void Timer::setFont(sf::Font &font)
{
    timerText.setFont(font);
}

void Timer::update()
{
    if (!isRunning)
        return;
    if (remainingTime <= 0.0f)
        return;

    remainingTime -= 1.0f / 60.0f;

    if (remainingTime <= 0.0f)
    {
        remainingTime = 0.0f;
        isRunning = false;
    }
    updateText();
}

void Timer::start()
{
    isRunning = true;
}

void Timer::stop()
{
    isRunning = false;
}

void Timer::reset()
{
    remainingTime = initialTime;
    // isRunning = false;
    updateText();
}

bool Timer::isExpired() const
{
    return remainingTime <= 0.0f;
}

void Timer::addTime(float seconds)
{
    remainingTime += seconds;
    if (remainingTime < 0.0f)
        remainingTime = 0.0f;
    if (remainingTime > initialTime)
        remainingTime = initialTime;
    updateText();
}

void Timer::updateText()
{
    int minutes = static_cast<int>(remainingTime) / 60;
    int seconds = static_cast<int>(remainingTime) % 60;

    if (remainingTime <= 10.0f)
    {
        timerText.setFillColor(warningColor);
    }
    else
    {
        timerText.setFillColor(normalColor);
    }

    if (seconds < 10)
    {
        timerText.setString("Time: " + std::to_string(minutes) + ":0" + std::to_string(seconds));
    }
    else
    {
        timerText.setString("Time: " + std::to_string(minutes) + ":" + std::to_string(seconds));
    }
}


void Timer::draw(sf::RenderWindow &window)
{
    window.draw(timerText);
}