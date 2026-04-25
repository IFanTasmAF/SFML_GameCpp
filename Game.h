#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "GameState.h"

class Game {
 public:
  Game();
  void run();
  void changeState(std::unique_ptr<GameState> newState);
  void popState();
  sf::RenderWindow& getWindow() { return window_; }

 private:
  sf::RenderWindow window_;
  std::vector<std::unique_ptr<GameState>> stateStack_;
  sf::Clock clock_;
};
