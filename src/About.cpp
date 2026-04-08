void About::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(rulesText); // "Évitez les mines et atteignez le bunker !"
    window.draw(backButton); 
}