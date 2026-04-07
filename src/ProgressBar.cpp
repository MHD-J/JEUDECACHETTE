void ProgressBar::update(float playerX) {
    float ratio = playerX / totalDistance;
    if (ratio > 1.0f) ratio = 1.0f;
    foreground.setSize(sf::Vector2f(background.getSize().x * ratio, background.getSize().y));
}