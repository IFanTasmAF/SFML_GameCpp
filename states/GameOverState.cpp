#include "GameOverState.h"

GameOverState::GameOverState(sf::RenderWindow& window)
    : text(font, "GAME OVER", 50) {
  font.openFromFile("arial.ttf");

  text.setPosition({200.f, 250.f});
}

void GameOverState::handleInput(sf::RenderWindow& window) {
  while (auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }
  }
}

void GameOverState::update(float dt) {}

void GameOverState::render(sf::RenderWindow& window) { window.draw(text); }
