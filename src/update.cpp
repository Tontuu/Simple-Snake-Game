#include "engine.hpp"

void Engine::update() {

    if(timeSinceLastMove.asSeconds() >= sf::seconds(1.f / float(speed)).asSeconds()) {
        sf::Vector2f thisSectionPosition = snake[0].getPosition();
        sf::Vector2f lastSectionPosition = thisSectionPosition;

        if (!directionQueue.empty()) {
            switch(snakeDirection) {
                case Direction::UP:
                    if(directionQueue.front() != Direction::DOWN) {
                        snakeDirection = directionQueue.front();
                    }
                    break;
                case Direction::DOWN:
                    if(directionQueue.front() != Direction::UP) {
                        snakeDirection = directionQueue.front();
                    }
                    break;
                case Direction::RIGHT:
                    if(directionQueue.front() != Direction::LEFT) {
                        snakeDirection = directionQueue.front();
                    }
                    break;
                case Direction::LEFT:
                    if(directionQueue.front() != Direction::RIGHT) {
                        snakeDirection = directionQueue.front();
                    }
                    break;
            }
            directionQueue.pop_front();
        }

        if (sectionCount) {
            addSnakeSection();
            sectionCount--;
        }
       
        switch(snakeDirection) {
            case Direction::RIGHT:
                snake[0].setPosition(sf::Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
                break;
            case Direction::DOWN:
                snake[0].setPosition(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
                break; 
            case Direction::LEFT:
                snake[0].setPosition(sf::Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
                break;
            case Direction::UP:
                snake[0].setPosition(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
                break;
        }
        
        if (thisSectionPosition.x > resolution.x) {
            snake[0].setPosition
                (sf::Vector2f(thisSectionPosition.x - thisSectionPosition.x, thisSectionPosition.y));

        } else if (thisSectionPosition.x < 0) {
            snake[0].setPosition
                (sf::Vector2f(thisSectionPosition.x + resolution.x, thisSectionPosition.y));

        } else if (snake[0].getPosition().x == resolution.x) {
            snake[0].setPosition
                (sf::Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));

        } else if (thisSectionPosition.y > resolution.y - 20) {
            snake[0].setPosition
                (sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y - resolution.y));

        } else if (thisSectionPosition.y < 0) {
            snake[0].setPosition
                (sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y + resolution.y));
        }
        
        for (int i = 1; i < snake.size(); i++) {
            thisSectionPosition = snake[i].getPosition(); 
            snake[i].setPosition(lastSectionPosition);
            lastSectionPosition = thisSectionPosition;
        }

        for (auto & i : snake) {
           i.update(); 
        }

        if (snake[0].getShape().getGlobalBounds().intersects(apple.getSprite().getGlobalBounds())) {
            applesEaten++;
            applesEatenText.setString("APPLES " + std::to_string(applesEaten));
            sectionCount += 4;
            appleMove();
        }

        for (int i = 1; i < snake.size(); i++) {
            if(snake[0].getShape().getGlobalBounds().intersects(snake[i].getShape().getGlobalBounds())) {
                gameover = true;
            }
        }

        timeSinceLastMove == sf::Time::Zero;
    }
}
