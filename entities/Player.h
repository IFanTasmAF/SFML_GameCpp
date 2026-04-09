#pragma once
#include "Entity.h"

class Player : public Entity {
 public:
  Player(float x, float y);

  void update(float dt) override;
  void draw(sf::RenderWindow& window) override;
};
