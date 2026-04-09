#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "../entities/Monster.h"
#include "../entities/Player.h"

class PlayState {
 private:
  Player player;
  std::vector<Monster*> monsters;

 public:
  PlayState();

  void update(float dt);
  void draw(sf::RenderWindow& window);
};
