#pragma once
#include "Entity.h"

class PassiveMonster : public Entity {
 public:
  PassiveMonster(int x, int y);

  void update(float dt) override;
  void draw(sf::RenderWindow& window) override;
};
