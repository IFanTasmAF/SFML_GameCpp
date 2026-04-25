#pragma once
#include <memory>

#include "GameState.h"

class Hero;
class Monster;
class ExploringState;

class CombatState : public GameState {
 public:
  CombatState(Game& game, ExploringState& exploring, Monster& monster,
              bool heroAttacksFirst);
  void handleInput(const sf::Event& event, Game& game) override;
  void update(float deltaTime) override;
  void draw(sf::RenderWindow& window) override;

 private:
  Hero& hero_;
  Monster& monster_;
  ExploringState& exploring_;
  bool heroWon_;
  bool finished_;
  float timer_;
};
