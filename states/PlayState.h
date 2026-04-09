#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <vector>

#include "../entities/Player.h"
#include "../ui/UI.h"
#include "../world/Map.h"
#include "GameState.h"

class Game;
class Monster;

class PlayState : public GameState {
 public:
  PlayState(sf::RenderWindow& window, Game* game);

  void handleInput(sf::RenderWindow& window) override;
  void update(float dt) override;
  void render(sf::RenderWindow& window) override;

 private:
  Game* game;

  Player player;
  Map map;
  UI ui;

  std::vector<Monster*> monsters;

  float move_delay;
  float move_timer;
};

#endif
