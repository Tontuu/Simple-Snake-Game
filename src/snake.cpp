#include "snake.hpp"

Snake::Snake(sf::Vector2f startPosition) {
	section.setSize(sf::Vector2f(20, 20));
	section.setFillColor(sf::Color::Green);
	section.setOutlineThickness(-1.f);
	section.setOutlineColor(sf::Color(35, 35, 35));
	section.setPosition(startPosition);
	position = startPosition;
}

sf::Vector2f Snake::getPosition() {
	return position;
}

void Snake::setPosition(sf::Vector2f newPosition) {
	position = newPosition;
}

sf::RectangleShape Snake::getShape() {
	return section;
}

void Snake::update() {
	section.setPosition(position);
}
