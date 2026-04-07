#include <vector>
#include "Obstacle.h"

// ... dans le main ...
std::vector<Obstacle*> mesObstacles;

// On ajoute les 4 types différents
mesObstacles.push_back(new Pierre(300, 520));
mesObstacles.push_back(new Mine(600, 550));
mesObstacles.push_back(new Drone(400, 200));
mesObstacles.push_back(new BarqueEau(800, 540));

// --- Dans la boucle de jeu ---
float dt = clock.restart().asSeconds();

for (auto obs : mesObstacles) {
    obs->update(dt); // Le drone bouge, la barque flotte, la mine reste fixe
}

// --- Dans la partie dessin ---
window.clear();
for (auto obs : mesObstacles) {
    obs->draw(window);
}
window.display();