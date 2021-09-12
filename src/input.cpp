#include "engine.hpp"

void Engine::input() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {

          if (event.key.code == sf::Keyboard::Escape) {
            window.close();
          }

          if (event.key.code == sf::Keyboard::P) {
              shiftPause();
          }

          if (gameover && event.key.code == sf::Keyboard::Enter) {
              newGame();
          }

          if (event.key.code == sf::Keyboard::Up) {
            addDirection(Direction::UP);
          } else if (event.key.code == sf::Keyboard::Down) {
              addDirection(Direction::DOWN);
          } else if (event.key.code == sf::Keyboard::Right) {
              addDirection(Direction::RIGHT);
          } else if (event.key.code == sf::Keyboard::Left) {
              addDirection(Direction::LEFT);
          }
        }
    }
}

void Engine::addDirection(int newDirection) {

    if (directionQueue.empty()) {
        directionQueue.emplace_back(newDirection);
    } else {
        if (directionQueue.back() != newDirection) {
            directionQueue.emplace_back(newDirection);
        }
    }
}
