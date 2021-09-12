#include "apple.hpp"

Apple::Apple() {
	sf::Vector2f startingPosition(400, 300);
	sprite.setSize(sf::Vector2f(20, 20));
	sprite.setFillColor(sf::Color::Red);
	sprite.setPosition(startingPosition);
}

void Apple::setPosition(sf::Vector2f newPosition) {
	sprite.setPosition(newPosition);
}

sf::RectangleShape Apple::getSprite() {
	return sprite;
}


