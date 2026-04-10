#pragma once
#include <vector>

#include "../entities/Monster.h"
#include "../entities/Player.h"
#include "../world/Map.h"
#include "../ui/UI.h"
#include "GameState.h"

class PlayState : public GameState {
 private:
  Player player;
  std::vector<Monster*> monsters;
  UI ui;
  Map map;

 public:
  PlayState();	

  void handleInput(sf::RenderWindow& window) override;
  void update(float dt) override;
  void render(sf::RenderWindow& window) override;
};
