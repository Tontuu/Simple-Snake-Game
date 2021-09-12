#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>

class Snake {
	
	public:
		explicit Snake(sf::Vector2f startPosition);

		sf::Vector2f getPosition();
		sf::RectangleShape getShape();
		void update();
		void setPosition(sf::Vector2f newPosition);


	private:
		sf::Vector2f position;	
		sf::RectangleShape section;

};

#endif /* SNAKE_H */
