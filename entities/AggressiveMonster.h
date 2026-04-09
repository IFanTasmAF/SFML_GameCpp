#pragma once
#include "Entity.h"

class AggressiveMonster : public Entity {
 public:
  AggressiveMonster(int x, int y);

  void update(float dt) override;
  void draw(sf::RenderWindow& window) override;
};
