#include "GameOverState.h"

#include "Constants.h"
#include "Game.h"
#include "ResourceManager.h"

GameOverState::GameOverState(bool victory) : victory_(victory) {}

void GameOverState::handleInput(const sf::Event& event, Game& game) {
  if (event.is<sf::Event::KeyPressed>()) {
    game.getWindow().close();
  }
}

void GameOverState::update(float) {}

void GameOverState::draw(sf::RenderWindow& window) {
  sf::Font& font = ResourceManager::getInstance().getFont();
  std::string msg = victory_ ? "You Win!" : "Game Over";
  sf::Text text(font, msg, 40);
  text.setFillColor(sf::Color::White);
  text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2));
  window.draw(text);
}
