#pragma once
#include <SFML/Graphics.hpp>

#include "GameState.h"

class GameOverState : public GameState {
 public:
  GameOverState(sf::RenderWindow& window);

  void handleInput(sf::RenderWindow& window) override;
  void update(float dt) override;
  void render(sf::RenderWindow& window) override;

 private:
  sf::Font font;
  sf::Text text;
};
