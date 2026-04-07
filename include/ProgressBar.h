class ProgressBar {
private:
    sf::RectangleShape background;
    sf::RectangleShape foreground; // La barre qui se remplit
    float totalDistance;
public:
    ProgressBar(float width, float height, float totalDist);
    void update(float playerX); // On passe la position X du joueur
    void draw(sf::RenderWindow& window);
};