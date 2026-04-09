#pragma once
#include <vector>

#include "../entities/AggressiveMonster.h"
#include "../entities/PassiveMonster.h"
#include "../entities/Player.h"
#include "GameState.h"

class PlayState : public GameState {
 private:
  Player player;
  std::vector<Entity*> monsters;

 public:
  PlayState();

  void update(float dt) override;
  void draw(sf::RenderWindow& window) override;
};
