#include "engine.hpp"

const sf::Time Engine::TimePerFrame = sf::seconds(1.f/60.f); // ????

Engine::Engine() {

	sf::Image myIcon;
	myIcon.loadFromFile("assets/icon.png");

	resolution = sf::Vector2f(600, 400);
	window.create(sf::VideoMode(resolution.x, resolution.y, 64), "Snake", sf::Style::Default);
	window.setIcon(64, 64, myIcon.getPixelsPtr());
	window.setFramerateLimit(FPS);

	mainFont.loadFromFile("assets/fonts/ARCADECLASSIC.TTF");

	setupText(&applesEatenText, mainFont, "APPLES ", 24, sf::Color::White);
	sf::FloatRect applesEatenBounds = applesEatenText.getLocalBounds();
	applesEatenText.setPosition(sf::Vector2f(50 - applesEatenBounds.width /2, 5 ));

	setupText(&gameoverText, mainFont, "GAMEOVER", 72, sf::Color::White);
	sf::FloatRect gameoverBounds = gameoverText.getLocalBounds();
	gameoverText.setPosition(sf::Vector2f(resolution.x / 2 - gameoverBounds.width / 2, resolution.y / 2 - 100));
	gameoverText.setOutlineThickness(2);
	gameoverText.setOutlineColor(sf::Color::Green);

	setupText(&pressEnterText, mainFont, "Press   ENTER   to   restart !!!", 38, sf::Color::White);
	sf::FloatRect pressEnterBounds = pressEnterText.getLocalBounds();
	pressEnterText.setPosition(sf::Vector2f(resolution.x / 2 - pressEnterBounds.width / 2, gameoverText.getPosition().y + 75));
	pressEnterText.setOutlineThickness(1);
	pressEnterText.setOutlineColor(sf::Color::Green);


	setupText(&pauseText, mainFont, "PAUSED", 55, sf::Color::White);
	sf::FloatRect pauseBounds = pauseText.getLocalBounds();
	pauseText.setPosition(sf::Vector2f(resolution.x / 2 - pauseBounds.width / 2, resolution.y / 2 - 50));
	pauseText.setOutlineThickness(1);
	pauseText.setOutlineColor(sf::Color::Red);


	newGame();
}

void Engine::newGame() {
	sectionCount = 0;
	applesEaten = 0;
	snakeDirection = Direction::RIGHT;
	timeSinceLastMove = sf::Time::Zero;
	directionQueue.clear();
	pause = false;
	gameover = false;
	applesEatenText.setString("APPLES " + std::to_string(applesEaten));

	addSnake();
	appleMove();

}

void Engine::shiftPause() {
	if (pause) {
		pause = false;
	} else {
		pause = true;
	}
}

void Engine::setupText(sf::Text *text, const sf::Font &font,const sf::String &value, int size, sf::Color colour){
	text -> setFont(font);
	text -> setString(value);
	text -> setCharacterSize(size);
	text -> setFillColor(colour);

}

void Engine::run() {
	sf::Vector2f test = snake[0].getPosition();
  sf::Clock clock;
	
	while (window.isOpen()) {
    sf::Time delta = clock.restart();
    timeSinceLastMove += delta;

		input();
		if (!pause && !gameover) { update(); }
		draw();

	}
}

void Engine::addSnake() {
	snake.clear();	
	snake.emplace_back(sf::Vector2f(100, 100));
	snake.emplace_back(sf::Vector2f(80, 100));
	snake.emplace_back(sf::Vector2f(60, 100));
}

void Engine::addSnakeSection() {

	sf::Vector2f newSectionPosition = snake[snake.size() - 1].getPosition();
	snake.emplace_back(newSectionPosition);
}

void Engine::appleMove() {
	sf::Vector2f appleResolution = sf::Vector2f(resolution.x / 20 -2, resolution.y / 20 - 2);
	sf::Vector2f newApplePos;
	bool placeCheck = true;
	srand(time(nullptr));

	do {
		placeCheck = true;

		newApplePos.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolution.x)) * 20;
		newApplePos.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolution.y)) * 20;

		for (auto & i : snake) {
			if (i.getShape().getGlobalBounds()
			.intersects(sf::Rect<float>(newApplePos.x, newApplePos.y, 20, 20))) {
				placeCheck = false;
				break;
			}
		}

	} while (!placeCheck);
	apple.setPosition(newApplePos);
}


