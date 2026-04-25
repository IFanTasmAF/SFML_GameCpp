#pragma once
#include <SFML/Graphics.hpp>

class Game;

class GameState {
 public:
  virtual ~GameState() = default;
  virtual void handleInput(const sf::Event& event, Game& game) = 0;
  virtual void update(float deltaTime) = 0;
  virtual void draw(sf::RenderWindow& window) = 0;
};
