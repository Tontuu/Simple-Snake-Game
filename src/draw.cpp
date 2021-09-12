#include "engine.hpp"
#include "snake.hpp"

void Engine::draw() {
	using namespace std;
	window.clear(sf::Color(35, 35, 35));
	

	window.draw(apple.getSprite());
	
	for (auto & i : snake) {
		window.draw(i.getShape());	
	}

	if (gameover) {
		window.draw(gameoverText);
		window.draw(pressEnterText);
	} else if (pause) {
		window.draw(pauseText);
	}

	window.draw(applesEatenText);
	window.display();
}
