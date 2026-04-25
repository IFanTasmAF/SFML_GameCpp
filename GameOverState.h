#pragma once
#include "GameState.h"

class GameOverState : public GameState {
 public:
  GameOverState(bool victory);
  void handleInput(const sf::Event& event, Game& game) override;
  void update(float deltaTime) override;
  void draw(sf::RenderWindow& window) override;

 private:
  bool victory_;
};
