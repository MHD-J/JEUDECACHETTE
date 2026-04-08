#include "../include/Collision.h"
#include <SFML/Graphics.hpp>
bool checkCollision(const sf::FloatRect & rect1,const sf::FloatRect & rect2){
    return rect1.intersects(rect2);
}