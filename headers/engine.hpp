#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "snake.hpp"
#include "apple.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <deque> 
#include <ctime>
#include <iostream>

class Engine {
	public:
    enum Direction { UP, RIGHT, LEFT, DOWN }; 
        
		Engine();

    void addDirection(int newDirection);
    void update();
		void input();
		void draw();
		void run(); 
		void addSnake();
		void addSnakeSection();
		void appleMove();
		void shiftPause();
		void newGame();

		static void setupText(sf::Text *text, const sf::Font &font, const sf::String &value, int size, sf::Color colour);

		sf::Vector2f resolution; 
		sf::RenderWindow window; 

	private:

		const unsigned int FPS = 10;
		static const sf::Time TimePerFrame; 
		std::vector<Snake> snake;

		bool gameover;
		bool pause;
	  int speed = 4;
		int snakeDirection;
		int sectionCount;
		int applesEaten;
		std::deque<int> directionQueue; 

		sf::Time timeSinceLastMove;
		sf::Font mainFont;

		sf::Text applesEatenText;
		sf::Text gameoverText;
		sf::Text pauseText;
		sf::Text pressEnterText;

		Apple apple;
};
#endif /* ENGINE_HPP */
